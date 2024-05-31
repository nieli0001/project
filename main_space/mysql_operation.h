#ifndef MYSQL_OPERATIONS_H
#define MYSQL_OPERATIONS_H

#include "C:/Program Files/MySQL/MySQL Server 8.0/include/mysql.h"

// MySQL 연결 정보 전역 변수로 선언
extern const char *server;
extern const char *user;
extern const char *password;
extern const char *database;

// MySQL 연결을 초기화하는 함수
MYSQL* init_mysql_connection(const char *server, const char *user, const char *password, const char *database);

// MySQL 연결을 종료하는 함수
void close_mysql_connection(MYSQL *conn);

// 사용자 데이터를 데이터베이스에 삽입하는 함수
int insert_user_data(MYSQL *conn, const char *name, int age, const char *id, const char *password);

// 사용자의 로그인 정보를 확인하는 함수
int check_user_credentials(MYSQL *conn, const char *id, const char *password);

#endif // MYSQL_OPERATIONS_H
