import sys



# 配列を用意して初期化
Adaptive_application_name = [
    "AA1",
]

message_name = [
    "AA1toAA2"
] 


# 長い関数名を変数で組み立て
rclcpp_callback_register1 = (
    f'"{Adaptive_application_name[0]}::{Adaptive_application_name[0]}(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, '
    f'std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >, '
    f'std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)'
    f'::{{lambda(std::unique_ptr<sensor_msgs::msg::Image_<std::allocator<void> >, std::default_delete<sensor_msgs::msg::Image_<std::allocator<void> > > >)#1}}"'
)


"""
イベント名と引数リストから初期化用 tracepoint コードを生成する
"""
init_events = [
    ('rcl_node_init', [0x62EF47807CC0, 0x62EF4793C600, f'"{Adaptive_application_name[0]}"', '"/"', 6865866736588]),
    ('rcl_publisher_init', [0x55C04CBE1ED0, 0x62EF47807CC0, 0x55C04CBF9E30, f'"{message_name[0]}"', 10, 5250838799101]),
    ('rcl_publisher_init', [0x62EF47A32F70, 0x62EF47807CC0, 0x62EF47A61640, '"/parameter_events"', 1000, 6865874652999]),
    ('rcl_timer_init', [0x55C04CBF3320, 100000000, 5250838811707]),
    ('rclcpp_timer_callback_added', [0x55C04CBF3320, 0x55C04CBF5620, 5250838813380]),
    ('rclcpp_callback_register', [0x55C04CBF5620, rclcpp_callback_register1, 5250838817697]),
    ('callback_group_add_timer', [0x55C04CBC68A0, 0x55C04CBF3320, 5250838819631]),
    ('rclcpp_timer_link_node', [0x55C04CBF3320, 0x62EF47807CC0, 5250838821073]),
]

def main(output_file):
    def format_arg(a):
        if isinstance(a, int):
            # 10進数か16進数か判定（0xで始まるものは16進数で出力）
            if a > 0xFFFFFFFF:
                return f'0x{a:X}'
            else:
                return str(a)
        return a

    with open(output_file, 'w') as fout:
        for name, args in init_events:
            arg_str = ', '.join(format_arg(a) for a in args)
            fout.write(f'tracepoint(ros2_caret, {name}, {arg_str});\n')

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python make_init_tracepoints.py <output_file>")
        sys.exit(1)
    main(sys.argv[1])
