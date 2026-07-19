#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int result_1 = 0;
int result_2 = 0;
int S_len(char a[]);
void find_Posi(char str[], char sub[]);
void clear_b();
int main() {
    char inputStr[100];// 널 문자 고려
    char subStr[100];

    printf("최대 99개 문자 입력 <inputStr> : ");
    result_1 = scanf("%99s", inputStr);// 최대 개수를 지정하여 99자를 초과하여 입력 시 오류가 나지 않도록 조치함.
    if (result_1 != 1) {
        printf("입력을 읽는 것에 실패하였습니다.\n");
        return 0;// 아예 아무 것도 못 읽는 경우 예외 처리
    }
    clear_b();//99자 이상 입력할 경우 프로그램이 중단되는 현상을 방지하기 위한 버퍼 삭제 기능
    printf("찾는 문자열 <subStr> : ");
    result_2 =scanf("%99s", subStr);
    if (result_2 != 1) {
        printf("입력을 읽는 것에 실패하였습니다.\n");
        return 0;
    }
    find_Posi(inputStr, subStr);
    clear_b();
    return 0;
}

//문자열 길이 구하기
int S_len(char a[]) {
    int len = 0;
    while (a[len] != '\0') {
        len++;
    }
    return len;
}

//찾는 문자열 위치 출력
void find_Posi(char str[], char sub[]) {
    int str_len = S_len(str);
    int sub_len = S_len(sub);
    int i, j;
    int match = 0; 
    int found = 0;

    for (i = 0; i <= str_len - sub_len; i++) {// 찾는 문자열이 들어갈 수 있는 마지막 위치까지 탐색
        match = 1;// 일치한다는 가정 하에 시작
        // 만약, 찾는 문자열의 길이가 입력된 문자열의 길이보다 크다고 하더라도, 반복문이 실행되지 않아 found도 0으로 남는다.
        for (j = 0; j < sub_len; j++) {// 찾는 문자열의 글자수만큼 i칸에서부터 구역을 정해 일치하는지 확인
            if (str[i + j] != sub[j]) {
                match = 0;
                break;
                //일치하지 않을 경우 2번 반복문 탈출
            }
        }

        if (match == 1) {
            printf("%s의 위치 : %d\n", sub, i + 1);//i가 0부터 시작하기 때문에 1을 추가해야한다. (사람은 1부터 읽기 때문)
            found = 1;
        }
    }

    if (found == 0) {
        printf("문자열을 찾을 수 없습니다.\n");
    }
}
void clear_b() {
    char c;
    do {
        scanf("%c", &c);
    } while (c != '\n'); // 앞선 C언어 과제에서도 사용했던 버퍼 비우기용 코드
}