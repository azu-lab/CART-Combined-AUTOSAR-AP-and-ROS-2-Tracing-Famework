    rm -f write_lttng
    rm -f ros2_tracepoints.so
    rm -f ros2_caret_tracepoints.so
    rm -f fake_clock.so
    gcc -shared -o ros2_tracepoints.so -fPIC -I. ros2_tracepoints.c -llttng-ust
    gcc -shared -o ros2_caret_tracepoints.so -fPIC -I. ros2_caret_tracepoints.c -llttng-ust
    gcc -shared -o fake_clock.so -fPIC fake_clock.c -ldl -pthread
    gcc -D_XOPEN_SOURCE=700 -o write_lttng write_lttng.c -ldl -llttng-ust -L. -l:ros2_tracepoints.so -l:ros2_caret_tracepoints.so -l:fake_clock.so