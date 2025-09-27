/*
 * ros2_tracepoints.h - LTTng tracepoint definitions for all ros2 events.
 *
 * 各イベント定義:
 *   Provider : ros2
 *   (id, stream_id, loglevel は LTTng内部で管理)
 */

 #undef TRACEPOINT_PROVIDER
 #define TRACEPOINT_PROVIDER ros2
 
 #undef TRACEPOINT_INCLUDE
 #define TRACEPOINT_INCLUDE "ros2_tracepoints.h"
 
 #if !defined(ROS2_TRACEPOINTS_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
 #define ROS2_TRACEPOINTS_H
 
 #include <lttng/tracepoint.h>
 #include <stdint.h>
 
 /* event id: 0, ros2:rcl_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_init,
    TP_ARGS(
        uint64_t, context_handle,
        const char*, version
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, context_handle, context_handle)
        ctf_string(version, version)
    )
 )
 
 /* event id: 1, ros2:rcl_node_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_node_init,
    TP_ARGS(
        uint64_t, node_handle,
        uint64_t, rmw_handle,
        const char*, node_name,
        const char*, namespace
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_handle, rmw_handle)
        ctf_string(node_name, node_name)
        ctf_string(namespace, namespace)
    )
 )
 
 /* event id: 2, ros2:rmw_publisher_init */
 TRACEPOINT_EVENT(
    ros2,
    rmw_publisher_init,
    TP_ARGS(
        uint64_t, rmw_publisher_handle,
        const uint8_t*, gid
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, rmw_publisher_handle, rmw_publisher_handle)
        ctf_array(uint8_t, gid, gid, 24)
    )
 )
 
 /* event id: 3, ros2:rcl_publisher_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_publisher_init,
    TP_ARGS(
        uint64_t, publisher_handle,
        uint64_t, node_handle,
        uint64_t, rmw_publisher_handle,
        const char*, topic_name,
        uint64_t, queue_depth
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, publisher_handle, publisher_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_publisher_handle, rmw_publisher_handle)
        ctf_string(topic_name, topic_name)
        ctf_integer(uint64_t, queue_depth, queue_depth)
    )
 )
 
 /* event id: 4, ros2:rclcpp_publish */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_publish,
    TP_ARGS(
        uint64_t, publisher_handle,
        uint64_t, message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, publisher_handle, publisher_handle)
        ctf_integer_hex(uint64_t, message, message)
    )
 )
 
 /* event id: 5, ros2:rcl_publish */
 TRACEPOINT_EVENT(
    ros2,
    rcl_publish,
    TP_ARGS(
        uint64_t, publisher_handle,
        uint64_t, message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, publisher_handle, publisher_handle)
        ctf_integer_hex(uint64_t, message, message)
    )
 )
 
 /* event id: 6, ros2:rmw_publish */
 TRACEPOINT_EVENT(
    ros2,
    rmw_publish,
    TP_ARGS(
        uint64_t, message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, message, message)
    )
 )
 
 /* event id: 7, ros2:rmw_subscription_init */
 TRACEPOINT_EVENT(
    ros2,
    rmw_subscription_init,
    TP_ARGS(
        uint64_t, rmw_subscription_handle,
        const uint8_t*, gid
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, rmw_subscription_handle, rmw_subscription_handle)
        ctf_array(uint8_t, gid, gid, 24)
    )
 )
 
 /* event id: 8, ros2:rcl_subscription_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_subscription_init,
    TP_ARGS(
        uint64_t, subscription_handle,
        uint64_t, node_handle,
        uint64_t, rmw_subscription_handle,
        const char*, topic_name,
        uint64_t, queue_depth
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, subscription_handle, subscription_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_subscription_handle, rmw_subscription_handle)
        ctf_string(topic_name, topic_name)
        ctf_integer(uint64_t, queue_depth, queue_depth)
    )
 )
 
 /* event id: 9, ros2:rclcpp_subscription_init */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_subscription_init,
    TP_ARGS(
        uint64_t, subscription_handle,
        uint64_t, subscription
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, subscription_handle, subscription_handle)
        ctf_integer_hex(uint64_t, subscription, subscription)
    )
 )
 
 /* event id: 10, ros2:rclcpp_subscription_callback_added */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_subscription_callback_added,
    TP_ARGS(
        uint64_t, subscription,
        uint64_t, callback
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, subscription, subscription)
        ctf_integer_hex(uint64_t, callback, callback)
    )
 )
 
 /* event id: 11, ros2:rmw_take */
 TRACEPOINT_EVENT(
    ros2,
    rmw_take,
    TP_ARGS(
        uint64_t, rmw_subscription_handle,
        uint64_t, message,
        int64_t, source_timestamp,
        int32_t, taken
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, rmw_subscription_handle, rmw_subscription_handle)
        ctf_integer_hex(uint64_t, message, message)
        ctf_integer(int64_t, source_timestamp, source_timestamp)
        ctf_integer(int32_t, taken, taken)
    )
 )
 
 /* event id: 12, ros2:rcl_take */
 TRACEPOINT_EVENT(
    ros2,
    rcl_take,
    TP_ARGS(
        uint64_t, message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, message, message)
    )
 )
 
 /* event id: 13, ros2:rclcpp_take */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_take,
    TP_ARGS(
        uint64_t, message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, message, message)
    )
 )
 
 /* event id: 14, ros2:rcl_service_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_service_init,
    TP_ARGS(
        uint64_t, service_handle,
        uint64_t, node_handle,
        uint64_t, rmw_service_handle,
        const char*, service_name
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, service_handle, service_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_service_handle, rmw_service_handle)
        ctf_string(service_name, service_name)
    )
 )
 
 /* event id: 15, ros2:rclcpp_service_callback_added */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_service_callback_added,
    TP_ARGS(
        uint64_t, service_handle,
        uint64_t, callback
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, service_handle, service_handle)
        ctf_integer_hex(uint64_t, callback, callback)
    )
 )
 
 /* event id: 16, ros2:rcl_client_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_client_init,
    TP_ARGS(
        uint64_t, client_handle,
        uint64_t, node_handle,
        uint64_t, rmw_client_handle,
        const char*, service_name
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, client_handle, client_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_client_handle, rmw_client_handle)
        ctf_string(service_name, service_name)
    )
 )
 
 /* event id: 17, ros2:rcl_timer_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_timer_init,
    TP_ARGS(
        uint64_t, timer_handle,
        int64_t, period
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, timer_handle, timer_handle)
        ctf_integer(int64_t, period, period)
    )
 )
 
 /* event id: 18, ros2:rclcpp_timer_callback_added */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_timer_callback_added,
    TP_ARGS(
        uint64_t, timer_handle,
        uint64_t, callback
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, timer_handle, timer_handle)
        ctf_integer_hex(uint64_t, callback, callback)
    )
 )
 
 /* event id: 19, ros2:rclcpp_timer_link_node */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_timer_link_node,
    TP_ARGS(
        uint64_t, timer_handle,
        uint64_t, node_handle
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, timer_handle, timer_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
    )
 )
 
 /* event id: 20, ros2:rclcpp_callback_register */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_callback_register,
    TP_ARGS(
        uint64_t, callback,
        const char*, symbol
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_string(symbol, symbol)
    )
 )
 
 /* event id: 21, ros2:callback_start */
 TRACEPOINT_EVENT(
    ros2,
    callback_start,
    TP_ARGS(
        uint64_t, callback,
        int32_t, is_intra_process
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_integer(int32_t, is_intra_process, is_intra_process)
    )
 )
 
 /* event id: 22, ros2:callback_end */
 TRACEPOINT_EVENT(
    ros2,
    callback_end,
    TP_ARGS(
        uint64_t, callback
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback, callback)
    )
 )
 
 /* event id: 23, ros2:rcl_lifecycle_state_machine_init */
 TRACEPOINT_EVENT(
    ros2,
    rcl_lifecycle_state_machine_init,
    TP_ARGS(
        uint64_t, node_handle,
        uint64_t, state_machine
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, state_machine, state_machine)
    )
 )
 
 /* event id: 24, ros2:rcl_lifecycle_transition */
 TRACEPOINT_EVENT(
    ros2,
    rcl_lifecycle_transition,
    TP_ARGS(
        uint64_t, state_machine,
        const char*, start_label,
        const char*, goal_label
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, state_machine, state_machine)
        ctf_string(start_label, start_label)
        ctf_string(goal_label, goal_label)
    )
 )
 
 /* event id: 25, ros2:rclcpp_executor_get_next_ready */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_executor_get_next_ready,
    TP_ARGS(),
    TP_FIELDS()
 )
 
 /* event id: 26, ros2:rclcpp_executor_wait_for_work */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_executor_wait_for_work,
    TP_ARGS(
        int64_t, timeout
    ),
    TP_FIELDS(
        ctf_integer(int64_t, timeout, timeout)
    )
 )
 
 /* event id: 27, ros2:rclcpp_executor_execute */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_executor_execute,
    TP_ARGS(
        uint64_t, handle
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, handle, handle)
    )
 )
 
 /* event id: 28, ros2:message_construct */
 TRACEPOINT_EVENT(
    ros2,
    message_construct,
    TP_ARGS(
        uint64_t, original_message,
        uint64_t, constructed_message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, original_message, original_message)
        ctf_integer_hex(uint64_t, constructed_message, constructed_message)
    )
 )
 
 /* event id: 29, ros2:rclcpp_intra_publish */
 TRACEPOINT_EVENT(
    ros2,
    rclcpp_intra_publish,
    TP_ARGS(
        uint64_t, publisher_handle,
        uint64_t, message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, publisher_handle, publisher_handle)
        ctf_integer_hex(uint64_t, message, message)
    )
 )
 
 /* event id: 30, ros2:dispatch_subscription_callback */
 TRACEPOINT_EVENT(
    ros2,
    dispatch_subscription_callback,
    TP_ARGS(
        uint64_t, message,
        uint64_t, callback,
        uint64_t, source_stamp,
        uint64_t, message_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, message, message)
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_integer(uint64_t, source_stamp, source_stamp)
        ctf_integer(uint64_t, message_timestamp, message_timestamp)
    )
 )
 
 /* event id: 31, ros2:dispatch_intra_process_subscription_callback */
 TRACEPOINT_EVENT(
    ros2,
    dispatch_intra_process_subscription_callback,
    TP_ARGS(
        uint64_t, message,
        uint64_t, callback,
        uint64_t, message_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, message, message)
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_integer(uint64_t, message_timestamp, message_timestamp)
    )
 )
 
 #endif /* ROS2_TRACEPOINTS_H */
 
 #include <lttng/tracepoint-event.h>
