#include <stdio.h>  
#include <sys/time.h>  
#include <sys/types.h>  
#include <unistd.h>  
  
int main() {  
    struct timeval tv;  
    int ret;  
  
    // 设置定时器为3秒  
    while (1) {  
        tv.tv_sec = 3;  // 秒  
        tv.tv_usec = 0; // 微秒  
  
        // 调用select实现定时器  
        // 因为四个文件描述符集合都是NULL，所以select会阻塞直到超时  
        ret = select(0, NULL, NULL, NULL, &tv);  
        if (ret == -1) {  
            perror("select error");  
            break; // 如果有错误，退出循环  
        }  
  
        // select返回0表示超时  
        if (ret == 0) {  
            printf("hello\n");  
            fflush(stdout); // 确保输出被立即刷新  
        }  
    }  
  
    return 0;  
}
