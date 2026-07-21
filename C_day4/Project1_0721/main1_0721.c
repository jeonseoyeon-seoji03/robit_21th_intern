#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct
{
	int grade;
	float score;
	char name[20];
}Stu; // 구조체 정의

void erase_buffer(void);
void sort_student(Stu list[], int n);
int name_dic(char a[], char b[]); // 버퍼 지우는 함수, 오름차순 정렬하는 함수, 이름 사전 순으로 분류하는 함수

int main() {
	Stu list[5];
	printf("5명의 학년, 성적, 이름을 입력하시오.\n");

	for (int i = 0; i < 5; i++) {
		printf("%d번째 학생의 학년을 입력하시오.",i+1);
		int result_1 = scanf_s("%d", &list[i].grade);
		if (result_1 != 1 || list[i].grade <= 0) {
			printf("1 이상의 정수를 입력해주세요.\n");
			erase_buffer();// 문자 오입력시의 무한 반복 현상을 막기 위한 함수
			i--;
			continue;
		}
		printf("%d번째 학생의 학점을 입력하시오.", i + 1);
		int result_2 = scanf_s("%f", &list[i].score);// f를 lf로 입력하여 오류 발생 (수정 완료)
		if (result_2 != 1 || list[i].score < 0|| list[i].score > 4.5) {
			printf("1 이상 4.5 이하의 실수를 입력해주세요.\n");
			erase_buffer();
			i--;
			continue;
		}
		printf("%d번째 학생의 이름을 입력하시오.", i + 1);
		int result_3 = scanf_s("%s", &list[i].name,sizeof(list[i].name));
		if (result_3 != 1) {
			printf("문자열을 입력해주세요.\n");
			erase_buffer();
			i--;
			continue;
		}
	}
	sort_student(list, 5); // 오름차순 정렬

	for (int i = 0; i < 5; i++) {
		printf("%d %.1f %s\n", list[i].grade, list[i].score, list[i].name);
	}
	return 0;// 결과 출력
}
void erase_buffer(void) {
	char ch;
	do {
		scanf_s("%c", &ch, 1);
	} while (ch != '\n');
}// 숫자를 입력해야하나, 문자 등을 입력한 경우, 무한 반복 오류가 나는 것을 방지하기 위해 작성한 함수

int name_dic(char a[], char b[]) {
	int i = 0; 
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return a[i] - b[i];
		}
		i++;
	}
	return a[i] - b[i];
}// 아스키코드를 이용한 함수로, a의 이름이 사전상 먼저일 경우 음수, 나중일 경우 양수, 같으면 0이다.

void sort_student(Stu list[], int n) {
	for (int i = 0; i < n-1; i++) { 
		for (int j = 0; j < n - 1 - i; j++) {// 반복할 때마다 맨 뒤에 와야할 군집이 정해지니 -i한다.
			int need_swap = 0;
			if (list[j].grade != list[j + 1].grade) {
				if (list[j].grade > list[j + 1].grade) {
					need_swap = 1; // 학년 비교-> 바꿀 필요성이 있는 경우 need_swap=1이 됨.
				}
			}
			else if (list[j].score != list[j + 1].score) {
				if (list[j].score > list[j + 1].score) {
					need_swap=1;
				}// 학년이 같을 경우, 학점 비교
			}
			else {
				
				int num = name_dic(list[j].name, list[j + 1].name);// 학년, 학점이 같을 경우 이름 사전순 비교
				if (num > 0) {
					need_swap = 1;
				}
			}

			if (need_swap == 1) {
				Stu swap = list[j];
				list[j] = list[j + 1];
				list[j + 1] = swap;// 바꿀 필요성이 존재하는 경우, 바꾸어준다.
			}
		}
	}
}
