#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 문제의 조건으로 주어진 두 함수, 2차원 배열의 메모리 할당을 위한 함수

void arr_ij(int* sizeRow, int* sizeCol, int** pArr); // 나선형 배열을 만드는 함수
void print(int* row, int* col, int** pArr); // 만들어진 배열을 출력하는 함수
void memory(int** arr, int row, int col); // 2차원 메모리 할당 과정 일부에 쓰이는 함수

int main() {
	int** arr = NULL; //arr 값으로 NULL 저장
	int row, col, sizeRow, sizeCol;
	int result_1, result_2;
	printf("행의 수를 입력하세요.");
	result_1 = scanf("%d", &sizeRow);
	if (result_1 != 1 || sizeRow < 1 || sizeRow > 10000) {
		printf("1 이상의 정수만 입력 가능합니다.");
		return 0;
	}// 1~10000 사이의 정수가 입력되지 않았을 경우의 예외 처리

	printf("열의 수를 입력하세요.");
	result_2 = scanf("%d", &sizeCol);
	if (result_2 != 1 || sizeCol < 1 || sizeCol > 10000) {
		printf("1 이상의 정수만 입력 가능합니다.");
		return 0;
	}// 1~10000 사이의 정수가 입력되지 않았을 경우의 예외 처리
	

	row = sizeRow;
	col = sizeCol;// 의미상 구분한 두 변수일 뿐, 하나로 통일해도 문제가 되진 않는다.

	//만약 10000*10000일 경우, 메모리가 부족하여 문제가 발생할 수 있지만, 아래 메모리 할당 단계에서 이를 처리 후 종료시킬 수 있는 코드를 넣어둠.
	arr = (int**)malloc(sizeof(int*) * row);
	if (arr == NULL)
	{
		printf("메모리 할당 실패\n");
		exit(1);
	}// row 값에 따른 1차 메모리 할당
	//arr 자체를 바꾸는 것은 main에서, 각 행을 채우는 일은 memory()에서 진행하여 배우지 않은 삼중 포인터의 사용을 피함.

	memory(arr, row, col);
	arr_ij(&sizeRow, &sizeCol, arr);
	print(&row, &col, arr);

	for (int i = 0; i < row;i++) {
		free(arr[i]);
	}

	free(arr);// 메모리 해제 (행 배열 포인터까지 포함)
	return 0;
}

// 2차원 메모리 할당 과정 일부에 쓰이는 함수
void memory(int** arr, int row, int col) {
	for (int i = 0; i < row; i++) {
		arr[i] = (int*)malloc(sizeof(int) * col);// row마다 col 개수에 따른 메모리를 2차 할당
		if (arr[i] == NULL) {
			printf("메모리 할당 실패\n");
			exit(1);
		}
	}
}

// 나선형 배열을 만드는 함수
void arr_ij(int* sizeRow, int* sizeCol, int** pArr) {
	int top = 0;
	int bottom = *sizeRow - 1;
	int left = 0;
	int right = *sizeCol - 1; // 배열의 모서리를 이용하여 나선형 배열을 작성할 예정
	int count = 1;
	while (top <= bottom && left <= right) {
		for (int i = left; i <= right; i++) {
			pArr[top][i]= count;// C언어 3일차에서는 2차원 배열을 구현할 수 없어 1차원으로 흉내를 냈지만, 현재는 동적할당과 포인터를 사용하여 가능.
			count++;
		}// 첫 줄을 채우는 코드 (왼->오)
		top++;// 한 줄 내리기

		for (int i = top; i <= bottom; i++) {
			pArr[i][right] = count;
			count++;
		}// 오른쪽 맨 끝 줄을 채우는 코드 (위-> 아래)
		right--;// 한 줄 왼쪽으로 , 이미 채운 열을 제외하고, 다음 반복에서 처리될 영역을 한 칸 안으로 좁힘

		if (top <= bottom) {// 1줄짜리 배열일 경우, 아래 코드가 그대로 진행되면 이전 진행 결과가 새로운 결과에 덮이기 때문에 이를 방지하고자 작성한 코드
			for (int i = right; i >= left; i--) {
				pArr[bottom][i] = count;
				count++;
			}// 마지막 줄을 채우는 코드 (오-> 왼)
			bottom--;// 한 줄 위로  이미 채운 행을 제외하고, 다음 반복에서 처리될 영역을 한 칸 안으로 좁힘
		}

		if (left <= right) {// 1줄짜리 배열일 경우, 아래 코드가 그대로 진행되면 이전 진행 결과가 새로운 결과에 덮이기 때문에 이를 방지하고자 작성한 코드
			for (int i = bottom; i >= top; i--) {
				pArr[i][left] = count;
				count++;
			}//왼쪽 맨 끝 줄을 채우는 코드 
			left++;// 한 줄 오른쪽으로.
		}


	}
	}

// 만들어진 배열을 출력하는 함수
void print(int* row, int* col, int** pArr) {
	int max = (*row) * (*col);// arr_ij에서 count가 1부터 시작하므로 행과 열의 곱이 마지막 수이기 때문이다.
	int num = 1;
	while (max >= 10) {
		max = max / 10;
		num++;
	}// 배열의 마지막 수의 자릿수만큼 자릿수가 주어져야 나선형 배열이 출력되었을 때 의도대로 나오기 때문에 자릿수를 구하는 코드를 추가함.

	for (int i = 0; i < *row;i++) {
		for (int j = 0; j < *col; j++) {
			printf("%*d ",num, pArr[i][j]);// 2차원 배열을 출력하는 함수. 이미 메모리가 2차원 배열로 할당되어 있으므로 지난번 과제처럼 흉내낸 식이 아니어도 된다.
		}// %*d를 사용하는 것은 printf의 문법이므로 사용함.
		printf("\n");
	}
}