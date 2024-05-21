#include <stdio.h>  
#include <stdlib.h>  
#include "cJSON.h"  
  
int main() {  
    // 创建一个空的JSON对象  
    cJSON *root = cJSON_CreateObject();  
  
    // 在JSON对象中添加"username"字段  
    cJSON_AddItemToObject(root, "username", cJSON_CreateString("shebei"));  
  
    // 在JSON对象中添加"deviceId"字段  
    cJSON_AddItemToObject(root, "deviceId", cJSON_CreateString("2084491"));  
  
    // 将JSON对象转换为字符串并打印  
    char *json_string = cJSON_Print(root);  
    printf("%s\n", json_string);  
  
    // 释放内存  
    free(json_string);  
    cJSON_Delete(root);  
  
    return 0;  
}
