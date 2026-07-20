#include <stdio.h>
int main() {
	int sand[5][5] = { 0 };
	int count = 1;
	int i_dist = 0;
	int j_dist = 0; // 가운데 행, 열인 2에서 얼마나 떨어져있는지 확인하기 위한 변수 

	for (int i = 0; i < 5; i++) {
		if (i >= 2) {
			i_dist = i - 2;
		}
		else {
			i_dist = 2 - i;
		}// 절댓값 함수를 못 쓰는 관계로 위와 같이 작성.
		for (int j = 0; j < 5; j++) {
			if (j >= 2) {
				j_dist = j - 2;
			}
			else {
				j_dist = 2 - j;
			}

			if (i_dist >= j_dist) {
				sand[i][j] = count;
				count++; // 중앙에서부터의 행의 거리보다 중앙에서부터의 열의 거리가 같거나 이보다 작은 경우, 0이 아닌 숫자가 들어갈 수 있다는 규칙이 존재한다.
			}// count를 통해, 순서대로 숫자를 작성하였다.
		}
	}

	for (int k = 0; k < 5; k++) {
		for(int p = 0; p < 5; p++) {
			printf("%2d  ", sand[k][p]);
			
		}// 만들어진 2차원 배열을 출력하는 코드이다.
		printf("\n");
	}
}

