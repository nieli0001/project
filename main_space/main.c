#include <stdio.h>
#include "registerLogin.h"
#include "mainspace.h"

int main() {
    registerlog();
    mainspace();
    return 0;
}

//1 : ȸ������ 2 : �α���
void registerlog() {
    int menuNum = 0;
    printf("1: �α���   2: ȸ������\n");
    while (1) {
        scanf("%d", &menuNum);
        if (menuNum == 1) {
            login();
            break;
        } else if (menuNum == 2) {
            createAccount();
            break;
        } else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }
}
