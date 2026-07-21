#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int str_len(char* str); // 문자열의 길이를 재는 함수
void str_copy(char* a, char* b); //문자열을 다른 변수에 옮겨주는 함수
char* input_sentence(); //문자열을 입력하고 메모리를 동적할당하는 함수
char* rever_sentence(char* str); //입력된 문자열을 거꾸로 출력할 수 있게끔 역으로 정렬하는 함수
char find_fre(char* str); // 최다 등장 문자를 찾아내는 함수

int main() {
	char* sentence = input_sentence();
	printf("입력한 문장: %s\n", sentence);

	char* reverse_sentence= rever_sentence(sentence);
	printf("반대로 전환된 문장: %s\n", reverse_sentence);

	char high_char = find_fre(sentence);
	printf("최다 등장 문자: %c\n", high_char);

	free(sentence);
	free(reverse_sentence);//메모리 해제
	return 0;
}

// 문자열의 길이를 재는 함수
int str_len(char* str) {
	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

//문자열을 다른 변수에 옮겨주는 함수
void str_copy(char* a, char* b) {
	int i = 0;
	while (b[i] != '\0') {
		a[i] = b[i];
		i++;
	}
	a[i] = '\0';
}

//문자열을 입력하고 메모리를 동적할당하는 함수
char* input_sentence() {
	char tem[200]; // 임시로 주어진 칸
	printf("문장을 입력하세요: ");
	char* result_1 = fgets(tem, sizeof(tem), stdin);
	if (result_1 == NULL) {// 수업 시간에 다룬 라이브러리의 함수여서 사용함, 문자열 입력을 받음.
		printf("입력 오류\n");
		exit(1);
	}//예외 처리
	int len = str_len(tem);
	if (len > 0 && tem[len - 1] == '\n') {
		tem[len - 1] = '\0';//개행문자가 있을 경우 '\0'로 바꾸어주기 위함.
		len--;
	}
	char* sentence = (char*)malloc(len + 1);
	if (sentence == 0)
	{
		printf("메모리 할당 실패\n");
		exit(1);
	}//메모리 동적 할당 및 예외 처리
	str_copy(sentence, tem);// 임시 저장소에서 동적 할당된 메모리로 옮겨줌

	return sentence;//문자열을 반환함.
}

//입력된 문자열을 거꾸로 출력할 수 있게끔 역으로 정렬하는 함수
char* rever_sentence(char*str) {
	int len = str_len(str);
	char* result = (char*)malloc(len + 1);
	if (result == 0)
	{
		printf("메모리 할당 실패\n");
		exit(1);
	}// 메모리를 동적할당 한 후, 할당되지 않았을 경우의 예외 처리
	int j = 0;
	for (int i = len - 1; i >=0; i--) {// '\0'을 제외하고 역으로 정렬할 수 있도록 len-1부터 시작함.
		result[j] = str[i];
		j++;
	}// 주어진 문자열을 역으로 정렬함.
	result[len] = '\0';// 역으로 변환된 문자열엔 없으므로 추가

	return result;// 역변환 문자열 반환
}

// 최다 등장 문자를 찾아내는 함수
char find_fre(char* str) {
	int count[256] = { 0 };
	char* p = str;
	while ((unsigned char)*p != '\0') {// 음수가 나올 때의 오류를 방지하기 위해 unsigned char 변환을 사용함.
		if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z')) {
			count[(unsigned char)*p]++; // 공백과 특수문자는 세지 않도록 조건을 추가함. 
		}
		p++;
	}//아스키코드를 이용하여 특정 문자가 몇 회 나왔는지 기록

	char high_char = 0;
	int high_count = 0;
	for (int i = 0; i < 256;i++) {
		if (count[i] > high_count) {
			high_count = count[i];
			high_char = (char)i;// 제일 많이 나온 문자의 인덱스를 문자로 변환함.
		}
	}
	return high_char;// 최다 등장 문자를 반환함.
}