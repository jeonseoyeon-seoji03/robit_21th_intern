//과제 3

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int year = 0;

	do {
		printf("년도를 입력하세요 : ");
		int result = scanf_s("%d", &year);
		if (result == 0) 
		{
			printf("숫자만 입력가능합니다.");
			char ch;
			do {
				scanf_s("%c", &ch, (unsigned int)(sizeof(ch))); //과제 1과 같이 버퍼 문제가 발생하지 않도록 조치함.
			} while (ch != '\n');
			continue;
		}
		break;
	} while (1);

	if (year % 400 == 0) {
		printf("%d년은 윤년입니다",year);
	}
	else if ((year % 4 == 0) && (year % 100 != 0)) {
		printf("%d년은 윤년입니다",year);
	}
	else {
		printf("%d년은 윤년이 아닙니다",year);
	}
	return 0;
}