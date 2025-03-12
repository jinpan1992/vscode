#include <stdio.h>
#include <string.h>

// 定义事件类型常量
#define EVENT_KEY_PRESS    0
#define EVENT_TIMER_TIMEOUT 1
#define EVENT_SERIAL_COMMAND 2
#define MAX_EVENTS         3

// 定义回调函数类型
typedef void (*CallbackFunc)(int event_type, void* data);

// 全局回调函数指针数组
CallbackFunc g_callbacks[MAX_EVENTS] = {NULL};

// 注册函数：将回调函数绑定到事件类型
void registerCallback(int event_type, CallbackFunc cb) {
    if (event_type >= 0 && event_type < MAX_EVENTS)
        g_callbacks[event_type] = cb;
}

// 事件触发器：模拟事件发生时的调用逻辑
void triggerEvent(int event_type, void* data) {
    if (g_callbacks[event_type]) {
        printf("[Trigger] Event %d occurred, data: %s\n", event_type, (char*)data);
        g_callbacks[event_type](event_type, data);
    }
}

// 用户定义的回调函数1：处理按键事件
void keyPressHandler(int event_type, void* data) {
    printf("[Handler] Key pressed: %s\n", (char*)data);
}

// 用户定义的回调函数2：处理定时器超时
void timerTimeoutHandler(int event_type, void* data) {
    printf("[Handler] Timer timeout: %s\n", (char*)data);
}

// 用户定义的回调函数3：处理串口命令
void serialCommandHandler(int event_type, void* data) {
    printf("[Handler] Serial command: %s\n", (char*)data);
}

int main() {
    // 注册回调函数
    registerCallback(EVENT_KEY_PRESS, keyPressHandler);
    registerCallback(EVENT_TIMER_TIMEOUT, timerTimeoutHandler);
    registerCallback(EVENT_SERIAL_COMMAND, serialCommandHandler);

    // 模拟事件触发
    triggerEvent(EVENT_KEY_PRESS, "Enter key pressed");
    triggerEvent(EVENT_TIMER_TIMEOUT, "5s timeout");
    triggerEvent(EVENT_SERIAL_COMMAND, "CMD:READ_DATA");

    return 0;
}
