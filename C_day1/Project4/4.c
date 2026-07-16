// 과제 4

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double first_num = 0;
	double second_num = 0;
	double result = 1;
	char arith;
	printf("Input Arithmetic Operation\nex)    3.4 * 8.5\n       2.9 - 5.4\n       3.9 * 8.0\n       3.9 ^ 8\n");
	printf("Input: ");
	int re= scanf("%lf %c %lf", &first_num, &arith, &second_num);
	if (re != 3) {
		printf("올바른 형식이 아닙니다. 프로그램을 재실행하십시오.");
		return 0;
	}
	if (arith == '+') {
		result = first_num + second_num;
		printf("%.2lf + %.2lf = %.2lf", first_num, second_num, result);
	}
	else if (arith == '-') {
		result = first_num - second_num;
		printf("%.2lf - %.2lf = %.2lf", first_num, second_num, result);
	}
	else if (arith == '*') {
		result = first_num * second_num;
		printf("%.2lf * %.2lf = %.2lf", first_num, second_num, result);
	}
	else if (arith == '/') {
		if (second_num == 0) {
			printf("분모는 0이 될 수 없습니다. 다시 입력해주세요.");
			return 0;
		}
		result = first_num / second_num;
		printf("%.2lf / %.2lf = %.2lf", first_num, second_num, result);
	}
	else if (arith == '^') {

		if ((second_num != (int)second_num) || second_num<0) {
			printf("현 계산기에서는 지수는 0 또는 양의 정수로만 입력 가능합니다.");
				return 0;
		}
		
		for (int i = 0; i < second_num; i++) {
			result = result * first_num;
		}
		printf("%.2lf ^ %.2lf = %.2lf", first_num, second_num, result);
	}
	else {
		printf("입력이 잘못되었습니다. 다시 입력해주세요.");
	}

	return 0;
}