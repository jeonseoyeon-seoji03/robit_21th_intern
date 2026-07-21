// 기준시로부터 현재 시각까지의 초를 서로 빼어 차이를 구한 후 이를 다시 시 분 초로 변환하는 방법을 사용.

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	int year, month, day;
}DATE;
typedef struct {
	int hour, min, sec;
}TIME;// 구조체 정의

typedef struct {
	DATE date;
	TIME time;
}TIMESTAMP; // 날짜, 시간이 담긴 중첩 구조체 정의

void erase_buffer(void); // 정수 입력 자리에 문자를 입력했을 경우 발생하는 무한 반복 현상을 해결하기 위한 코드
void input_data(TIMESTAMP* ts); //현재 날짜와 시각을 입력하고, 조건에 맞는 입력인지 확인하는 함수
int day_month(int year, int month); // 월별로 바뀌는 마지막 날짜를 확인하기 위한 함수
int leap_year(int year); //윤년을 구별하는 함수
double total_day(int year, int month, int day); //기준시인 1년 1월 1일으로부터의 날짜를 구하는 함수
double trans_sec(TIMESTAMP ts); //기준시로부터의 날짜와 현재 시각을 초로 변환하여 모두 합하는 함수
void print_final(TIMESTAMP t1, TIMESTAMP t2); //두 현재 시각의 초를 빼어 그 차이를 구한 뒤, 다시 시 분 초로 바꾸는 함수
 
int main() {
	TIMESTAMP ts[2];// ts= timestamp
	input_data(ts);
	print_final(ts[0], ts[1]);
	return 0;
}

// 정수 입력 자리에 문자를 입력했을 경우 발생하는 무한 반복 현상을 해결하기 위한 코드
void erase_buffer(void) {
	char ch;
	do {
		scanf_s("%c", &ch, 1);
	} while (ch != '\n');
}

//현재 날짜와 시각을 입력하고, 조건에 맞는 입력인지 확인하는 함수
void input_data(TIMESTAMP* ts) {
	for (int i = 0; i < 2;i++) {
		printf("%d번째 현재 날짜와 현재 시각을 입력해주세요 (년,월,일,시,분,초) (공백으로 구분): \n",i+1);
		int result_1 = scanf("%d %d %d %d %d %d", &ts[i].date.year, &ts[i].date.month, &ts[i].date.day, &ts[i].time.hour, &ts[i].time.min, &ts[i].time.sec);
		if (result_1 != 6) {
			printf("날짜와 시각에 표기할 수 있는 정수만 입력 가능합니다.\n");
			erase_buffer();
			i--;
			continue;// 정수형 입력이 제대로 들어왔는지 확인 및 예외 처리
		}
		if (ts[i].date.year < 1) {
			printf("년도는 1 이상의 정수만 입력 가능합니다.\n");
			i--;
			continue; // 조건에 맞는 입력인지 확인 후 반복문 재실행하는 코드
		}
		if (ts[i].date.month < 1|| ts[i].date.month > 12) {
			printf("월은 1~12 사이의 정수만 입력 가능합니다.\n");
			i--;
			continue;
		}
		int max_day = day_month(ts[i].date.year, ts[i].date.month);// 월별로 바뀌는 마지막 날짜를 확인하기 위한 함수
		if (ts[i].date.day<1 || ts[i].date.day> max_day) {
			printf("%d월은 1~%d 사이의 정수만 입력 가능합니다.\n", ts[i].date.month, max_day);
			i--;
			continue;
		}
		if (ts[i].time.hour < 0 || ts[i].time.hour>23) {
			printf("시각은 0~23 사이의 정수만 입력 가능합니다.\n");
			i--;
			continue;
		}
		if (ts[i].time.min < 0 || ts[i].time.min>59) {
			printf("분은 0~59 사이의 정수만 입력 가능합니다.\n");
			i--;
			continue;
		}
		if (ts[i].time.sec< 0 || ts[i].time.sec>59) {
			printf("초는 0~59 사이의 정수만 입력 가능합니다.\n");
			i--;
			continue;
		}
	}

}

// 월별로 바뀌는 마지막 날짜를 확인하기 위한 함수
int day_month(int year, int month) {
	int day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && leap_year(year)) {
		return 29;//윤년일 때, 2월의 마지막 날짜를 바꾸어주기 위한 코드
	}
	return day[month - 1];// 배열 인덱스는 0부터 시작하기 때문에 입력받은 month에서 1을 빼야 한다.
}

//윤년을 구별하는 함수
int leap_year(int year) {
	if (year % 4 == 0 && (year % 100 != 0|| year % 400 == 0)) {
		return 1;
	}
	return 0;
}

//기준시인 1년 1월 1일으로부터의 날짜를 구하는 함수
double total_day(int year, int month,int day) {
	double days = 0;
	for (int y = 1; y < year; y++) {
		if (leap_year(y)) {
			days += 366; // 윤년일 경우, 366일 더함
		}
		else { days += 365; }
	}
	for (int m = 1; m < month; m++) {
		days += day_month(year, m);
	}
	days += day;
	return days;
}

//기준시로부터의 날짜와 현재 시각을 초로 변환하여 모두 합하는 함수
double trans_sec(TIMESTAMP ts) {
	double days = total_day(ts.date.year, ts.date.month, ts.date.day);
	double seconds = days * 86400;
	seconds += ts.time.hour * 3600;
	seconds += ts.time.min * 60;
	seconds += ts.time.sec;

	return seconds;
}

//두 현재 시각의 초를 빼어 그 차이를 구한 뒤, 다시 시 분 초로 바꾸는 함수
void print_final(TIMESTAMP t1, TIMESTAMP t2) {
	double s1 = trans_sec(t1);
	double s2 = trans_sec(t2);

	double final = 0;
	if (s1 >= s2) {
		final = s1 - s2;
	}
	else {
		final = s2 - s1;
	}// 두 현재 시각을 빼줌

	int final_sec = (int)final;// 나머지 연산은 정수에서만 할 수 있다는 점을 발견-> double 형을 int로 바꾸어줌 (두 현재 시각의 차이는 대부분 int 형으로 다룰 수 있으므로.)

	int h = final_sec / 3600;
	int m = (final_sec % 3600) / 60;
	int s = final_sec % 60;// 두 현재 시각의 차이를 시 분 초로 재변환함.

	printf("출력: %d시 %d분 %d초\n", h, m, s);
}