#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // 예제에서 사용된 외부 라이브러리는 사용 가능하다는 안내를 받았습니다.

typedef struct {
	int x;
	int y;
}point;// 구조체 정의

void erase_buffer(void);// 버퍼를 지워 무한 반복 오류 방지하는 함수 
void input_point(point* list, int num);// 좌표 입력 함수
double distance(point a, point b);// 거리 구하는 함수
int far_point(point* list, int num, double* sum);// 가장 먼 좌표의 인덱스 찾기, 좌표 거리 총합 구하기

int main() {
	int num = 0;// 좌표 개수
	double total_sum = 0; // 좌표 거리들의 합
	printf("입력을 받을 좌표의 개수를 입력하시오: ");
	int result_1 = scanf("%d", &num);
	if (result_1 != 1 || num < 1) {
		printf("좌표의 개수는 1 이상의 정수만 입력 가능합니다.\n");
		return 0; // 조건에 맞지 않는 입력을 넣었을 때의 예외 처리
	}
	point *list = (point*)malloc(sizeof(point) * num);
	if (list == NULL) {
		printf("메모리 할당 실패\n");
		return 0;// 메모리 할당에 실패했을 경우의 예외 처리
	}
	input_point(list, num);// 좌표 입력
	int final_i = far_point(list, num, &total_sum);// 가장 먼 좌표의 인덱스 찾기, 좌표끼리의 거리 총합

	printf("가장 거리가 먼 좌표는 (%d,%d)이며, 다른 좌표의 거리 총합은 약 %.1lf입니다.\n", list[final_i].x, list[final_i].y, total_sum);// 결과 출력
	free(list);
	return 0;
}

void erase_buffer(void) {
	char ch;
	do {
		scanf_s("%c", &ch, 1);
	} while (ch != '\n');
}
void input_point(point* list, int num) {
	for (int i = 0; i < num; i++) {
		printf("%d번째 x y 좌표를 입력하세요. (공백으로 구분): ",i+1);
		int result_2 = scanf("%d %d", &list[i].x, &list[i].y);
		if (result_2 != 2) {
			printf("정수를 입력해주세요.\n");
			erase_buffer();// 문자를 입력했을 경우 무한 반복 문제를 해결하기 위한 함수 사용
			i--;
			continue;
		}

	}
}
double distance(point a, point b) {
	int m_x = a.x - b.x;
	int m_y = a.y - b.y;
	return sqrt((double)(m_x * m_x + m_y * m_y)); //math.h 라이브러리 사용
}
int far_point(point* list, int num, double* f_sum) {
	int far_index = 0;
	double max_sum = -1; // 좌표 간의 거리는 늘 0 또는 양수이므로 음수를 초깃값으로 두는 것이 안전할 것 같아 다음과 같이 설정하였다.

	for (int i = 0; i < num; i++) {
		double sum = 0;
		for (int j = 0; j < num; j++) {
			if (i == j) {
				continue;// 같은 좌표를 비교하는 것이므로 좌표 거리, 먼 좌표를 구하는 계산에서는 무의미하다. 따라서 넘긴다.
			}
			sum = sum + distance(list[i], list[j]);// 모든 좌표에서 가장 먼 좌표를 구하는 것이므로 다음과 같이 계산한다.
		}
		if (sum > max_sum) {
			max_sum = sum;
			far_index = i;// 가장 합이 높은 좌표를 가진 인덱스를 따로 저장한다.
		}
	}
	*f_sum = max_sum;
	return far_index;
}