//과제 7

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main() {
	int n = 0;
	int r = 0;
	int result = 0;
	printf("n과 r을 입력하세요.(공백으로 구분)");
	result = scanf_s("%d %d", &n, &r);
	if (result != 2 || n <= 0 || n>=21||r < 0) {
		printf("n은 20이하의 양의 정수만, r은 0 이상의 정수만 입력 가능합니다. 프로그램을 재실행하십시오.");
		return 0;
	}
	long long per = 0;
	long long per_re = 1;
	long long com = 0;
	long long com_re = 0;

	// 중복 순열 구하기
	if (r == 0) {
		per_re = 1;
	}else{
		for (int i = r; i > 0; i--) {
			per_re = per_re * n;
		}
	}
	long long r_result = 1;
	// 순열 구하기
	long long n_result = 1;
	long long n_r_result = 1;
	if (r > n) {
		printf("순열에서 뽑는 개수(r)는 전체(n)보다 많을 수 없습니다.\n순열 계산을 건너뜁니다.\n");
	}else{
		for (int i = n; i > 0; i--) {
			n_result = n_result * i;
		}
		if (n - r != 0) {
			for (int i = n - r; i > 0; i--) {
				n_r_result = n_r_result * i;
			}
		}
		else {
			n_r_result = 1;
		}

		per = n_result / n_r_result;
	}
	//조합 구하기
	n_result = 1;
	n_r_result = 1;
	
	if (r > n) {
		printf("조합에서 뽑는 개수(r)는 전체(n)보다 많을 수 없습니다.\n조합 계산을 건너뜁니다.\n");
	}
	else {
		for (int i = n; i > 0;i--) {
			n_result = n_result * i;
		}
		if (n - r != 0) {
			for (int i = n - r; i > 0; i--) {
				n_r_result = n_r_result * i;
			}
		}
		else {
			n_r_result = 1;
		}
		if (r != 0) {
			for (int i = r; i > 0; i--) {
				r_result = r_result * i;
			}
		}
		else {
			r_result = 1;
		}
		com = n_result / (n_r_result * r_result);
	}
	//중복조합 구하기
	n_result = 1;
	n_r_result = 1;
	r_result = 1;
	for (int i = n+r-1; i > 0;i--) {
		n_r_result = n_r_result * i;
	}
	if (n - 1 != 0) {
		for (int i = n - 1; i > 0; i--) {
			n_result = n_result * i;
		}
	}
	else {
		n_result = 1;
	}
	if (r != 0) {
		for (int i = r; i > 0; i--) {
			r_result = r_result * i;
		}
	}
	else {
		r_result = 1;
	}
	com_re = n_r_result / (n_result * r_result);

	if (r > n) {
		printf("순열과 조합을 계산하는데에 실패했습니다. \n");
		printf("중복순열의 값은 %lld, 중복조합의 값은 %lld입니다.\n",per_re, com_re);
	}
	else {
		printf("순열의 값은 %lld,중복순열의 값은 %lld, \n조합의 값은 %lld, 중복조합의 값은 %lld입니다.\n", per, per_re, com, com_re);
	}
}
 