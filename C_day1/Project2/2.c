//과제 2
// 교육하지 않은 C언어 개념 사용 시 감점 사항에 따라 함수를 사용하지 않음
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int n = 0;
	int result;
	double fibo[50] = {0,}; // 정확한 값을 얻기 위해 50번째 수까지 구할 수 있도록 설정함
	fibo[0] = 0;
	fibo[1] = 1;  //1,2번째 수는 미리 입력함. (for문의 계산식을 시작하는 데에 필요.)
	
	do{
		printf("몇번째 피보나치 수를 출력할까요? 2 이상 50 이하의 정수를 입력하세요.\n");
		result= scanf_s("%d", &n);
		if (result == 0) {
			printf("정수가 아닌 기타 문자는 입력 불가 합니다.\n");
			char ch;
			do {
				scanf_s("%c", &ch,(unsigned int)(sizeof(ch))); //과제 1과 같이 버퍼 문제가 발생하지 않도록 조치함.
			} while (ch != '\n');
			continue;
		} // 문자를 입력할 경우의 예외 처리
		if (n <= 1 || n>50) {
			printf("2 이상, 50 이하의 정수만 입력 가능합니다.\n");
			continue;
		}// 범위를 벗어난 숫자를 입력한 경우의 예외 처리
	} while (n <= 1 || n > 50);
	
		for (int i = 2; i < n; i++) {
			fibo[i] = fibo[i - 1] + fibo[i - 2]; // for문을 이용한 피보나치 수열 공식
	}
		printf("%d번째 피보나치 수는 %.lf입니다.", n, fibo[n-1]);
		return 0;
}