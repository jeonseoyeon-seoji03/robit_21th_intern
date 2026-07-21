#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void input_number(int** numbers, int* count);
void print_shape(int* numbers, int count);

int main() {
	int *numbers = NULL; // NULL 저장 (후에 동적 할당 할 때 사용할 예정)
	int count = 0;// 몇 개의 숫자를 배열에 추가했는지 확인하는 변수
	for (int i = 0; i < 12;i++) {
		input_number(&numbers, &count);// 각각의 주소를 보냄 (함수 내에서 두 값을 직접 바꾸기 위해서.)
		print_shape(numbers, count);// 주소와 값을 보냄
	}
	free(numbers);// 메모리 해체
	return 0;
}
//메모리 할당 및 숫자 입력 함수
void input_number(int** numbers, int* count) {
	if (*numbers == NULL) {
		*numbers = (int*)malloc(sizeof(int));
		if (*numbers == NULL)
		{
			printf("메모리 할당 실패\n");
			exit(1);
		}// 메모리 할당 실패 시의 예외 처리
	}
	else {
		*numbers = (int*)realloc(*numbers, sizeof(int)*(*count+1));//입력을 받을 때마다 메모리를 재할당함.
		if (*numbers == NULL)
		{
			printf("메모리 할당 실패\n");
			exit(1);
		}
	}

	int result_1;
	printf("숫자 배열에 사용할 음이 아닌 정수를 입력하시오 :");
	result_1 = scanf("%d", *numbers+*count);// 주소에 값 입력
	if (result_1 != 1 || *(*numbers + *count) < 0) {// 입력이 숫자가 아니거나, 음수인 경우 예외 처리하는 코드 *(*numbers + *count)가 입력 받은 수
		printf("음이 아닌 정수만 입력할 수 있습니다.");
		exit(1);
	}
	else {
		(*count)++;// count의 값을 증가
	}
}

//숫자 배열 출력
void print_shape(int* numbers, int count) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 4; col++) {
			int x = (row*4 + col) % count; //전체 칸을 처음부터 끝까지 순서대로 센 번호를 count로 나눈 나머지가 배열의 인덱스가 됨 (반복 구조이기 때문), 
			printf("%d", numbers[x]);
		}
		printf("\n");
	}
}