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

    // MySQL ���� �ʱ�ȭ
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    printf("�̸��� �Է��ϼ���: ");
    scanf("%99s", name);
    printf("���̸� �Է��ϼ���: ");
    scanf("%d", &age);
    printf("ID �Է�: ");
    scanf("%49s", id);

    while (1) {
        printf("��й�ȣ �Է� (��ü �н����� ���̴� 8�� �̻�, Ư������, ��ҹ���, ���� ����): ");
        scanf("%49s", pw);
        printf("��й�ȣ Ȯ��: ");
        scanf("%49s", pwCheck);
        if (strcmp(pw, pwCheck) != 0) {
            printf("��й�ȣ�� ��ġ���� �ʽ��ϴ�. �ٽ� �Է��ϼ���.\n");
        } else {
            printf("����� ������ ������ �Ϸ�Ǿ����ϴ�.\n");

            // ����� �����͸� �����ͺ��̽��� �����ϴ� �Լ��� ���
            if (insert_user_data(conn, name, age, id, pw) == 0) {
                printf("����� ������ �����ͺ��̽��� ����Ǿ����ϴ�.\n");
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

    // MySQL ���� �ʱ�ȭ
    MYSQL *conn = init_mysql_connection(server, user, password, database);
    if (conn == NULL) {
        return;
    }

    while (count < LIMIT) {
        printf("���̵� �Է��ϼ���: ");
        scanf("%49s", id);
        printf("��й�ȣ�� �Է��ϼ���: ");
        scanf("%49s", pw);
        if (check_user_credentials(conn, id, pw)) {
            printf("�α��εǾ����ϴ�.\n");
            break;
        } else {
            printf("��й�ȣ�� Ʋ�Ƚ��ϴ�. �ٽ� �õ��ϼ���.\n");
        }
        count++;
    }
    close_mysql_connection(conn);
}
