#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int N1 = 0;
	int N2 = 0;
	int result_1 = 0;
	int count = 1;
	do{
		printf("행과 열을 입력: ");
		result_1 = scanf_s("%d %d", &N1, &N2);
		if (result_1 != 2||N1<1||N2<1) {
			printf("행과 열에는 1 이상의 정수만을 입력할 수 있습니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch, 1);  // 문자를 입력했을 경우 뜨는 무한 반복 오류를 막기 위한 코드
			} while (ch != '\n');
		}
	} while (result_1 != 2 || N1 < 1 || N2 < 1); // 입력받은 열과 행이 조건에 맞는지 확인 후 프로그램 메인 기능 실행
	
	int* A = (int*)malloc(N1 * N2 * sizeof(int));
	int* B = (int*)malloc(N2 * N1 * sizeof(int)); // 입력받은 N1,N2를 행렬 정의에 쓸 수 없으니, 동적 할당으로 진행
	// C언어 수업에서 진행하지 않은 항목은 사용하지 못하므로 이중포인터를 사용할 수 없다. 따라서 1차원 배열로 2차원 배열을 흉내낼 것이다,
	if (A == 0) {
		printf("메모리 할당에 실패했습니다.\n");
		return 1;
	}
	if (B == 0) {
		printf("메모리 할당에 실패했습니다.\n");
		return 1;
	}

	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N2; j++) {
			A[i * N2 + j] = count; // 행 번호*열의 개수+열 속 위치가 1차원 배열 속의 [i][j]이다.
			count++;
			printf("%d ", A[i * N2 + j]);// 1차원 배열에서 2차원 배열을 흉내낼 예정.
		}
		printf("\n");
	}

	count = 0;
	printf("\n");

	for (int i = 0; i < N2; i++) {
		for (int j = 0; j < N1; j++) {
			B[i * N1 + j] = A[j * N2 + i];//B[i * N1 + j]는 B[i][j], A[j * N2 + i]는 A[j][i]를 나타낸다.
			printf("%2d ", B[i * N1 + j]);
		}
		printf("\n");
	}

	free(A);
	free(B);
	return 0;
	
}