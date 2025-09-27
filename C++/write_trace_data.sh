# curpath=`pwd`

TRACE_OUTPUT_DIR="../trace_output"

export LTTNG_SESSIOND_PATH=/usr/bin/lttng-sessiond
export LTTNG_TRACEPOINT_LIB=/usr/lib/x86_64-linux-gnu/liblttng-ust.so.0



export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
export LD_PRELOAD=./fake_clock.so
# babeltrace2 でトレースデータを表示
lttng create my_session --output "$TRACE_OUTPUT_DIR"
lttng enable-event -u -a
lttng add-context -u -t vpid -t procname -t vtid
lttng start

# 生成されたトレースディレクトリを取得
TRACE_DIR=$(lttng list | grep "Trace output:" | awk '{print $3}')




./write_lttng


lttng stop
lttng destroy

unset LD_PRELOAD




if [[ "$1" == "--display" ]]; then
# babeltrace2 でトレースデータを表示
    if [ -d "$TRACE_DIR" ]; then
        echo "Displaying trace from: $TRACE_DIR"
        babeltrace2 "$TRACE_DIR" 
    else
        echo "Trace directory not found: $TRACE_DIR"
        exit 1
    fi
fi

babeltrace2 "$TRACE_DIR" > "$TRACE_OUTPUT_DIR/latest_trace_data.txt"
echo $TRACE_DIR