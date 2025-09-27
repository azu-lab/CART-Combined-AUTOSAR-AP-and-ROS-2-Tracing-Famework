import argparse
import os
import sys

def inject_tracepoints(input_file):
    output_dir = "tracepoint_code"
    os.makedirs(output_dir, exist_ok=True)
    base = os.path.splitext(os.path.basename(input_file))[0]
    output_path = os.path.join(output_dir, f"{base}_injected.c")

    with open(input_file, 'r') as fin, open(output_path, 'w') as fout:
        for line in fin:
            fout.write(line)
            if line.strip().startswith("tracepoint"):
                fout.write("    j++;\n")
                fout.write("    set_fake_timestamp(unix_ns1[j]);\n")
    print(f"Injected file saved to: {output_path}")

def main():
    parser = argparse.ArgumentParser(
        description="tracepoint の直後に usleep()/j++/set_fake_timestamp() を差し込む"
    )
    parser.add_argument("input_files", nargs='+', help="tracepoint 呼び出しを含むソースファイル（複数指定可）")
    args = parser.parse_args()

    for input_file in args.input_files:
        if not os.path.isfile(input_file):
            print(f"Error: '{input_file}' が見つかりません", file=sys.stderr)
            continue
        inject_tracepoints(input_file)

if __name__ == "__main__":
    main()