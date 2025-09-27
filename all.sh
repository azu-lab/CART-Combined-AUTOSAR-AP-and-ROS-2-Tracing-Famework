./clean.sh

./ROS2_conversion.sh

./aralog_conversion.sh

cd C++/

./build.sh

if [[ "$1" == "--display" ]]; then
    echo "Displaying trace data..."
    ./write_trace_data.sh --display
else
    echo "Running trace data generation..."
    ./write_trace_data.sh
fi


cd ..
