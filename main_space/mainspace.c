#include <stdio.h>
#include "mainspace.h"
#include "mysql_operation.h"
#include "registerLogin.h"

// ���� �޴� �Լ�
void mainspace() {
    int selectNumber = 0;
    while (1) {
        printf("1. ���� ���� �Է�\n");
        printf("2. ���� ��ȸ\n");
        printf("3. ���� ���� ����\n");
        printf("4. �α׾ƿ�\n");
        printf("���Ͻô� ������ ��ȣ�� �Է��ϼ���: ");
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
                printf("�α׾ƿ� �Ǿ����ϴ�.\n");
                return;
            default:
                printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
}

// ���� ������ �Է��ϰ�, DB�� bankInfo ���̺� �����ϴ� �Լ�
void inputAccount() {
    char bankName[50];
    char userPw[50];
    char bankNumber[100];
    char bankBalance[100];
    int count = 0;

    // MySQL ���� �ʱ�ȭ
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    printf("������ ������� �Է��ϼ���: ");
    scanf("%49s", bankName);
    printf("���¹�ȣ�� �Է��ϼ���('-' ����): ");
    scanf("%99s", bankNumber);
    printf("������ �ܾ��� �Է��ϼ���: ");
    scanf("%99s", bankBalance);

    while (count < LIMIT) {
        printf("����� ��й�ȣ�� �Է��ϼ���: ");
        scanf("%49s", userPw);

        // ��й�ȣ Ȯ�� (��: �α��ε� ������� ��й�ȣ�� ��ġ�ϴ��� Ȯ��)
        if (check_user_credentials(conn, "user_id", userPw)) { // "user_id"�� ���� �α��ε� ������� ID�� ���� �ʿ�
            char query[256];
            snprintf(query, sizeof(query), 
                     "INSERT INTO bankInfo (bankName, bankNumber, bankBalance) VALUES ('%s', '%s', '%s')", 
                     bankName, bankNumber, bankBalance);
            if (mysql_query(conn, query)) {
                fprintf(stderr, "INSERT error: %s\n", mysql_error(conn));
            } else {
                printf("���� ������ ����Ǿ����ϴ�.\n");
            }
            break;
        } else {
            printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �õ��ϼ���.\n");
        }
        count++;
    }

    close_mysql_connection(conn);
}

// ���� ������ ��ȸ�ϴ� �Լ�
void viewAccount() {
    char bankNumber[100];
    printf("��ȸ�� ���� ��ȣ�� �Է��ϼ���: ");
    scanf("%99s", bankNumber);

    // MySQL ���� �ʱ�ȭ
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
        printf("���� �����: %s\n", row[0]);
        printf("���� ��ȣ: %s\n", row[1]);
        printf("���� �ܾ�: %s\n", row[2]);
    } else {
        printf("���¸� ã�� �� �����ϴ�.\n");
    }

    mysql_free_result(res);
    close_mysql_connection(conn);
}

// ���� ������ �����ϴ� �Լ�
void deleteAccount() {
    char bankNumber[100];
    printf("������ ���� ��ȣ�� �Է��ϼ���: ");
    scanf("%99s", bankNumber);

    // MySQL ���� �ʱ�ȭ
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    char query[256];
    snprintf(query, sizeof(query), "DELETE FROM bankInfo WHERE bankNumber = '%s'", bankNumber);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "DELETE error: %s\n", mysql_error(conn));
    } else {
        printf("���� ������ �����Ǿ����ϴ�.\n");
    }

    close_mysql_connection(conn);
}
