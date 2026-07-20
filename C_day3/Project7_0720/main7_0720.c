#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int str_correct(char a[], char b[]);
void print_space(int depth);

int main() {
	//변수 정의
	int tag_len = 20; // 태그 이름의 최대 길이
	int capacity = 10;// 스택의 초기 용량 (10개 초과시 늘리는 코드 추가 작성 예정)
	char* box;// 문자열 배열을 흉내내기 위한 1차원 배열
	int top = 0;// 스택에 쌓인 태그 개수
	char* input_stack; // HELLO 등을 담기위한 변수
	int input_capacity = 200; // HELLO 등의 문자열의 최대 길이
	int len = 0;

	// 메모리 할당 및 확인
	box = (char*)malloc(sizeof(char) * capacity * tag_len);
	if (box == 0) {
		printf("메모리 할당에 실패했습니다.");
		return 1;
	}
	input_stack = (char*)malloc(sizeof(char) * input_capacity);
	if (input_stack == 0) {
		printf("메모리 할당에 실패했습니다.");
		free(box);
		return 1;
	}

	//입력을 문자열로 만들기
	char ch;
	do {
		scanf_s("%c", &ch, 1);
		if (ch != '\n') {
			input_stack[len] = ch;
			len++;
		}
	} while (ch != '\n');
	input_stack[len] = '\0'; // 이전 과제들고 유사한 형태의 코드로 문자를 읽어내 문자열을 만들었습니다.
	
	int i = 0;
	while (i < len) {
		if (input_stack[i] == '<') {
			int closing = 0;// 닫힘 기호 확인하는 변수
			char tag_name[20];
			int j = 0;

			i++;
			if (input_stack[i] == '/')
			{
				closing = 1; //닫힘 기호 있을 경우 1
				i++;
			}


			while (input_stack[i] != '>') {
				tag_name[j] = input_stack[i];//태그 이름은 20자 이내로 가정
				i++;
				j++;
			}// 태그 내 글자를 옮기는 코드

			tag_name[j] = '\0';
			i++;
			if (closing == 1) {
				if (top == 0) {
					printf("오류가 발생하였습니다. 여는 태그 없이 닫는 태그가 존재합니다.\n");
					return 1;
				}
				else {
					char* top_tag = box + (top - 1) * tag_len;
					if (str_correct(top_tag, tag_name) == 0) {
						printf("오류가 발생하였습니다. 태그의 짝이 맞지 않습니다.\n");
						return 1;
					}
					else {
						top--;
						print_space(top);
						printf("</%s>\n", tag_name);
					}
				}
			}
			else {
				print_space(top);
				printf("<%s>\n", tag_name);
				if (top >= capacity) {
					capacity = capacity * 2;
					box = (char*)realloc(box, sizeof(char) * capacity * tag_len);
					if (box == 0) {
						printf("메모리 재할당에 실패했습니다.\n");
						return 1;
					}// 태그 개수가 10개 이상일 경우 재할당하는 코드
				}
				char* push_first = box + top * tag_len;
				int k = 0;
				while (tag_name[k] != '\0') {
					push_first[k] = tag_name[k];
					k++;
				}
				push_first[k] = '\0';

				top++;
			}
		}
		else {
			char text[200];
			int k = 0;

			while (i < len && input_stack[i] != '<') {
				text[k] = input_stack[i];
				i++;
				k++;
			}// 일반 텍스트를 읽는 코드
			text[k] = '\0';

			print_space(top);
			printf("%s\n", text);
		}

	}
	if (top != 0) {
		printf("오류가 발생하였습니다. 닫히지 않은 태그가 있습니다.\n");
		return 1;
	}
	return 0;
}
int str_correct(char a[], char b[]) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return 0;
		}
		i++;
	}
	if (a[i] == '\0' && b[i] == '\0') {
		return 1;
	}
	return 0;// 저번 과제에서 사용한 문자열 비교식과 유사하게 작성하였다.
}// 두 문자열이 동일한지 확인하는 코드

void print_space(int depth) {
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
}// 들여쓰기 하는 코드





