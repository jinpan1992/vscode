#include <stdio.h>
#include <time.h>

int main() {
    time_t rawtime;
    struct tm *timeinfo;

    // 获取当前时间
    time(&rawtime);
    // 转换为本地时间
    timeinfo = localtime(&rawtime);

    // 打印时间
    printf("Current local time: %d-%02d-%02d %02d:%02d:%02d\n",
           timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

    return 0;
}
