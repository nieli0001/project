#ifndef MYSQL_OPERATIONS_H
#define MYSQL_OPERATIONS_H

#include "C:/Program Files/MySQL/MySQL Server 8.0/include/mysql.h"

// MySQL ���� ���� ���� ������ ����
extern const char *server;
extern const char *user;
extern const char *password;
extern const char *database;

// MySQL ������ �ʱ�ȭ�ϴ� �Լ�
MYSQL* init_mysql_connection(const char *server, const char *user, const char *password, const char *database);

// MySQL ������ �����ϴ� �Լ�
void close_mysql_connection(MYSQL *conn);

// ����� �����͸� �����ͺ��̽��� �����ϴ� �Լ�
int insert_user_data(MYSQL *conn, const char *name, int age, const char *id, const char *password);

// ������� �α��� ������ Ȯ���ϴ� �Լ�
int check_user_credentials(MYSQL *conn, const char *id, const char *password);

#endif // MYSQL_OPERATIONS_H
