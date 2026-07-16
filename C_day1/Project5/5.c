// 과제 5

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int num = 0;
	int result = 0;
	printf("값을 입력하세요.");
	result = scanf_s("%d", &num);
	if (result != 1 || num <= 0) {
		printf("양의 정수만 입력 가능합니다. 프로그램을 재실행하십시오.");
		return 0;
		
	}
	int space_num = num; // 공백을 계산하기 위해 num값을 대입한 변수
	for (int l = 1; l <= num; l++) { //줄 별로 그리도록 하는 코드
		for (int i = 1; i < l + 1; i++) {
			printf("*");
		}
		for (int j = (space_num - 1) * 2; j > 0; j -= 1) {
			printf(" "); // 공백이 (num-1)*2만큼 존재함을 이용한 코드
		}
		for (int i = 1; i < l + 1; i++) {
			printf("*");
		}
		printf("\n");
		space_num -= 1; // num값은 변하면 안되기 때문에 만든 변수로 공백 코드를 위한 추가 계산을 시행한다.
	}

	int space_num2 = 1;
	for(int l=num-1; l>0; l--){
		for (int i = 1; i < l + 1; i++) {
			printf("*");
		}
		for (int j = space_num2* 2; j > 0; j --) {
			printf(" ");
		}
		for (int i = 1; i < l + 1; i++) {
			printf("*");
		}
		printf("\n");
		space_num2 += 1; //별이 감소하는 부분의 코드이다.
	}
}