#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int main() {
	int N1 = 0;
	int N2 = 0;
	int result_1 = 0;
	int count = 1;
	do {
		printf("행과 열을 입력: ");
		result_1 = scanf_s("%d %d", &N1, &N2);
		if (result_1 != 2 || N1 < 1 || N2 < 1 || N1 % 2 != 1 || N2 % 2 != 1) {
			printf("행과 열에는 1 이상의 홀수만을 입력할 수 있습니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch, 1);  // 문자를 입력했을 경우 뜨는 무한 반복 오류를 막기 위한 코드
			} while (ch != '\n');
		}
	} while (result_1 != 2 || N1 < 1 || N2 < 1 || N1 % 2 != 1 || N2 % 2 != 1); // 입력받은 열과 행이 조건에 맞는지 확인 후 프로그램 메인 기능 실행

	int* A = (int*)malloc(N1 * N2 * sizeof(int)); // 입력받은 N1,N2를 행렬 정의에 쓸 수 없으니, 동적 할당으로 진행
	if (A == 0) {
		printf("메모리 할당에 실패했습니다.\n");
		return 1;
	}
	// 변형된 나선형 배열 
	int total = N1 * N2;
	int c_row = (N1 - 1) / 2;
	int c_col = (N2 - 1) / 2; // 중심 찾기
	A[c_row * N2 + c_col] = count;// 중심점에 1 작성
	count++;

	for (int r = 1; count <= total; r++) {//r은 중심으로부터의 거리. count가 total을 넘어가면 모든 칸을 채웠다는 것임으로 반복을 종료한다.
		c_row += 1; //이전 마름모의 끝에서 아래로 한칸 이동
		c_col += 0;
		if (c_row >= 0 && c_row < N1 && c_col >= 0 && c_col < N2) {
			A[c_row * N2 + c_col] = count++;// 범위 안에 위치 할 경우, 값을 기록하고 count를 증가시킨다.
		}
		for (int s = 0; s < r - 1; s++) {// 대각선 방향으로 r-1번 이동(1단계에서 한 번 진행해서 온 위치이므로 r-1번 필요.)
			c_row += 1; c_col += 1;
			if (c_row >= 0 && c_row < N1 && c_col >= 0 && c_col < N2) {
				A[c_row * N2 + c_col] = count++;
			}
		}
		for (int s = 0; s < r; s++) {// 앞선 단계에서 이동에 영향을 미친 것이 없으므로 r로 진행한다.
			c_row -= 1; c_col += 1;// 위쪽 꼭짓점으로 향한다.
			if (c_row >= 0 && c_row < N1 && c_col >= 0 && c_col < N2) {
				A[c_row * N2 + c_col] = count++;
			}
		}
		for (int s = 0; s < r; s++) {
			c_row -= 1; c_col -= 1;// 왼쪽 꼭짓점으로 향한다.
			if (c_row >= 0 && c_row < N1 && c_col >= 0 && c_col < N2) {
				A[c_row * N2 + c_col] = count++;
			}
		}
		for (int s = 0; s < r; s++) {// 아래 꼭짓점으로 이동-> 다음번 마름모의 시작 위치가 됨.
			c_row += 1; c_col -= 1;
			if (c_row >= 0 && c_row < N1 && c_col >= 0 && c_col < N2) {
				A[c_row * N2 + c_col] = count++;
			}
		}
		// 이동한 좌표가 미리 지정한 범위를 벗어나는 경우, 값을 기록하고 count를 증가시키지 않고 지나간다.
	}
	for (int i = 0; i < N1; i++) {
		for (int j = 0; j < N2; j++) {
			printf("%2d ", A[i * N2 + j]);
		}
		printf("\n");
	}// 작성된 배열을 출력하는 기능
	free(A);
	return 0;
}