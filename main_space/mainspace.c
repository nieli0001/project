#include <stdio.h>
#include "mainspace.h"
#include "mysql_operation.h"
#include "registerLogin.h"

// 메인 메뉴 함수
void mainspace() {
    int selectNumber = 0;
    while (1) {
        printf("1. 계좌 정보 입력\n");
        printf("2. 계좌 조회\n");
        printf("3. 계좌 정보 삭제\n");
        printf("4. 로그아웃\n");
        printf("원하시는 서비스의 번호를 입력하세요: ");
        scanf("%d", &selectNumber);

        switch (selectNumber) {
            case 1:
                inputAccount();
                break;
            case 2:
                viewAccount();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
                printf("로그아웃 되었습니다.\n");
                return;
            default:
                printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }
}

// 계좌 정보를 입력하고, DB의 bankInfo 테이블에 저장하는 함수
void inputAccount() {
    char bankName[50];
    char userPw[50];
    char bankNumber[100];
    char bankBalance[100];
    int count = 0;

    // MySQL 연결 초기화
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    printf("계좌의 은행명을 입력하세요: ");
    scanf("%49s", bankName);
    printf("계좌번호를 입력하세요('-' 제외): ");
    scanf("%99s", bankNumber);
    printf("계좌의 잔액을 입력하세요: ");
    scanf("%99s", bankBalance);

    while (count < LIMIT) {
        printf("사용자 비밀번호를 입력하세요: ");
        scanf("%49s", userPw);

        // 비밀번호 확인 (예: 로그인된 사용자의 비밀번호와 일치하는지 확인)
        if (check_user_credentials(conn, "user_id", userPw)) { // "user_id"는 실제 로그인된 사용자의 ID로 변경 필요
            char query[256];
            snprintf(query, sizeof(query), 
                     "INSERT INTO bankInfo (bankName, bankNumber, bankBalance) VALUES ('%s', '%s', '%s')", 
                     bankName, bankNumber, bankBalance);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "INSERT error: %s\n", mysql_error(conn));
            } else {
                printf("계좌 정보가 저장되었습니다.\n");
            }
            break;
        } else {
            printf("비밀번호가 일치하지 않습니다. 다시 시도하세요.\n");
        }
        count++;
    }

    close_mysql_connection(conn);
}

// 계좌 정보를 조회하는 함수
void viewAccount() {
    char bankNumber[100];
    printf("조회할 계좌 번호를 입력하세요: ");
    scanf("%99s", bankNumber);

    // MySQL 연결 초기화
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT bankName, bankNumber, bankBalance FROM bankInfo WHERE bankNumber = '%s'", bankNumber);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "SELECT error: %s\n", mysql_error(conn));
        close_mysql_connection(conn);
        return;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "mysql_store_result() failed: %s\n", mysql_error(conn));
        close_mysql_connection(conn);
        return;
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(res))) {
        printf("계좌 은행명: %s\n", row[0]);
        printf("계좌 번호: %s\n", row[1]);
        printf("계좌 잔액: %s\n", row[2]);
    } else {
        printf("계좌를 찾을 수 없습니다.\n");
    }

    mysql_free_result(res);
    close_mysql_connection(conn);
}

// 계좌 정보를 삭제하는 함수
void deleteAccount() {
    char bankNumber[100];
    printf("삭제할 계좌 번호를 입력하세요: ");
    scanf("%99s", bankNumber);

    // MySQL 연결 초기화
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM bankInfo WHERE bankNumber = '%s'", bankNumber);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "DELETE error: %s\n", mysql_error(conn));
    } else {
        printf("계좌 정보가 삭제되었습니다.\n");
    }

    close_mysql_connection(conn);
}
