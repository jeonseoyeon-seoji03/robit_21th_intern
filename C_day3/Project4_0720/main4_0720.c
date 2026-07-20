#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int main() {
	int N1 = 0;
	int result_1 = 0;
	int max = -999;
	int min = 999;
	int sum = 0;
	float avg = 0;

	do {
		printf("몇 개의 원소를 할당하시겠습니까? ");
		result_1 = scanf_s("%d", &N1);
		if (result_1 != 1 || N1 < 1) {
			printf("1 이상의 정수만을 입력할 수 있습니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch, 1);  // 문자를 입력했을 경우 뜨는 무한 반복 오류를 막기 위한 코드
			} while (ch != '\n');
		}
	} while (result_1 != 1 || N1 < 1); // 입력받은 열과 행이 조건에 맞는지 확인 후 프로그램 메인 기능 실행

	int* A = (int*)malloc(N1 * sizeof(int));
	if (A == 0) {
		printf("메모리 할당에 실패했습니다.\n");
		return 1;
	}
	// 정수형 데이터 입력
	for (int i = 0; i < N1; i++) {
		int result_2 = 0;
		printf("정수형 데이터 입력: ");
		result_2 = scanf_s("%d", &A[i]);

		if (result_2 != 1) {
			printf("정수형 데이터만을 입력할 수 있습니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch, 1);  // 문자를 입력했을 경우 뜨는 무한 반복 오류를 막기 위한 코드
			} while (ch != '\n');
			i--;
			continue;
			
		}
		sum = sum + A[i];// 합계 저장 코드
		if (A[i] > max) {
			max = A[i];
		}
		if (A[i] < min) {
			min = A[i];// 최대 최소 비교 코드
		}

	}
	avg = (float)sum / (float)N1;
	printf("최댓값: %d\n최솟값: %d\n전체합: %d\n평균: %.2lf\n",max, min, sum, avg); // 결과 출력

	free(A);
	return 0;

}