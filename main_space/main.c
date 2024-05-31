#include <stdio.h>
#include "registerLogin.h"
#include "mainspace.h"

int main() {
    registerlog();
    mainspace();
    return 0;
}

//1 : 회원가입 2 : 로그인
void registerlog() {
    int menuNum = 0;
    printf("1: 로그인   2: 회원가입\n");
    while (1) {
        scanf("%d", &menuNum);
        if (menuNum == 1) {
            login();
            break;
        } else if (menuNum == 2) {
            createAccount();
            break;
        } else {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
        }
    }
}
