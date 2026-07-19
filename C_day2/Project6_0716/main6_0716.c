#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int S[21] = { 0, }; // 함수 사용 예정이라 전역 배열 사용
void add(int x);
void remove_X(int x);
int check(int x);
int correct(char a[], char b[]);
void toggle(int x);
void all_0();
void empty_0();
void printS();

int main() {
	char command[10];
	int x = 0;
	int result_1 = 0;
	int r_2 = 0;
	printf("연산을 선택하세요. (1 <= x <= 20)");
	printf("\nadd X\nremove X\ncheck X\ntoggle X\nall 0\nempty 0\n\n");

	while (1) {
		printf("input: ");
		result_1 = scanf("%s %d", command, &x);
		if (result_1 != 2 || x < 0 || x>20) {//all 0, empty 0의 입력 문제를 해결하기 위해 0을 추가함. 이후 과정에 0은 영향을 미치지 않으므로 해당 사항을 유지함.
			printf("입력 양식에 맞게 입력해주세요. 숫자는 1~20 사이의 수만 입력 가능합니다.\n");
			continue;
		}// 입력 양식 및 조건 확인
		if (correct(command, "add")) {
			add(x);
			printS();
		}
		else if (correct(command, "remove")) {
			remove_X(x);
			printS();
		}
		else if (correct(command, "check")) {
			r_2=check(x);
			printf("%d\n", r_2);
			printS();
		}
		else if (correct(command, "toggle")) {
			toggle(x);
			printS();
		}
		else if (correct(command, "all")) {// 비교하는 command에서는 0를 읽지 않았기 때문.
			all_0();
			printS();
		}
		else if (correct(command, "empty")) {// 비교하는 command에서는 0를 읽지 않았기 때문.
			empty_0();
			printS();
		}
		else {
			printf("입력 양식이 잘못 되었습니다.\n"); //command에 없는 양식 입력 시 뜨는 안내
			continue;
		}
		
	}
	return 0;
}

int correct(char a[], char b[]) {
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
	return 0;
}// 두 문자열이 같으면 1, 다르면 0 반환

// 20가지 수의 존재 여부를 20개의 인덱스에 넣을 예정.
void add(int x) {
	S[x] = 1;// 존재하는 경우에도 계속 1이기 때문에 괜찮다.
}
void remove_X(int x) {
	S[x] = 0; // 없어도 계속 0이기 때문에 괜찮다.
}
int check(int x) {
	return S[x];
}
void toggle(int x) {
	if (S[x] == 1) {
		S[x] = 0;
	}
	else {
		S[x] = 1;
	}
}
void all_0() {
	for (int i = 1; i <= 20; i++) {
		S[i] = 1;
	}
}
void empty_0() {
	for (int i = 1; i <= 20; i++) {
		S[i] = 0;
	}
}
void printS() {
	int i;
	printf("집합 : { ");
	for (i = 1; i <= 20; i++) {
		if (S[i] == 1) {
			printf("%d, ",i);
			
		}
	}
	printf("}\n");
}
