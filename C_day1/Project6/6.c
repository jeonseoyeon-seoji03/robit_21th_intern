// 과제 6

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int n = 0;
	int result = 0;
	printf("값을 입력하세요.");
	result = scanf_s("%d", &n);
	if (result != 1 || n <= 0) {
		printf("양의 정수만 입력 가능합니다. 프로그램을 재실행하십시오.");
		return 0;
	}
	
	for (int i = 1; i <= n; i++)// i번째 별을 그리도록 함.
	{
		for (int j = 1;j <= i; j++) {
			for (int k = 0; k < i - j; k++) {
				printf(" "); // 왼쪽 공백 출력
			}

			for (int p = 0; p < 2 * j - 1; p++) {
				if (j == 1 || j == i || p == 0 || p == 2 * j - 2) {
					printf("*");
				}
				else {
					printf(" ");
				}// 별, 별 사이의 공백 출력
			}
			printf("\n");
		}

		for (int p = 0; p < n - i;p++) {
			printf("\n");
		} //빈 줄 출력.
	}
}
