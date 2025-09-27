#!/usr/bin/env python3
"""
指定したアドレスの `callback_start` イベントのみからタイムスタンプとアドレスを抽出する。
使い方:
  python3 extract_ros2_callback_start_for_addr.py <input_file> <output_file> <0xADDRESS>

出力形式:
  TIMESTAMP 0xADDRESS
例:
  17:53:10.366067580 0x55C04CBCA488
"""
import re
import sys
import os
from datetime import datetime

TS_RE = re.compile(r"\[([0-9]{1,2}:[0-9]{2}:[0-9]{2}\.[0-9]+)\]")
ADDR_RE = re.compile(r"0x[0-9A-Fa-f]+")
EVENT_RE = re.compile(r"\bros2:callback_start:\b")


def process(in_path, out_path, address):
    if not os.path.isfile(in_path):
        print(f"入力ファイルが見つかりません: {in_path}")
        sys.exit(1)
    out_dir = os.path.dirname(out_path)
    if out_dir:
        os.makedirs(out_dir, exist_ok=True)

    count = 0
    with open(in_path, 'r', encoding='utf-8', errors='ignore') as inf, open(out_path, 'w', encoding='utf-8') as outf:
        for line in inf:
            # ログ内に 'ros2:callback_start' と指定アドレスが含まれる行のみ処理
            if 'ros2:callback_start' not in line:
                continue
            # 大文字小文字の差を無視してアドレスを確認
            if address.lower() not in line.lower():
                continue
            ts_m = TS_RE.search(line)
            addr_m = ADDR_RE.search(line)
            if ts_m and addr_m:
                # addr_m で見つかった最初のアドレスが指定アドレスと一致するか確認（小文字比較）
                if addr_m.group(0).lower() == address.lower():
                    ts = ts_m.group(1)  # 例: 17:53:10.366067580
                    # 日付情報がログ行にないため、実行時のローカル日付を使用して unix 時間へ変換する
                    try:
                        hms, frac = ts.split('.', 1) if '.' in ts else (ts, '0')
                        h, m, s = map(int, hms.split(':'))
                        # ナノ秒長に正規化
                        nanos = (frac + '000000000')[:9]
                        today = datetime.now()
                        dt = datetime(year=today.year, month=today.month, day=today.day, hour=h, minute=m, second=s)
                        epoch_sec = int(dt.timestamp())
                        # マイクロ秒に変換（小数部はナノ秒から先頭6桁を使用）
                        micros = int(nanos[:6])
                        total_micros = epoch_sec * 1_000_000 + micros
                        # 出力はマイクロ秒精度の整数（Unix epoch マイクロ秒）
                        outf.write(f"{total_micros}\n")
                        count += 1
                    except Exception:
                        # 何か解析できなければスキップ
                        continue
    print(f"{count} 件抽出して {out_path} に保存しました。")


if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Usage: python3 extract_ros2_callback_start_for_addr.py <input> <output> <0xADDRESS>")
        sys.exit(1)
    process(sys.argv[1], sys.argv[2], sys.argv[3])
