#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int N = 0;
	int B = 0;
	int result_1 = 0;
	int result_2 = 0;
	int result_3 = 0;
	int num = 0;
	printf("N: ");
	result_1 = scanf("%d", &N);
	if (result_1 != 1||N<=0||N>100) {
		printf("100 이하의 양의 정수만 입력가능합니다.");
		return 0;
	}
	printf("B: ");
	result_2 = scanf("%d", &B);
	if (result_2 != 1 || B <= 0|| B > N) {
		printf("N 이하의 양의 정수만 입력가능합니다.");
		return 0;
	}
	printf("수열 입력: ");
	int A[100] = { 0, };
	for (int k = 0; k < N; k++) {
		result_3 = scanf("%d", &A[k]);
		if (result_3 != 1 || A[k] <= 0 || A[k] > N) {
			printf("1~%d 사이의 수만 입력가능합니다.",N);
			return 0;
		}
		for (int j = 0; j < k; j++) {
			if (A[k] == A[j]) {
				printf("숫자를 중복으로 입력할 수 없습니다.");
				return 0;
			}
		}
	}
	
	
	
	for (int i = 0; i < N; i++) {
		for (int j = i;N > j;j++) {
			int len = j - i + 1;// 인덱스가 0부터 시작하므로 0~2까지의 구간일 경우 길이는 3이지만 j-i만 할 경우 2가 나오기 때문.
				if (len % 2 != 0) {
					// b가 중앙값이 되려면 b보다 작은 값, 큰 값의 개수가 같아야하고, 탐색한 구간 안에 B가 있어야함.
					int small = 0;
					int big = 0;
					int exist = 0; // b를 구간 안에서 찾아내면 1, 못 찾으면 0
					for (int k = i; k <= j; k++) {
						// 여기서 A[k]를 보고 small, big, exist를 갱신
						if (A[k] == B) {
							exist = 1;
						}
						else if (A[k] > B) {
							big += 1;
						}
						else if (A[k] < B) {
							small += 1;
						}

						
					}
					if (exist == 1 && big == small) {
						num += 1;
					}
			}
		}
	}
	printf("중앙값이 %d인 부분 수열의 갯수 : %d", B, num);
}
