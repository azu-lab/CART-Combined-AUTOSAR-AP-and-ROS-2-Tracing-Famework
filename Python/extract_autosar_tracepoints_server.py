import re
import os
import sys

output_path = "output/autosar_tracepoints_server.csv"

keywords = [
    "=== AUTOSAR_callback_start_send ===",
    "=== AUTOSAR_rclcpp_publish ===",
    "=== AUTOSAR_callback_end_send ==="
]

if len(sys.argv) != 2:
    print("Usage: python extract_autosar_tracepoints_server.py <input_file> ")
    sys.exit(1)

input_path = sys.argv[1]

# 出力先ディレクトリがなければ作成
os.makedirs(os.path.dirname(output_path), exist_ok=True)


def pad_timestamp_to_nanos(ts: str) -> str:
    if not ts:
        return ts
    if '.' in ts:
        sec, frac = ts.split('.', 1)
        frac = ''.join(ch for ch in frac if ch.isdigit())
        frac9 = (frac + '0' * 9)[:9]
        return f"{int(sec)}{frac9}"
    if ts.isdigit():
        val = int(ts)
        # microseconds (>=16 digits) -> convert
        if len(ts) >= 16:
            sec = val // 1_000_000
            nsec = (val % 1_000_000) * 1000
            return f"{sec}{nsec:09d}"
        if len(ts) > 10:
            sec = val // 1_000_000_000
            nsec = val % 1_000_000_000
            return f"{sec}{nsec:09d}"
        return f"{val}000000000"

pattern = re.compile(r"\[(\d+)\].*?(=== AUTOSAR_[^=]+===)")

with open(input_path, "r") as fin, open(output_path, "w") as fout:
    for line in fin:
        m = pattern.search(line)
        if m:
            raw_ts = m.group(1)
            timestamp = pad_timestamp_to_nanos(raw_ts)
            label = m.group(2).replace("=== ","").replace(" ===","")
            fout.write(f"{label}, {timestamp}\n")
