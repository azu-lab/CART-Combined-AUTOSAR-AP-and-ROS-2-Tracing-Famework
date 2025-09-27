/*
 * ros2_caret_tracepoints.h - LTTng tracepoint definitions for ros2_caret events.
 *
 * 各イベント定義:
 *   Provider : ros2_caret
 *   (id, stream_id, loglevel は LTTng内部で管理)
 */

#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER ros2_caret

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "ros2_caret_tracepoints.h"

#if !defined(ROS2_CARET_TRACEPOINTS_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define ROS2_CARET_TRACEPOINTS_H

#include <lttng/tracepoint.h>
#include <stdint.h>

/* event id: 32, ros2_caret:on_data_available */
TRACEPOINT_EVENT(
    ros2_caret,
    on_data_available,
    TP_ARGS(
        uint64_t, source_stamp
    ),
    TP_FIELDS(
        ctf_integer(uint64_t, source_stamp, source_stamp)
    )
)

/* event id: 33, ros2_caret:dds_write */
TRACEPOINT_EVENT(
    ros2_caret,
    dds_write,
    TP_ARGS(
        uint64_t, message
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, message, message)
    )
)

/* event id: 34, ros2_caret:dds_bind_addr_to_stamp */
TRACEPOINT_EVENT(
    ros2_caret,
    dds_bind_addr_to_stamp,
    TP_ARGS(
        uint64_t, addr,
        uint64_t, source_stamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, addr, addr)
        ctf_integer(uint64_t, source_stamp, source_stamp)
    )
)

/* event id: 35, ros2_caret:dds_bind_addr_to_addr */
TRACEPOINT_EVENT(
    ros2_caret,
    dds_bind_addr_to_addr,
    TP_ARGS(
        uint64_t, addr_from,
        uint64_t, addr_to
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, addr_from, addr_from)
        ctf_integer_hex(uint64_t, addr_to, addr_to)
    )
)

