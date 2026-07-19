#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int check(char note[8]);
int main() {
	char mel[8];

	int re = 0;
	for (int i = 0; i < 8; i++) {
		printf("%d번째 음을 작성하세요.", i + 1);
		re= scanf(" %c", &mel[i]);
		if (re != 1||mel[i]!= 'c' && mel[i] != 'd' && mel[i] != 'e' && mel[i] != 'f' && mel[i] != 'g' && mel[i] != 'a' && mel[i] != 'b' && mel[i] != 'C') {
			printf("다장조의 음만 입력할 수 있습니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch, (unsigned)sizeof(ch));
			} while (ch != '\n');

			i--;// 다장조의 음이 아닌 문자를 입력할 경우의 예외 처리
		}
	}
	int result = check(mel);
	switch (result) { // 함수의 반환값을 토대로 결과를 출력함.
	case (1):
		printf("결과: ascending");
		break;
	case (2):
		printf("결과: descending");
		break;
	case (3):
		printf("결과: mixed");
		break;
	}
}

int check(char note[8]) {
	char ascend[8] = { 'c','d','e','f','g','a','b','C' };
	char descend[8] = { 'C','b','a','g','f','e','d','c' }; // 배열과 배열을 비교할 예정
	int  ascend_num = 1;
	int  descend_num = 1;
	for (int i = 0; i < 8; i++) {
		if (note[i] != ascend[i]) {
			ascend_num = 0;// 초깃값이 1인 변수의 값을 조건에 맞지 않을 때 0으로 바꿈으로서 아래에서 조건식을 거쳐 결과를 반환하게 됨.
		}
		if (note[i] != descend[i]) {
			descend_num = 0;
		}
	}
	if (ascend_num == 0 && descend_num == 0)
	{
		return 3;
	}
	else if(ascend_num != 0){
		return 1;
	}
	else if (descend_num != 0) {
		return 2;
	}
}