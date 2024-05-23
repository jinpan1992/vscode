#include <stdio.h>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    static int lines = 0;
    
    for (i = 0; i < argc; i++) {
        printf("[%d] %s = %s\n", i, azColName[i], argv[i] ? argv[i] : "NULL");
    }
    lines++;
    printf("第%d行数据查询完毕...\n", lines);
    return 0;
}

int main(int argc, char *argv[]) {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;

    // 检查参数数量
    if (argc < 3) {
        fprintf(stderr, "使用方法: %s 数据库文件 表名\n", argv[0]);
        return 1;
    }

    const char *db_filename = argv[1]; // 数据库文件名从命令行参数获取
    const char *table_name = argv[2];  // 表名从命令行参数获取

    // 打开数据库连接
    rc = sqlite3_open(db_filename, &db);
    if (rc) {
        fprintf(stderr, "无法打开数据库： %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stdout, "成功打开数据库\n");
    }

    // 构建SQL查询语句
    char *sql = malloc(strlen("SELECT * FROM ") + strlen(table_name) + 1);
    sprintf(sql, "SELECT * FROM %s;", table_name);
    
    // 查询指定表中的所有记录
    rc = sqlite3_exec(db, sql, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL错误： %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        fprintf(stdout, "查询成功\n");
    }

    // 清理SQL语句
    free(sql);

    // 关闭数据库连接
    sqlite3_close(db);

    return 0;
}
