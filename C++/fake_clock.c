#define _GNU_SOURCE
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <pthread.h>

// `clock_gettime()` のオリジナル関数
static int (*real_clock_gettime)(clockid_t, struct timespec *) = NULL;

// `txt` から取得するカスタムタイムスタンプ
static uint64_t fake_timestamp = 1738888888123456789UL;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void set_fake_timestamp(uint64_t timestamp) {
    pthread_mutex_lock(&lock);
    fake_timestamp = timestamp;
    fflush(stdout);
    pthread_mutex_unlock(&lock);
}


__attribute__((visibility("default")))
int clock_gettime(clockid_t clk_id, struct timespec *ts) {
 if (real_clock_gettime == NULL) {
    real_clock_gettime = dlsym(RTLD_NEXT, "clock_gettime");
    if (!real_clock_gettime) {
        fprintf(stderr, "Error: Failed to load original clock_gettime: %s\n", dlerror());
        return -1;
    }
}


    if (clk_id == CLOCK_MONOTONIC || clk_id == CLOCK_REALTIME) {
        fflush(stdout);

        if (pthread_mutex_lock(&lock) != 0) {
            fprintf(stderr, "Error: Failed to lock mutex\n");
            return -1;
        }

        ts->tv_sec = fake_timestamp / 1000000000;
        ts->tv_nsec = fake_timestamp % 1000000000;
        pthread_mutex_unlock(&lock);

        return 0;
    }

    return real_clock_gettime(clk_id, ts);
}
