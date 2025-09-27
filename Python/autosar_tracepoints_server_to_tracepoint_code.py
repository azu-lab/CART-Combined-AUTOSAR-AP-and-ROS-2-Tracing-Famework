import os
import sys

def main(input_file, output_file):
    # AUTOSAR文言→tracepoint名の対応表
    mapping = {
        'AUTOSAR_callback_start_send': 'callback_start',
        'AUTOSAR_rclcpp_publish': 'rclcpp_publish',
        'AUTOSAR_callback_end_send': 'callback_end',
    }
    # 固定アドレス（make_tracepoint_write.pyと同じ）
    cb_addr_cache = 0x55C04CBF5620
    pub_addr_cache = 0x55C04CB413F0
    pub_addr_cache2 = 0x55C04CBE1ED0

    # タイムスタンプ出力ファイル名
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
            if tp == 'callback_start':
                tsout.write(ts + '\n')
                fout.write(f'tracepoint(ros2, callback_start, 0x{cb_addr_cache:X}, 0);\n')
            elif tp == 'rclcpp_publish':
                for _ in range(4):
                    tsout.write(ts + '\n')
                fout.write(f'tracepoint(ros2, rclcpp_publish, 0x{pub_addr_cache2:X}, 0x{pub_addr_cache:X});\n')
                fout.write(f'tracepoint(ros2, rcl_publish, 0x{pub_addr_cache2:X}, 0x{pub_addr_cache:X});\n')
                fout.write(f'tracepoint(ros2_caret, dds_write, 0x{pub_addr_cache:X});\n')
                fout.write(f'tracepoint(ros2_caret, dds_bind_addr_to_stamp, 0x{pub_addr_cache:X}, {ts});\n')
            elif tp == 'callback_end':
                tsout.write(ts + '\n')
                fout.write(f'tracepoint(ros2, callback_end, 0x{cb_addr_cache:X});\n')
            else:
                continue

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python autosar_tracepoints_server_to_tracepoint_code.py <input_file> <output_file>")
        sys.exit(1)
    main(sys.argv[1], sys.argv[2])
