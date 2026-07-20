#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
	int N1 = 0;
	int result_1 = 0;
	int count = 1;
	do {
		printf("행과 열이 될 N을 입력: ");
		result_1 = scanf_s("%d", &N1);
		if (result_1 != 1 || N1 < 1) {
			printf("행과 열에는 1 이상의 정수만을 입력할 수 있습니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch, 1);  // 문자를 입력했을 경우 뜨는 무한 반복 오류를 막기 위한 코드
			} while (ch != '\n');
		}
	} while (result_1 != 1 || N1 < 1); // 입력받은 숫자가 조건에 맞는지 확인 후 프로그램 메인 기능 실행

	int* A = (int*)malloc(N1 * N1 * sizeof(int)); // 입력받은 N1를 행렬 정의에 쓸 수 없으니, 동적 할당으로 진행
	if (A == 0) {
		printf("메모리 할당에 실패했습니다.\n");
		return 1;
	}
	// 대각선 행렬 프로그램(행+열=i번째 대각선이라는 규칙이 존재함을 이용)

	int group = 2 * N1 - 2; //몇번째 대각선까지 존재하는지 계산
	for (int i = 0; i <= group; i++) {// i번 대각선 그룹의 칸을 채운다.
		for (int row = 0; row <N1; row++) {
			int col = i - row; // 행과 열을 합쳤을 때 i가 나오는 규칙이 존재하기 때문에 이러한 식이 나온다.
			if (col >= 0 && col < N1) {// 행은 모든 범위를 훑지만, 열은 주어진 범위만 훑게함으로써 대각선을 채움
				A[row * N1 + col] = count;// 행*전체 행의 개수+열 규칙 이용
				count++;
			}
		

		}
	}
	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N1; j++) {
			printf("%2d  ", A[i * N1 + j]);
		}
		printf("\n");
}
	free(A);
	return 0;
}

