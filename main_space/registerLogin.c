#include "registerLogin.h"
#include "mysql_operation.h"
#include <stdio.h>
#include <string.h>

#define LIMIT 5

void createAccount() {
    char id[50];
    char pw[50];
    char pwCheck[50];
    char name[100];
    int age;

    // MySQL 연결 초기화
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    printf("이름을 입력하세요: ");
    scanf("%99s", name);
    printf("나이를 입력하세요: ");
    scanf("%d", &age);
    printf("ID 입력: ");
    scanf("%49s", id);

    while (1) {
        printf("비밀번호 입력 (전체 패스워드 길이는 8자 이상, 특수문자, 대소문자, 숫자 포함): ");
        scanf("%49s", pw);
        printf("비밀번호 확인: ");
        scanf("%49s", pwCheck);
        if (strcmp(pw, pwCheck) != 0) {
            printf("비밀번호가 일치하지 않습니다. 다시 입력하세요.\n");
        } else {
            printf("사용자 계정의 생성이 완료되었습니다.\n");

            // 사용자 데이터를 데이터베이스에 삽입하는 함수를 사용
            if (insert_user_data(conn, name, age, id, pw) == 0) {
                printf("사용자 정보가 데이터베이스에 저장되었습니다.\n");
            }
            break;
        }
    }
    close_mysql_connection(conn);
}

void login() {
    int count = 0;
    char id[50];
    char pw[50];

    // MySQL 연결 초기화
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    while (count < LIMIT) {
        printf("아이디를 입력하세요: ");
        scanf("%49s", id);
        printf("비밀번호를 입력하세요: ");
        scanf("%49s", pw);
        if (check_user_credentials(conn, id, pw)) {
            printf("로그인되었습니다.\n");
            break;
        } else {
            printf("비밀번호가 틀렸습니다. 다시 시도하세요.\n");
        }
        count++;
    }
    close_mysql_connection(conn);
}
