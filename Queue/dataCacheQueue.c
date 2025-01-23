#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_SIZE 10

// 定义队列结构
typedef struct {
    int buffer[MAX_SIZE]; // 数据缓存区
    int head;            // 队列头部索引
    int tail;            // 队列尾部索引
    int count;           // 队列中数据项数量
    sem_t semEmpty;      // 信号量，表示空闲位置的数量
    sem_t semFull;       // 信号量，表示已占用位置的数量
    pthread_mutex_t lock; // 互斥锁，保护队列操作
} DataCacheQueue;

// 初始化队列
void InitQueue(DataCacheQueue* queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;
    sem_init(&queue->semEmpty, 0, MAX_SIZE);
    sem_init(&queue->semFull, 0, 0);
    pthread_mutex_init(&queue->lock, NULL);
}

// 入队操作
void Enqueue(DataCacheQueue* queue, int data) {
    sem_wait(&queue->semEmpty); // 等待空闲位置
    pthread_mutex_lock(&queue->lock);
    queue->buffer[queue->tail] = data;
    queue->tail = (queue->tail + 1) % MAX_SIZE;
    queue->count++;
    pthread_mutex_unlock(&queue->lock);
    sem_post(&queue->semFull); // 增加一个已占用位置
}

// 出队操作
int Dequeue(DataCacheQueue* queue) {
    int data;
    sem_wait(&queue->semFull); // 等待数据项
    pthread_mutex_lock(&queue->lock);
    data = queue->buffer[queue->head]; 
    queue->head = (queue->head + 1) % MAX_SIZE;
    queue->count--;
    pthread_mutex_unlock(&queue->lock);
    sem_post(&queue->semEmpty); // 增加一个空闲位置
    return data;
}

// 销毁队列
void DestroyQueue(DataCacheQueue* queue) {
    sem_destroy(&queue->semEmpty);
    sem_destroy(&queue->semFull);
    pthread_mutex_destroy(&queue->lock);
}

// 查看队列中的所有数据
int ViewQueue(const char* title, DataCacheQueue* queue) {
    //int count = 0;
    printf("%s Queue contents:\n", title);
    pthread_mutex_lock(&queue->lock);
    for (int i = queue->head; i != queue->tail; i = (i + 1) % MAX_SIZE) {
        printf("%d ", queue->buffer[i]);
        //count++;
    }
    printf("\n");
    //count = queue->count;
    pthread_mutex_unlock(&queue->lock);
    return queue->count;
}

// 示例使用
int main() {
    DataCacheQueue queue;
    InitQueue(&queue);

    // 模拟生产者线程向队列中添加数据
    Enqueue(&queue, 1);
    Enqueue(&queue, 2);
    Enqueue(&queue, 22);
    
     // 添加数据后查看队列
    int count = ViewQueue("After Enqueue", &queue);

    // 模拟消费者线程从队列中取出数据
    printf("Dequeued: %d\n", Dequeue(&queue));
    printf("Dequeued: %d\n", Dequeue(&queue));
    
     // 取出数据后查看剩余数据
    count = ViewQueue("After Dequeue 2 items", &queue);
    printf("Remaining count: %d\n", count);

    DestroyQueue(&queue);
    return 0;
}
