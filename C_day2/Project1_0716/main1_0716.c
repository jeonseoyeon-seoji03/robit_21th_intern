#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
void star_1(int s);
void star_2(int s);
void star_3(int s);
void star_4(int s);

int main() {
	int size = 0;
	int type = 0;
	int result = 0;

	printf("사이즈와 종류를 입력하시오.");
	result = scanf("%d %d", &size, &type);
	if (result != 2 || size <= 0 || type > 4 || type < 0) {
		printf("사이즈는 1 이상, 종류는 1~4 범위 안에서만 선택 가능합니다.");
		return 0;
	}

	switch (type) {
	case 1:
		star_1(size);
		break;
	case 2:
		star_2(size);
		break;
	case 3:
		star_3(size);
		break;
	case 4:
		star_4(size);
		break;
	default:
		printf("1~4번의 종류만 입력 가능합니다.");
		break;
	}
	return 0;
}
void star_1(int s) {
	for (int i = 1; i <= s; i++) {
		int star = (i < s - i + 1) ? i : s - i + 1;
		for (int j = 1; j <= star; j++) {
			printf("*");
		}
		printf("\n");
	}
}
void star_2(int s) {
	int top = (s + 1) / 2;
	for (int i = 1; i <= s; i++) {
		int star = (i < s - i + 1) ? i : s - i + 1;
		for (int j = 1; j <= top-star; j++) {
			printf(" ");
		}
		for (int j = 1; j <= star; j++) {
			printf("*");
		}
		printf("\n");
	}
}
void star_3(int s) {
	int log = (s - 1) / 2; // 중심에서 가장 먼 곳
	for (int i = 1; i <= s; i++) {
		int d = (i - 1 < s - i) ? (i - 1) : (s - i);
		int dist = log - d; // 중심까지의 거리로 바꾸어주기
		int star = 2 * dist + 1; //별 개수는 중심까지의 거리*2+1
		int space = (s - star) / 2;// 공백 개수는 (사이즈-별 개수)/2
		for (int j = 1; j <= space; j++) {
			printf(" ");
		}
		for (int j = 1; j <= star; j++) {
			printf("*");
		}
		printf("\n");
	}
}
void star_4(int s) {
	int log = (s + 1) / 2; // 중심에서 가장 먼 곳
	int log_2 = (s % 2 == 0) ? log + 1 : log;
	for (int i = 1; i <= s; i++) {
		int d;// 짝수일 경우 대비, 중심점이 아닌 중심 구간을 만들 것임.
		if (i < log) {
			d = log - i;
		}
		else if (i > log_2) {//중심구간에서 두번째 중심점보다 큰 경우, 거리 구하기
			d = i - log_2;
		}
		else {
			d = 0; // 
		}
		int star = d + 1; //별 개수는 중심까지의 거리+1
		int space = (i - 1 < log - 1) ? (i - 1) : (log - 1);
		for (int j = 1; j <= space; j++) {
			printf(" ");
		}
		for (int j = 1; j <= star; j++) {
			printf("*");
		}
		printf("\n");
	}
}