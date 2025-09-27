import re
import sys
import os


output_path = "output/autosar_tracepoints_client.csv"

keywords = [
    "=== AUTOSAR_rmw_take ===",
    "=== AUTOSAR_callback_start_recieve ===",
    "=== AUTOSAR_callback_end_recieve ==="
]

if len(sys.argv) != 2:
    print("Usage: python extract_autosar_tracepoints_client.py <input_file> ")
    sys.exit(1)

input_path = sys.argv[1]

# 出力先ディレクトリがなければ作成
os.makedirs(os.path.dirname(output_path), exist_ok=True)


def pad_timestamp_to_nanos(ts: str) -> str:
    """
    Normalize a timestamp string into seconds.nanoseconds (9 digits) format.

    Accepts forms like:
    - "12345"              -> treated as seconds -> "12345.000000000"
    - "12345.678"          -> fractional seconds -> right-pad to 9 digits -> "12345.678000000"
    - "123456789012345678" -> integer nanoseconds -> convert to sec.nsec
    """
    if not ts:
        return ts
    # If it contains a dot, treat as seconds.fraction
    if '.' in ts:
        sec, frac = ts.split('.', 1)
        # keep only digits
        frac = ''.join(ch for ch in frac if ch.isdigit())
        frac9 = (frac + '0' * 9)[:9]
        return f"{int(sec)}{frac9}"
    # no dot: could be raw nanoseconds, microseconds, or plain seconds
    if ts.isdigit():
        try:
            val = int(ts)
        except ValueError:
            return ts
        # If it's long (likely microseconds, e.g., 16 digits), treat as microseconds and convert
        if len(ts) >= 16:
            # microseconds -> nanoseconds
            sec = val // 1_000_000
            nsec = (val % 1_000_000) * 1000
            return f"{sec}{nsec:09d}"
        # If moderately long (e.g., 10-15), it may already be nanoseconds or milliseconds
        if len(ts) > 10:
            # treat as nanoseconds
            sec = val // 1_000_000_000
            nsec = val % 1_000_000_000
            return f"{sec}{nsec:09d}"
        # otherwise treat as seconds
        return f"{val}.000000000"
    return ts

pattern = re.compile(r"\[(\d+)\].*?(=== AUTOSAR_[^=]+===)")

with open(input_path, "r") as fin, open(output_path, "w") as fout:
    for line in fin:
        m = pattern.search(line)
        if m:
            raw_ts = m.group(1)
            timestamp = pad_timestamp_to_nanos(raw_ts)
            label = m.group(2).replace("=== ","").replace(" ===",")")
            fout.write(f"{label}, {timestamp}\n")
