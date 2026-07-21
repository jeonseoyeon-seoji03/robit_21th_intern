#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	char *item;
	int price;
}shop; // 구조체 정의

void erase_buffer(void);// 숫자 자리에 문자가 입력되었을 때 생기는 무한 반복 오류 방지를 위한 함수
void input_item(shop* list, int num); // 물건 이름과 가격을 입력하는 함수
int str_len(char* str);// 물건 이름에 대한 동적 할당을 위한 길이 측정 함수
void str_copy(char* a, char* b);// 임시로 저장해둔 문자열을 할당된 곳으로 옮기는 함수
char* search_name(void);// 물건 이름을 찾는 함수
int str_correct(char* a, char* b);// 찾고자 하는 물건 이름과 기존에 작성된 물건 이름을 비교하는 함수
int calc(shop* list, int num, char* name);// 물건의 이름끼리 일치하는 경우, 가격을 계산하기 위한 함수

int main() {
	int num = 0;
	char* name; // 함수 값을 *char의 형태로 반환할 예정.
	printf("입력: ");
	int result_1 = scanf("%d", &num);
	if (result_1 != 1||num<=0) {
		printf("1 이상의 정수만 입력 가능합니다.");
		return 0;// 입력받을 물건 개수 입력 및 예외 처리
	}
	shop* list = (shop*)malloc(sizeof(shop) * num); // 입력받을 물건 개수에 대한 구조체 배열의 메모리 할당 
	if (list == 0) {
		printf("메모리 할당 실패");
		return 0;// 메모리 할당 실패 예외 처리
	}
	for (int i = 0; i < num; i++) {
		printf("%d번째 상품과 가격을 작성하세요.",i + 1);
		input_item(list, i);// 상품명 및 가격 작성
	}
	printf("찾으시는 상품명을 작성하세요: ");
	name= search_name();// 찾는 상품명 작성
	int result_4= calc(list, num, name);// 찾는 상품명=기존 상품명 일치 시 계산하는 함수
	printf("출력: %d", result_4);// 총합 가격 출력

	for (int i = 0; i < num; i++) {
		free(list[i].item);
	}
	free(name);
	free(list);// 동적 할당된 메모리 해제
	return 0;
}

// 숫자 자리에 문자가 입력되었을 때 생기는 무한 반복 오류 방지를 위한 함수
void erase_buffer(void) {
	char ch;
	do {
		scanf_s("%c", &ch, 1);
	} while (ch != '\n');
}// 버퍼를 삭제하여 무한 반복을 예방하는 함수

// 물건 이름에 대한 동적 할당을 위한 길이 측정 함수
int str_len(char* str) {
	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}// 동적 할당을 위해 문자열의 길이를 재는 함수_언급되지 않은 외부 라이브러리 사용 금지 조건에 따라 직접 정의함.

// 임시로 저장해둔 문자열을 할당된 곳으로 옮기는 함수
void str_copy(char* a, char* b) {
	int i = 0;
	while (b[i] != '\0') {
		a[i] = b[i];
		i++;
	}
	a[i] = '\0';
}// 동적 할당된 메모리로 임시 저장된 문자열을 옮기기 위한 함수_언급되지 않은 외부 라이브러리 사용 금지 조건에 따라 직접 정의함

// 물건 이름과 가격을 입력하는 함수
void input_item(shop *list, int i) {
	char tem[200]; // 임시로 주어진 칸
	int result_2;
	do {
		result_2 = scanf_s("%s %d", tem, sizeof(tem), & list[i].price);// scanf_s에서 %s를 사용할 경우 버퍼 크기인 sizeof(tem)이 필요하는 사실을 오류 수정 과정에서 알게됨 (수정 완료)
		if (result_2 != 2) {
			printf("문자열, 숫자 순서대로 입력 가능합니다.\n");
			erase_buffer();// 가격에 문자가 들어오는 등의 잘못된 입력이 들어올 경우, 버퍼를 삭제하지 않으면 무한 반복을 하게됨. 해당 현상을 해결하는 함수.
		}// 문자열, 가격 입력 받는 코드
	} while (result_2 != 2);

	int item_len = str_len(tem);
	list[i].item = (char*)malloc(item_len + 1); // /0 자리를 위해 1를 더했다.
	if (list[i].item == 0) {
		printf("메모리 할당 실패\n");
		return;// 메모리 할당 실패 예외 처리
	}
	str_copy(list[i].item, tem);// 임시 저장된 곳에서 동적 할당된 메모리로 이동
}

// 물건 이름을 찾는 함수
char* search_name(void) {
	char tem[200]; // 임시로 주어진 칸
	int result_3;
	do {
		result_3 = scanf_s("%s", tem,sizeof(tem));
		if (result_3 != 1) {
			printf("문자열만 입력 가능합니다.\n");
			erase_buffer();
		}
	} while (result_3 != 1);

	int name_len = str_len(tem);
	char *name = (char*)malloc(name_len + 1); // /0 자리를 위해 1를 더했다.
	if (name == 0) {
		printf("메모리 할당 실패\n");
		exit(1);
	}
	str_copy(name, tem);
	return name;// 찾는 물건명을 char*로 반환
}

// 찾고자 하는 물건 이름과 기존에 작성된 물건 이름을 비교하는 함수
int str_correct(char* a, char* b) {
	int i = 0;
	while (a[i] != '\0' && b[i] != '\0') {
		if (a[i] != b[i]) {
			return 0; // 다른 경우 0을 반환함. 아래 calc에서 판단의 조건으로 쓰임.
		}
		i++;
	}
	return a[i] == '\0' && b[i] == '\0';// 같은 길이에서 끝났는지 확인 (하나만 끝난 경우의 다른 하나의 마지막 글자가 서로 다를 가능성 배제)
}

// 물건의 이름끼리 일치하는 경우, 가격을 계산하기 위한 함수
int calc(shop* list, int num, char* name) {
	int total = 0;
	for (int i = 0; i < num;i++) {
		if (str_correct(list[i].item, name)) {
			total += list[i].price;// 물건명이 찾고자하는 물건명과 일치하는 경우, 가격 합산
		}
	}
	return total;// 만약, 일치하는 이름이 없었을 경우, total의 초깃값이 0인채로 반환되므로 조건을 충족한다.
}
