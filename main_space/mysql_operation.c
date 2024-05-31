#include "mysql_operation.h"
#include <stdio.h>
#include <string.h>

const char *server = "localhost";
const char *user = "your_mysql_user";
const char *password = "your_mysql_password";
const char *database = "your_database_name";

// MySQL 연결을 초기화하는 함수
MYSQL* init_mysql_connection(const char *server, const char *user, const char *password, const char *database) {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return NULL;
    }

    if (mysql_real_connect(conn, server, user, password, database, 0, NULL, 0) == NULL) {
        fprintf(stderr, "mysql_real_connect() failed\n");
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

// MySQL 연결을 종료하는 함수
void close_mysql_connection(MYSQL *conn) {
    mysql_close(conn);
}

// 사용자 데이터를 데이터베이스에 삽입하는 함수
int insert_user_data(MYSQL *conn, const char *name, int age, const char *id, const char *password) {
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO usersInfo (username, userage, userid, password) VALUES ('%s', %d, '%s', '%s')", name, age, id, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "INSERT error: %s\n", mysql_error(conn));
        return 1;
    }

    return 0;
}

// 사용자의 로그인 정보를 확인하는 함수
int check_user_credentials(MYSQL *conn, const char *id, const char *password) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM usersInfo WHERE userid = '%s'", id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT error: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row == NULL) {
        mysql_free_result(res);
        return 0;
    }

    int result = strcmp(row[0], password) == 0;

    mysql_free_result(res);
    return result;
}