/* event id: 36, ros2_caret:rmw_implementation */
TRACEPOINT_EVENT(
    ros2_caret,
    rmw_implementation,
    TP_ARGS(
        const char*, rmw_impl,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_string(rmw_impl, rmw_impl)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 37, ros2_caret:construct_executor */
TRACEPOINT_EVENT(
    ros2_caret,
    construct_executor,
    TP_ARGS(
        uint64_t, executor_addr,
        const char*, executor_type_name,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, executor_addr, executor_addr)
        ctf_string(executor_type_name, executor_type_name)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 38, ros2_caret:construct_static_executor */
TRACEPOINT_EVENT(
    ros2_caret,
    construct_static_executor,
    TP_ARGS(
        uint64_t, executor_addr,
        uint64_t, entities_collector_addr,
        const char*, executor_type_name,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, executor_addr, executor_addr)
        ctf_integer_hex(uint64_t, entities_collector_addr, entities_collector_addr)
        ctf_string(executor_type_name, executor_type_name)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 39, ros2_caret:add_callback_group */
TRACEPOINT_EVENT(
    ros2_caret,
    add_callback_group,
    TP_ARGS(
        uint64_t, executor_addr,
        uint64_t, callback_group_addr,
        const char*, group_type_name,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, executor_addr, executor_addr)
        ctf_integer_hex(uint64_t, callback_group_addr, callback_group_addr)
        ctf_string(group_type_name, group_type_name)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 40, ros2_caret:add_callback_group_static_executor */
TRACEPOINT_EVENT(
    ros2_caret,
    add_callback_group_static_executor,
    TP_ARGS(
        uint64_t, entities_collector_addr,
        uint64_t, callback_group_addr,
        const char*, group_type_name,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, entities_collector_addr, entities_collector_addr)
        ctf_integer_hex(uint64_t, callback_group_addr, callback_group_addr)
        ctf_string(group_type_name, group_type_name)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 41, ros2_caret:callback_group_add_timer */
TRACEPOINT_EVENT(
    ros2_caret,
    callback_group_add_timer,
    TP_ARGS(
        uint64_t, callback_group_addr,
        uint64_t, timer_handle,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback_group_addr, callback_group_addr)
        ctf_integer_hex(uint64_t, timer_handle, timer_handle)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 42, ros2_caret:callback_group_add_subscription */
TRACEPOINT_EVENT(
    ros2_caret,
    callback_group_add_subscription,
    TP_ARGS(
        uint64_t, callback_group_addr,
        uint64_t, subscription_handle,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback_group_addr, callback_group_addr)
        ctf_integer_hex(uint64_t, subscription_handle, subscription_handle)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 43, ros2_caret:callback_group_add_service */
TRACEPOINT_EVENT(
    ros2_caret,
    callback_group_add_service,
    TP_ARGS(
        uint64_t, callback_group_addr,
        uint64_t, service_handle,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback_group_addr, callback_group_addr)
        ctf_integer_hex(uint64_t, service_handle, service_handle)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 44, ros2_caret:callback_group_add_client */
TRACEPOINT_EVENT(
    ros2_caret,
    callback_group_add_client,
    TP_ARGS(
        uint64_t, callback_group_addr,
        uint64_t, client_handle,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback_group_addr, callback_group_addr)
        ctf_integer_hex(uint64_t, client_handle, client_handle)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 45, ros2_caret:sim_time */
TRACEPOINT_EVENT(
    ros2_caret,
    sim_time,
    TP_ARGS(
        uint64_t, stamp
    ),
    TP_FIELDS(
        ctf_integer(uint64_t, stamp, stamp)
    )
)

/* event id: 46, ros2_caret:caret_init */
TRACEPOINT_EVENT(
    ros2_caret,
    caret_init,
    TP_ARGS(
        int64_t, clock_offset,
        const char*, distribution
    ),
    TP_FIELDS(
        ctf_integer(int64_t, clock_offset, clock_offset)
        ctf_string(distribution, distribution)
    )
)

/* event id: 47, ros2_caret:rcl_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_init,
    TP_ARGS(
        uint64_t, context_handle,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, context_handle, context_handle)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 48, ros2_caret:rcl_node_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_node_init,
    TP_ARGS(
        uint64_t, node_handle,
        uint64_t, rmw_handle,
        const char*, node_name,
        const char*, node_namespace,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_handle, rmw_handle)
        ctf_string(node_name, node_name)
        ctf_string(namespace, node_namespace)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 49, ros2_caret:rcl_publisher_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_publisher_init,
    TP_ARGS(
        uint64_t, publisher_handle,
        uint64_t, node_handle,
        uint64_t, rmw_publisher_handle,
        const char*, topic_name,
        uint64_t, queue_depth,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, publisher_handle, publisher_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_publisher_handle, rmw_publisher_handle)
        ctf_string(topic_name, topic_name)
        ctf_integer(uint64_t, queue_depth, queue_depth)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 50, ros2_caret:rcl_subscription_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_subscription_init,
    TP_ARGS(
        uint64_t, subscription_handle,
        uint64_t, node_handle,
        uint64_t, rmw_subscription_handle,
        const char*, topic_name,
        uint64_t, queue_depth,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, subscription_handle, subscription_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_subscription_handle, rmw_subscription_handle)
        ctf_string(topic_name, topic_name)
        ctf_integer(uint64_t, queue_depth, queue_depth)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 51, ros2_caret:rclcpp_subscription_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_subscription_init,
    TP_ARGS(
        uint64_t, subscription_handle,
        uint64_t, subscription,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, subscription_handle, subscription_handle)
        ctf_integer_hex(uint64_t, subscription, subscription)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 52, ros2_caret:rclcpp_subscription_callback_added */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_subscription_callback_added,
    TP_ARGS(
        uint64_t, subscription,
        uint64_t, callback,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, subscription, subscription)
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 53, ros2_caret:rcl_timer_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_timer_init,
    TP_ARGS(
        uint64_t, timer_handle,
        int64_t, period,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, timer_handle, timer_handle)
        ctf_integer(int64_t, period, period)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 54, ros2_caret:rclcpp_timer_callback_added */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_timer_callback_added,
    TP_ARGS(
        uint64_t, timer_handle,
        uint64_t, callback,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, timer_handle, timer_handle)
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 55, ros2_caret:rclcpp_timer_link_node */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_timer_link_node,
    TP_ARGS(
        uint64_t, timer_handle,
        uint64_t, node_handle,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, timer_handle, timer_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 56, ros2_caret:rclcpp_callback_register */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_callback_register,
    TP_ARGS(
        uint64_t, callback,
        const char*, symbol,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_string(symbol, symbol)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 57, ros2_caret:rcl_service_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_service_init,
    TP_ARGS(
        uint64_t, service_handle,
        uint64_t, node_handle,
        uint64_t, rmw_service_handle,
        const char*, service_name,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, service_handle, service_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_service_handle, rmw_service_handle)
        ctf_string(service_name, service_name)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 58, ros2_caret:rclcpp_service_callback_added */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_service_callback_added,
    TP_ARGS(
        uint64_t, service_handle,
        uint64_t, callback,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, service_handle, service_handle)
        ctf_integer_hex(uint64_t, callback, callback)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 59, ros2_caret:rcl_client_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_client_init,
    TP_ARGS(
        uint64_t, client_handle,
        uint64_t, node_handle,
        uint64_t, rmw_client_handle,
        const char*, service_name,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, client_handle, client_handle)
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, rmw_client_handle, rmw_client_handle)
        ctf_string(service_name, service_name)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 60, ros2_caret:rcl_lifecycle_state_machine_init */
TRACEPOINT_EVENT(
    ros2_caret,
    rcl_lifecycle_state_machine_init,
    TP_ARGS(
        uint64_t, node_handle,
        uint64_t, state_machine,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, node_handle, node_handle)
        ctf_integer_hex(uint64_t, state_machine, state_machine)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 61, ros2_caret:rclcpp_ipb_to_subscription */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_ipb_to_subscription,
    TP_ARGS(
        uint64_t, ipb,
        uint64_t, subscription,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, ipb, ipb)
        ctf_integer_hex(uint64_t, subscription, subscription)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 62, ros2_caret:rclcpp_buffer_to_ipb */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_buffer_to_ipb,
    TP_ARGS(
        uint64_t, buffer,
        uint64_t, ipb,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, buffer, buffer)
        ctf_integer_hex(uint64_t, ipb, ipb)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

/* event id: 63, ros2_caret:rclcpp_construct_ring_buffer */
TRACEPOINT_EVENT(
    ros2_caret,
    rclcpp_construct_ring_buffer,
    TP_ARGS(
        uint64_t, buffer,
        uint64_t, capacity,
        int64_t, init_timestamp
    ),
    TP_FIELDS(
        ctf_integer_hex(uint64_t, buffer, buffer)
        ctf_integer(uint64_t, capacity, capacity)
        ctf_integer(int64_t, init_timestamp, init_timestamp)
    )
)

#endif /* ROS2_CARET_TRACEPOINTS_H */

#include <lttng/tracepoint-event.h>
