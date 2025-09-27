import sys



# 配列を用意して初期化
Adaptive_application_name = [
    "AA2"
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
    ('rcl_node_init', [0x55C04CC2CCA0, 0x62EF4793C600, f'"{Adaptive_application_name[1]}"', '"/"', 6865874652999]),
    ('add_callback_group', [0x55C04CAD9B20, 0x55C04CBC68A0, '"mutually_exclusive"', 5250835331000]),
    ('rcl_subscription_init', [0x55C04CC590D0, 0x55C04CC2CCA0, 0x62EF47807CC0, f'"{message_name[0]}"', 10, 5250835329685]),
    ('add_callback_group', [0x55C04CAD9B20, 0x7FB54C006210, '"mutually_exclusive"', 5250835331000]),
    ('rclcpp_subscription_init', [0x55C04CC590D0, 0x55C04CB65B50, 5250835329685]),
    ('rclcpp_subscription_callback_added', [0x55C04CB65B50, 0x55C04CBCA488, 5250835332000]),
    ('rclcpp_callback_register', [0x55C04CBCA488, rclcpp_callback_register1, 5250835333000]),
    ('callback_group_add_subscription', [0x7FB54C006210, 0x55C04CC590D0, 5250835330000]),
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
