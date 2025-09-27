babeltrace2 ROS2_tracedata/ust/uid/1000/64-bit > input/ROS2_trace_data.txt

python3 Python/extract_ROS2_timestamps.py input/ROS2_trace_data.txt output/output_ros2_timestamps.txt

python3 Python/make_ROS2_tracepoints.py input/ROS2_trace_data.txt tracepoint_code/output_ROS2_tracepoints_injected.c

python3 Python/extract_ros2_callback_start_for_addr.py input/ROS2_trace_data.txt output/ros2_callback_start_55C04CBCA488.txt 0x55C04CBCA488
echo "ROS2トレースポイントの抽出とコード生成が完了しました。"