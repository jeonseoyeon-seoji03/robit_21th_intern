#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main() {
	int num[8]= {0,};
	printf("입력\n");
	for (int i = 0; i < 8; i++) {
		printf("%d : ",i);
		int result= scanf("%d", &num[i]);
		if (result != 1) {
			printf("정수만 입력 가능합니다.\n");
			char ch; 
			do {
				scanf_s("%c", &ch, (unsigned)sizeof(ch));
			} while (ch != '\n');

			i--;
			continue; // 정수를 입력하지 않았을 경우의 예외처리
		}
	}
	printf("before sorting\n");
	for (int p = 0; p < 8; p++) {
		printf("%d  ", num[p]);
	}// 기존 배열 작성

	printf("\n");
	for (int i = 7; i > 0; i--) {
		int max_index = 0;
		
		for(int j=1; j<=i; j++)
		{
			if (num[j] > num[max_index]) {
				max_index = j;// 가장 큰 수의 인덱스를 기억
			}
		}
	
		int c = num[i];// 고정되지 않은 칸 중 맨 오른쪽 칸에 가장 큰 수를 대입
		num[i] = num[max_index];
		num[max_index] = c;
		for (int k = 0; k < 8; k++) {
			printf("%d  ", num[k]);
		}
		printf("\n");// 중간 과정 출력

	}
	printf("출력\n");
	for (int f = 0; f < 8; f++) {
		printf("%d : %d\n", f, num[f]);
	}
}

