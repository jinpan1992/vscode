// main.c  
#include <stdio.h>  
#include "swap.h"  
  
int main() {  
    int x, y;  
  
    printf("请输入第一个数字: ");  
    scanf("%d", &x);  
  
    printf("请输入第二个数字: ");  
    scanf("%d", &y);  
  
    printf("交换前的值:\n");  
    printf("x = %d\n", x);  
    printf("y = %d\n", y);  
  
    // 调用交换函数  
    swap(&x, &y);  
  
    printf("交换后的值:\n");  
    printf("x = %d\n", x);  
    printf("y = %d\n", y);  
  
    return 0;  
}