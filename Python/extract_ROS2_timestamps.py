
import re
import sys
import os

from get_trace_datetime import TraceInfo
import shutil

# スクリプトとリポジトリのパス情報
SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
REPO_ROOT = os.path.normpath(os.path.join(SCRIPT_DIR, '..'))

# デフォルトのメタデータ元パス（実行環境に応じてフルパスを設定）
METADATA_ORIG = '/home/ryudai/13_CART/CART_dev/ROS2_tracedata/ust/uid/1000/64-bit/metadata'

# デフォルトのコピー先（通常は output ディレクトリ上に .txt として生成して利用する）
METADATA_COPY_DEFAULT = os.path.join(REPO_ROOT, 'output', os.path.basename(METADATA_ORIG) + '.txt')

# 注意: TraceInfo のインスタンスは main() 内で METADATA_COPY を使って作成します。


# ログファイルからタイムスタンプを抽出する関数（1つ目のピリオドだけを無視）
def extract_timestamps(log_content):
    # 正規表現パターン: 角括弧内のタイムスタンプを検索
    timestamp_pattern = re.compile(r'\[([\d\.:]+)\]')
    
    # 全ての行に対してタイムスタンプを検索
    timestamps = []
    for line in log_content.splitlines():
        match = timestamp_pattern.search(line)
        if match:
            # タイムスタンプを取得し、1つ目のピリオドだけを無視する処理
            timestamp = match.group(1)
            parts = timestamp.split('.')
            # print(parts)
            if len(parts) >= 2:
                # 1つ目のピリオドを無視して結合
                timestamp = parts[0] + ' ' + '.'.join(parts[1:])
            timestamps.append(timestamp)
    
    return timestamps

# ファイルからログを読み込む
def read_log_file(file_path):
    with open(file_path, 'r') as f:
        return f.read()

# タイムスタンプをファイルに保存
def save_timestamps(timestamps, output_path):
    # 出力ディレクトリが存在しなければ作成する
    out_dir = os.path.dirname(output_path)
    if out_dir:
        os.makedirs(out_dir, exist_ok=True)
    with open(output_path, 'w') as f:
        for timestamp in timestamps:
            f.write(f"{timestamp}\n")
    print(f"{len(timestamps)} 件のタイムスタンプを {output_path} に保存しました")



# コマンドライン引数必須

import re
import sys
import os

def extract_timestamps(log_content):
    timestamp_pattern = re.compile(r'\[([\d\.:]+)\]')
    timestamps = []
    for line in log_content.splitlines():
        match = timestamp_pattern.search(line)
        if match:
            timestamp = match.group(1)
            parts = timestamp.split('.')
            if len(parts) >= 2:
                timestamp = parts[0] + ' ' + '.'.join(parts[1:])
            timestamps.append(timestamp)
    return timestamps

def read_log_file(file_path):
    with open(file_path, 'r') as f:
        return f.read()

def save_timestamps(timestamps, output_path, date_prefix=None):
    # 出力ディレクトリが存在しなければ作成する
    out_dir = os.path.dirname(output_path)
    if out_dir:
        os.makedirs(out_dir, exist_ok=True)
    with open(output_path, 'w') as f:
        for timestamp in timestamps:
            if date_prefix:
                f.write(f"{date_prefix} {timestamp}\n")
            else:
                f.write(f"{timestamp}\n")
    print(f"{len(timestamps)} 件のタイムスタンプを {output_path} に保存しました")

def main():
    if len(sys.argv) < 3:
        print("Usage: python ex_timestamp.py <input_file> <output_file>")
        sys.exit(1)
    file_path = sys.argv[1]
    output_path = sys.argv[2]
    if not os.path.isfile(file_path):
        print(f"入力ファイルが存在しません: {file_path}")
        sys.exit(1)
    # ログからタイムスタンプを抽出
    log_content = read_log_file(file_path)
    timestamps = extract_timestamps(log_content)

    # メタデータ原本を output/ 配下に .txt としてコピーしてそれを使用する
    try:
        if not os.path.exists(METADATA_ORIG):
            print(f"エラー: メタデータ元ファイルが見つかりません: {METADATA_ORIG}")
            sys.exit(1)
        # コピー先は output フォルダ内（必要ならコマンドラインで上書き可能に拡張可）
        metadata_copy = METADATA_COPY_DEFAULT
        out_dir = os.path.dirname(metadata_copy)
        os.makedirs(out_dir, exist_ok=True)
        shutil.copy(METADATA_ORIG, metadata_copy)
        print(f"メタデータを {metadata_copy} にコピーしました")
    except Exception as e:
        print(f"メタデータのコピーに失敗しました: {e}")
        sys.exit(1)

    # コピーしたファイルから日時情報を取得
    trace = TraceInfo(metadata_copy)
    if not trace.is_valid():
        print("エラー: トレースのメタデータから日時情報を取得できませんでした。")
        sys.exit(1)
    date_prefix = f"{trace.year}/{trace.month:02}/{trace.day:02}"
    save_timestamps(timestamps, output_path, date_prefix)

if __name__ == "__main__":
    main()

