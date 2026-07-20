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
		if (result_1 != 2 || N1 < 1 || N2 < 1) {
			printf("행과 열에는 1 이상의 정수만을 입력할 수 있습니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch, 1);  // 문자를 입력했을 경우 뜨는 무한 반복 오류를 막기 위한 코드
			} while (ch != '\n');
		}
	} while (result_1 != 2 || N1 < 1 || N2 < 1); // 입력받은 열과 행이 조건에 맞는지 확인 후 프로그램 메인 기능 실행

	int* A = (int*)malloc(N1 * N2 * sizeof(int)); // 입력받은 N1,N2를 행렬 정의에 쓸 수 없으니, 동적 할당으로 진행
	if (A == 0) {
		printf("메모리 할당에 실패했습니다.\n");
		return 1;
	}
	// 나선형 배열 작성 시작
	int top = 0;
	int bottom = N1 - 1;
	int left = 0;
	int right = N2 - 1; // 모서리를 이용하여 계산할 예정.

	while (top <= bottom && left <= right) {
		for (int i = left; i <= right; i++) {
			A[top* N2 +i] = count;// 행*(전체 열의 개수)+열로 지정하면 1차원 배열로 2차원 배열을 따라할 수 있다.
			count++;
		}// 첫 줄을 채우는 코드 (왼->오)
		top++;// 한 줄 내리기

		for (int i = top; i <= bottom; i++) {
			A[i*N2+right] = count;
			count++;
		}// 오른쪽 맨 끝 줄을 채우는 코드 (위-> 아래)
		right--;// 한 줄 왼쪽으로 , 이미 채운 열을 제외하고, 다음 반복에서 처리될 영역을 한 칸 안으로 좁힘
		
		if (top <= bottom) {// 1줄짜리 배열일 경우, 아래 코드가 그대로 진행되면 이전 진행 결과가 새로운 결과에 덮이기 때문에 이를 방지하고자 작성한 코드
			for (int i = right; i >= left; i--) {
				A[bottom * N2 + i] = count;
				count++;
			}// 마지막 줄을 채우는 코드 (오-> 왼)
			bottom--;// 한 줄 위로  이미 채운 행을 제외하고, 다음 반복에서 처리될 영역을 한 칸 안으로 좁힘
		}
		
		if (left <= right) {// 1줄짜리 배열일 경우, 아래 코드가 그대로 진행되면 이전 진행 결과가 새로운 결과에 덮이기 때문에 이를 방지하고자 작성한 코드
			for (int i = bottom; i >= top; i--) {
				A[i * N2 + left] = count;
				count++;
			}//왼쪽 맨 끝 줄을 채우는 코드 
			left++;// 한 줄 오른쪽으로.
		}
		

	}// 위 과정을 조건 달성 시까지 계속 반복하면 숫자가 나선형으로 순환하는 2차원 배열을 만들 수 있다.

	for (int i = 0; i < N1;i++ ) {
		for (int j = 0; j < N2; j++) {
			printf("%2d ", A[i * N2 + j]);
		}
		printf("\n");
	}// 2차원 배열을 흉내낸 것을 출력하는 코드

	free(A);
	return 0;
}