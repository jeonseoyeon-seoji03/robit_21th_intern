#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int min = 0;
	int max = 0;
	int result_1 = 0;
	int result_2 = 0;
	int nono_num[10001] = {0,};
	int nono_final[10001] = { 0, };
	int count = 0;
	printf("min :");
	result_1 = scanf("%d", &min);
	if (result_1 != 1||min<1||min>10000) {
		printf("1~10000 사이의 정수만 입력가능합니다.");
		return 0;
	}
	printf("max :");
		result_2 = scanf("%d", &max);
	if (result_2 != 1||max<min||max>10000) {
		printf("1~10000 사이의 min보다 큰 정수만 입력가능합니다.");
		return 0;
	}

	for (int i = 1; i <= 10000;i++) {
		nono_num[i] = 1;
	}// 모두 제곱 ㄴㄴ수라고 가정한다.

	for (int p = 2; p * p <= 10000; p++) {
		for (int i = p * p; i <= 10000; i += p * p) {
			nono_num[i] = 0;
		}
	}
	for (int i = min; i <= max; i++) {
		if (nono_num[i]) {
			count++;
			printf("%d ", i);
		}
	}

	printf("\n제곱ㄴㄴ수: %d개\n", count);
	return 0;
}