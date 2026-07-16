// 과제 1

#define _CRT_SECURE_NO_WARNINGS  // scanf를 다루셨고, #define _CRT_SECURE_NO_WARNINGS는 오류 목록에서도 안내하므로 사용하도록 하겠습니다.
#include <stdio.h>
int main()
{
	double num[5] = {0,};
	double max = -9999999;
	double min = 9999999; //max의 초깃값은 매우 작은 숫자, min의 초깃값은 매우 큰 숫자로 작성하여 비교 과정에서의 오류를 방지함.
	double sum = 0;
	for (int i = 0;i < 5;i++)
	{
		int result;
		printf("%d번째 실수를 입력하시오.", i + 1);
		result=scanf_s("%lf", &num[i]); 
		if (result == 0) { //scanf에서 반환된 값을 통해 실수가 입력되었는지 확인
			printf("실수가 정상적으로 입력되지 않았습니다.\n다시 입력해주세요.\n");
			char ch; // do-while을 활용해 버퍼가 이후 과정에 영향을 미치지 않게끔 하여 무한반복 문제를 해결함.
			do {
				scanf_s("%c", &ch, (unsigned)sizeof(ch));
			} while (ch != '\n');
			i -= 1;//continue를 통해 재반복되어도 문제가 생긴 순서부터 다시 시작하도록 작성함.
			continue;
		}
		
			sum = sum + num[i];
			if (num[i] > max) {
				max = num[i];
			}
			if (num[i] < min) {
				min = num[i];
			} // 평균 계산을 위한 합계, 최소, 최대 비교를 위한 코드
		
	}

	double avg = sum / 5;
	printf("---- 결과 ----\n");
	printf("평균은 %.6lf입니다\n", avg);
	printf("최댓값은 %.6lf입니다\n", max);
	printf("최솟값은 %.6lf입니다\n", min);

}