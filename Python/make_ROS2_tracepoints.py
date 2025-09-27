
import re
import sys
import os

def extract_groups(line):
    groups = []
    in_quotes = False
    group_start = None
    escape = False
    for i, char in enumerate(line):
        if char == '\\' and not escape:
            escape = True
            continue
        if char == '"' and not escape:
            in_quotes = not in_quotes
        if char == '{' and not in_quotes:
            if group_start is None:
                group_start = i
        elif char == '}' and not in_quotes:
            if group_start is not None:
                groups.append(line[group_start+1:i])
                group_start = None
        escape = False
    return groups

def split_on_comma(text):
    parts = []
    current = []
    in_quotes = False
    escape = False
    for char in text:
        if char == '\\' and not escape:
            escape = True
            current.append(char)
            continue
        if char == '"' and not escape:
            in_quotes = not in_quotes
            current.append(char)
        elif char == ',' and not in_quotes:
            parts.append(''.join(current).strip())
            current = []
        else:
            current.append(char)
        escape = False
    if current:
        parts.append(''.join(current).strip())
    return parts

def parse_log(input_path, output_path, max_lines=10000):
    line_count = 0
    # 出力ディレクトリが存在しなければ作成する
    out_dir = os.path.dirname(output_path)
    if out_dir:
        os.makedirs(out_dir, exist_ok=True)

    with open(input_path, 'r', encoding='utf-8') as f, open(output_path, 'w', encoding='utf-8') as out_f:
        for line in f:
            line_count += 1
            if line_count > max_lines:
                break
            line = line.strip()
            if not line:
                continue

            event_match = re.search(r"\]\s+\([^)]+\)\s+\S+\s+(.*):\s+\{", line)
            if event_match:
                event = event_match.group(1)
                event_parts = [part.strip() for part in event.split(':')]
            else:
                event_parts = []

            groups = extract_groups(line)
            data_key = []
            data_value = []
            if len(groups) >= 3:
                third_group = groups[2]
                pairs = split_on_comma(third_group)
                for pair in pairs:
                    if '=' in pair:
                        key, value = pair.split('=', 1)
                        data_key.append(key.strip())
                        data_value.append(value.strip())

            params = event_parts[:2]
            for value in data_value:
                params.append(value)
            tracepoint_cmd = "tracepoint(" + ", ".join(params) + ");"
            out_f.write(tracepoint_cmd + "\n")
            out_f.write("j++;\n")
            out_f.write("set_fake_timestamp(unix_ns3[j]);\n")


def main():
    if len(sys.argv) < 3:
        print("Usage: python analysis.py <input_file> <output_file>")
        sys.exit(1)
    file_path = sys.argv[1]
    output_path = sys.argv[2]
    if not os.path.isfile(file_path):
        print(f"入力ファイルが存在しません: {file_path}")
        # 既存処理を中止する代わりに、空のプレースホルダを生成して呼び出し元が続行できるようにする
        out_dir = os.path.dirname(output_path)
        if out_dir:
            os.makedirs(out_dir, exist_ok=True)
        with open(output_path, 'w', encoding='utf-8') as out_f:
            out_f.write("/* (自動生成) 入力ログが無いためプレースホルダを作成しました。 */\n")
        print(f"プレースホルダを作成しました: {output_path}")
        return
    parse_log(file_path, output_path)

if __name__ == "__main__":
    main()
