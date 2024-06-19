
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>


/**
 * 回调函数，用于处理查询结果。
 *
 * @param data 用户自定义数据，本函数中未使用。
 * @param argc 返回结果中的列数。
 * @param argv 返回结果中的行数据，每一列以字符串形式表示。
 * @param azColName 返回结果中每一列的名称。
 * @return 函数始终返回0。
 */
static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    static int lines = 0; // 静态变量，用于计数处理的行数
    
    // 遍历每一列，打印列名和对应的值
    for (i = 0; i < argc; i++) {
        printf("[%d] %s = %s\n", i, azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    lines++; // 行数递增
    printf("第%d行数据查询完毕...\n", lines); // 打印行处理信息
    return 0; // 函数结束，返回0
}

/**
 * 主函数：通过SQLite3库操作指定的数据库表。
 * 
 * @param argc 命令行参数数量。
 * @param argv 命令行参数数组。
 * @return 返回程序执行状态（0为成功，非0为错误）。
 */
int main(int argc, char *argv[]) {
    sqlite3 *db; // 数据库句柄
    char *errMsg = 0; // 错误信息缓冲区
    int rc; // 操作返回码

    // 检查命令行参数是否足够
    if (argc < 3) {
        fprintf(stderr, "使用方法: %s 数据库文件 表名\n", argv[0]);
        return 1;
    }

    // 从命令行参数中获取数据库文件名和表名
    const char *db_filename = argv[1];
    const char *table_name = argv[2];

    // 尝试打开数据库连接
    rc = sqlite3_open(db_filename, &db);
    if (rc) {
        // 打开失败，打印错误信息并返回
        fprintf(stderr, "无法打开数据库： %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        // 打开成功，打印提示信息
        fprintf(stdout, "成功打开数据库\n");
    }

    // 动态构建SELECT语句
    char *sql = malloc(strlen("SELECT * FROM ") + strlen(table_name) + 1);
    sprintf(sql, "SELECT * FROM %s;", table_name);
    
    // 执行SQL查询
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        // 查询出错，打印错误信息并释放错误信息缓冲区
        fprintf(stderr, "SQL错误： %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        // 查询成功，打印提示信息
        fprintf(stdout, "查询成功\n");
    }

    // 释放SELECT语句占用的内存
    free(sql);

    // 关闭数据库连接
    sqlite3_close(db);

    return 0;
}
