#include <stdio.h>  
#include <stdlib.h>  
#include <sqlite3.h>  
  
int main(int argc, char *argv[]) {  
    if (argc != 2) {  
        fprintf(stderr, "用法: %s <数据库文件名>\n", argv[0]);  
        return 1;  
    }  
  
    sqlite3 *db;  
    char *err_msg = 0;  
    int rc;  
  
    // 打开数据库（如果不存在则创建）  
    rc = sqlite3_open(argv[1], &db);  
    if (rc) {  
        fprintf(stderr, "无法打开数据库: %s\n", sqlite3_errmsg(db));  
        sqlite3_close(db);  
        return 1;  
    } else {  
        fprintf(stderr, "打开数据库成功\n");  
    }  
  
    // 准备SQL查询  
    const char *sql = "SELECT name FROM sqlite_master WHERE type='table';";  
  
    // 编译SQL语句  
    sqlite3_stmt *res;  
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);  
    if (rc != SQLITE_OK) {  
        fprintf(stderr, "SQL错误: %s\n", sqlite3_errmsg(db));  
        sqlite3_close(db);  
        return 1;  
    }  
  
    // 遍历查询结果  
    while (sqlite3_step(res) == SQLITE_ROW) {  
        // 获取表名称  
        const unsigned char *table_name = sqlite3_column_text(res, 0);  
        printf("表名称: %s\n", table_name);  
    }  
  
    // 清理并关闭  
    sqlite3_finalize(res);  
    sqlite3_close(db);  
  
    return 0;  
}
