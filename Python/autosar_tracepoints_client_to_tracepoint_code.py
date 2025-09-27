import os
import sys

def main(input_file, output_file):
    # AUTOSAR文言→tracepoint名の対応表
    mapping = {
        'AUTOSAR_rmw_take': 'rmw_take',
        'AUTOSAR_callback_start_recieve': 'callback_start',
        'AUTOSAR_callback_end_recieve': 'callback_end',
    }
    # 固定アドレス（make_tracepoint_read.pyと同じ）
    cb_addr_cache = 0x55C04CBCA488
    cb_rmw_take1_cache = 0x55C04CBCC040
    cb_rmw_take2_cache = 0x55C04CADCBA0

    ts_output_file = os.path.splitext(output_file)[0] + "_timestamps.txt"

    with open(input_file, 'r') as fin, \
         open(output_file, 'w') as fout, \
         open(ts_output_file, 'w') as tsout:
        for idx, line in enumerate(fin):
            line = line.strip()
            if not line:
                continue
            label, ts = [x.strip() for x in line.split(',', 1)]
            tp = mapping.get(label)
            tsout.write(ts + '\n')
            if tp == 'rmw_take':
                fout.write(f'tracepoint(ros2, rmw_take, 0x{cb_rmw_take1_cache:X}, 0x{cb_rmw_take2_cache:X}, {ts}, 1);\n')
            elif tp == 'callback_start':
                fout.write(f'tracepoint(ros2, callback_start, 0x{cb_addr_cache:X}, 0);\n')
            elif tp == 'callback_end':
                fout.write(f'tracepoint(ros2, callback_end, 0x{cb_addr_cache:X});\n')
            else:
                continue

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python autosar_tracepoints_to_tracepoint_code.py <input_file> <output_file>")
        sys.exit(1)
    main(sys.argv[1], sys.argv[2])
