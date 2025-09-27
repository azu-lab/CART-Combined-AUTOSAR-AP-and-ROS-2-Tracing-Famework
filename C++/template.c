#define _GNU_SOURCE
#define TRACEPOINT_DEFINE

#include "ros2_tracepoints.h"
#include "ros2_caret_tracepoints.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>
#include <dlfcn.h>
#include <lttng/tracepoint.h>



// `set_fake_timestamp()` の関数ポインタ
extern void set_fake_timestamp(uint64_t);

static int (*real_clock_gettime)(clockid_t, struct timespec *) = NULL;

int count = 0;

uint64_t convert_to_unix_ns(const char *timestamp) {
    struct tm tm_time;
    memset(&tm_time, 0, sizeof(struct tm));

    // `HH:MM:SS FFFFFFFF` のフォーマットから時刻とナノ秒部分を取得
    int year, month, day, hours, minutes, seconds;
    uint64_t fractional_ns;

    if (sscanf(timestamp, "%d/%d/%d %d:%d:%d %lu", &year, &month, &day, &hours, &minutes, &seconds, &fractional_ns) != 7) {
        fprintf(stderr, "Error parsing timestamp: %s\n", timestamp);
        return 0;
    }
    

    // **現在の日付を UTC で取得**
    time_t now = time(NULL);
    struct tm *current_tm = gmtime(&now);  // UTC の日付を取得
    if (!current_tm) {
        fprintf(stderr, "Error getting UTC time\n");
    return 0;
    }

    // **`tm_time` に取得した日付と `HH:MM:SS` をセット**
    tm_time.tm_year =  year - 1900;  // 年
    tm_time.tm_mon =  month - 1;      // 月
    tm_time.tm_mday =  day;           // 日
    tm_time.tm_hour = hours;
    tm_time.tm_min = minutes;
    tm_time.tm_sec = seconds;
    tm_time.tm_isdst = 0;  // 夏時間無効化

    // **UNIX時間 (秒単位) に変換**
    time_t epoch_sec = timegm(&tm_time);  // UTC の UNIX 時間
    if (epoch_sec == -1) {
        fprintf(stderr, "Error converting to epoch time\n");
        return 0;
    }

    // **UNIX時間 (ナノ秒単位) を計算**
    uint64_t unix_ns = (uint64_t)epoch_sec * 1000000000L + fractional_ns;

    unix_ns = unix_ns - 32400 * 1000000000L; // 9時間分の秒数を引く

    return unix_ns;
}


// "HH:MM:SS FFFFFFFF" 形式のタイムスタンプファイルを読み込んでunix_ns_arrayに格納する関数
void load_timestamp_file_conversion(const char *filepath, uint64_t *unix_ns_array, size_t max_size) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char timestamp[256];
    for (size_t i = 0; i < max_size; i++) {
        if (fgets(timestamp, sizeof(timestamp), file) == NULL) {
            break; // EOF or error
        }
        timestamp[strcspn(timestamp, "\n")] = 0; // 改行を削除
        unix_ns_array[i] = convert_to_unix_ns(timestamp);
    }
    fclose(file);
}



void load_timestamp_file(const char *filepath, uint64_t *unix_ns_array, size_t max_size) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    usleep(5000000);

    char line[256];
    for (int i = 0; i < 5000 && i < max_size; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            break; // EOF or error
        }
        line[strcspn(line, "\n")] = 0; 
        unix_ns_array[i] = strtoull(line, NULL, 10);
    }
    fclose(file);
}

int main() {

    // init tracepoint events
    size_t max_size = 20000;
    uint64_t unix_ns1[max_size];
    load_timestamp_file("../output/output_server_tracepoints_timestamps.txt", unix_ns1, max_size);

    int j = 0;
    set_fake_timestamp(unix_ns1[j]);
{
 
// INSERT1
}

//  send tracepoint events

{

  // INSERT2
}



// receive tracepoint events
    j = 0;

    uint64_t unix_ns2[max_size];
    load_timestamp_file("../output/output_client_tracepoints_timestamps.txt", unix_ns2, max_size);
    set_fake_timestamp(unix_ns2[j]);

 

    {

    // INSERT3
    }

// ROS 2 tracepoint events
    j = 0;

    uint64_t unix_ns3[max_size];
    load_timestamp_file_conversion("../output/output_ros2_timestamps.txt", unix_ns3, max_size);
    set_fake_timestamp(unix_ns3[j]);

    {

    // INSERT4
    }

 
    
 return 0;
}
