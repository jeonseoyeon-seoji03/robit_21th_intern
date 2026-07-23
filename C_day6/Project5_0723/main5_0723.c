#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char country[30];
    char province[30];
    char city[30];
    char dis[30];
} Address;

typedef struct {
    int number;
    char name[50];
    int score;
    Address address;
} Student;

typedef struct {
    Student* list;
    int count;
    int capacity;
} memory; // 동적 배열을 위한 구조체

void memory_init(memory* r);//메모리 초기화
void memory_big(memory* r);//메모리 재할당
void memory_free(memory* r);// 메모리 해제

int only_number(char* str);//입력된 문자열에 숫자만 존재하는지 확인하는 함수
int only_name(char* str);//입력된 문자열에 쉼표가 없는지 확인하는 함수
int str_len(char* str);//문자열 길이 측정하는 함수
void str_copy(char* c1, char* c2);//문자열 대입하는 함수
int str_cmp(char* a, char* b);//어떤 문자가 사전순으로 앞서는지 확인하는 함수
void remove_last(char* str);//개행 문자를 '\0'로 바꿔주는 함수
int str_t_num(char* str);//문자열을 정수로 변환하는 함수

void get_line(char* prompt, char* buf, int size); //문자열을 입력받고 개행문자를 제거하는 함수
int input_number(char* prompt);//숫자가 들어올 때까지 반복하며 정수로 변환 및 반환하는 함수
int input_score(char* prompt);//숫자 입력 함수에 점수 범위 제한을 둔 함수
void input_name(char* prompt, char* dest, int size);//문자열 입력 및 조건 확인 함수
void input_address(Address* addr);// 주소 입력

void print_student(Student* s);//학생 1명의 정보를 출력
void print_all(memory* r);//저장된 모든 학생 목록 출력

void swap_student(Student* a, Student* b);//학생 데이터 맞바꾸는 함수
void sort_by_number(memory* r);//학번 기준 오름차순 정렬
void sort_by_name(memory* r);
void sort_by_score(memory* r);
char* get_address(Address* a, int field);//주소에 간결하게 접근하기 위한 함수
void sort_by_address(memory* r, int field);//주소 항목 속 데이터의 사전순 오름차순 정렬

void search_by_number(memory* r);//학번 검색하는 함수
void search_by_score(memory* r);//성적 검색하는 함수
void search_by_address(memory* r, int field);//주소 검색하는 함수

void add_student(memory* r);//새로운 학생 추가하는 함수
void delete_student(memory* r);//학생 삭제하는 함수

void save_file(memory* r);//파일 저장하는 함수
void load_file(memory* r);//파일 불러오는 함수
int next_field(char* line, int* pos, char* dest, int max);//쉼표 기준으로 읽는 위치를 구분하면서 추출하는 함수

void print_menu(void);//메인 메뉴 선택 화면 출력
void sort_menu(memory* r);//선택에 따라 정렬 함수를 호출해주는 함수
void search_menu(memory* r);//선택에 따라 검색 함수를 호출해주는 함수

int main(void) {
    memory r;
    memory_init(&r);

    int ch;
    char st[10];

    while (1) {
        print_menu();
        get_line("선택: ", st, sizeof(st));
        if (!only_number(st)) {
            printf("숫자를 입력해주세요.\n");
            continue;
        }// 메뉴와 안내 문구를 출력하고 예외 처리도 함.

        ch = str_t_num(st);//정수로 변환

        if (ch == 1) {
            add_student(&r);
        }
        else if (ch == 2) {
            delete_student(&r);
        }
        else if (ch == 3) {
            sort_menu(&r);
        }
        else if (ch == 4) {
            search_menu(&r);
        }
        else if (ch == 5) {
            print_all(&r);
        }
        else if (ch == 6) {
            save_file(&r);
        }
        else if (ch == 7) {
            load_file(&r);
        }
        else if (ch == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }
        else {
            printf("잘못된 입력입니다.\n\n");
        }
    }

    memory_free(&r); // 메모리 해제
    return 0;
}

//메모리 초기화
void memory_init(memory* r) {
    r->capacity = 4;//초기 용량을 4로 설정해둠
    r->list = (Student*)malloc(r->capacity * sizeof(Student));// 용량에 맞춰 할당
    if (r->list == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }// 메모리 할당 실패 시 예외 처리
    r->count = 0;// 저장된 학생 수 0으로 초기화
}

//메모리 재할당
void memory_big(memory* r) {
    r->capacity *= 2;//용량을 두배로 늘릴 예정
    Student* temp = (Student*)realloc(r->list, r->capacity * sizeof(Student));
    if (temp == NULL) {
        printf("메모리 재할당 실패\n");
        exit(1);
    }//재할당 예외 처리
    r->list = temp; // 할당 실패를 대비하여 temp에 잠시 두었다가 list에 둠
}

// 메모리 해제
void memory_free(memory* r) {
    free(r->list);
    r->list = NULL;
    r->count = 0;
    r->capacity = 0;
}

//입력된 문자열에 숫자만 존재하는지 확인하는 함수
int only_number(char* str) {
    if (str[0] == '\0') {
        return 0;
    }//'\0' 있는 경우의 예외 처리
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }//문자가 0~9사이의 문자가 아니면 0 반환 (실패했다는 뜻)
    return 1;//숫자로만 이뤄진 경우(성공) 1 반환
}

//입력된 문자열에 쉼표가 없는지 확인하는 함수
int only_name(char* str) {
    if (str[0] == '\0') return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ',') return 0;
    }
    return 1;
}// 나중에 파일 만들 때 구분하는 역할로 쓰이는 쉼표가 이름이나 주소에 들어가지 않도록 함
//성공하면 1, 실패하면 0 반환

//문자열 길이 측정하는 함수
int str_len(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }// 끝날 때까지 길이 측정
    return len;
}

//문자열 대입하는 함수
void str_copy(char* c1, char* c2) {
    int i = 0;
    while (c2[i] != '\0') {
        c1[i] = c2[i];
        i++;
    }// c1에 c2의 값을 복사
    c1[i] = '\0';// 복사과정에서 '\0' 안 들어가니 넣어준다.
}

//어떤 문자가 사전순으로 앞서는지 확인하는 함수
int str_cmp(char* a, char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {// 끝에 도달하지 않을 때까지 반복
        if (a[i] != b[i]) {// 다른 글자가 나오는 경우, 아스키 코드 차이 계산
            return a[i] - b[i];
        }
        i++;
    }
    //한 쪽 문자열이 먼저 끝난 경우에도 아스키 코드 차이 계산
    return a[i] - b[i];
}

//개행 문자를 '\0'로 바꿔주는 함수
void remove_last(char* str) {
    int len = str_len(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

//문자열을 정수로 변환하는 함수
int str_t_num(char* str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; i++) {// 한 글자 씩 반복
        result = result * 10 + (str[i] - '0');// 10을 곱해 자릿수 올려주고, 문자를 숫자로 바꿔서 더해줌. '1'과 '0'의 차이는 1이기 때문.
    }
    return result;
}

//문자열을 입력받고 개행문자를 제거하는 함수
void get_line(char* p, char* b, int size) {
    printf("%s", p);
    fgets(b, size, stdin);// 개행문자까지 포함하여 입력받음
    remove_last(b);// '\0'으로 교체
}

//숫자가 들어올 때까지 반복하며 정수로 변환 및 반환하는 함수
int input_number(char* p) {
    char s_num[20];
    while (1) {
        get_line(p, s_num, sizeof(s_num));//문자열 입력 받음
        if (only_number(s_num)) {//숫자로만 구성되어있는지 확인
            return str_t_num(s_num);//정수로 바꿔서 반환
        }
        printf("숫자만 입력해주세요.\n");
    }
}

//숫자 입력 함수에 점수 범위 제한을 둔 함수
int input_score(char* p) {
    int score;
    while (1) {
        score = input_number(p);
        if (score >= 0 && score <= 100) {
            return score;
        }// 점수 범위 체크 및 반환
        printf("0~100 사이의 점수를 입력해주세요.\n");
    }
}

//문자열 입력 및 조건 확인 함수
void input_name(char* p, char* d, int size) {
    char str[100];
    while (1) {
        get_line(p, str, sizeof(str));
        if (only_name(str) && str_len(str) < size) {// 쉼표 없고 길이 기준에 맞는지 확인
            str_copy(d, str);// 조건 통과 시 복사
            return;
        }
        printf("제한 범위 내에서 빈 값, ','가 들어가지 않은 올바른 값을 입력해주세요. \n");
    }
}

// 주소 입력
void input_address(Address* addr) {
    input_name("나라: ", addr->country, sizeof(addr->country));
    input_name("도: ", addr->province, sizeof(addr->province));
    input_name("시: ", addr->city, sizeof(addr->city));
    input_name("구: ", addr->dis, sizeof(addr->dis));
}

//학생 1명의 정보를 출력
void print_student(Student* s) {
    printf("번호: %-5d 이름: %-10s 성적: %-3d 주소: %s,%s,%s,%s\n",
        s->number, s->name, s->score,
        s->address.country, s->address.province,
        s->address.city, s->address.dis);
}// -는 보기 편하게 작성한 것입니다.

//저장된 모든 학생 목록 출력
void print_all(memory* r) {
    if (r->count == 0) {
        printf("등록된 학생이 없습니다.\n\n");
        return;
    }//0명일 경우의 예외 처리

    for (int i = 0; i < r->count; i++) {
        print_student(&r->list[i]);
    }// 포인터를 전달하여 출력
    printf("\n");
}

//학생 데이터 맞바꾸는 함수
void swap_student(Student* a, Student* b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

//학번 기준 오름차순 정렬
void sort_by_number(memory* r) {
    for (int i = 0; i < r->count - 1; i++) {
        for (int j = 0; j < r->count - 1 - i; j++) {
            if (r->list[j].number > r->list[j + 1].number) {
                swap_student(&r->list[j], &r->list[j + 1]);
            }
        }
    }
}

// 사전순 오름차순 정렬
void sort_by_name(memory* r) {
    for (int i = 0; i < r->count - 1; i++) {
        for (int j = 0; j < r->count - 1 - i; j++) {
            if (str_cmp(r->list[j].name, r->list[j + 1].name) > 0) {
                swap_student(&r->list[j], &r->list[j + 1]);
            }//양수일 경우, 사전상 뒤이기 때문에 자리를 바꿔야 함.
        }
    }
}

//성적 기준 오름차순 정렬
void sort_by_score(memory* r) {
    for (int i = 0; i < r->count - 1; i++) {
        for (int j = 0; j < r->count - 1 - i; j++) {
            if (r->list[j].score > r->list[j + 1].score) {
                swap_student(&r->list[j], &r->list[j + 1]);
            }
        }
    }
}// 점수에 의한 버블정렬

//주소에 간결하게 접근하기 위한 함수
char* get_address(Address* a, int field) {
    if (field == 0) {
        return a->country;
    }
    if (field == 1) { 
        return a->province; 
    }
    if (field == 2) {
        return a->city;
    }
    if (field == 3)
    {
        return a->dis;
    }
}

//주소 항목 속 데이터의 사전순 오름차순 정렬
void sort_by_address(memory* r, int field) {
    for (int i = 0; i < r->count - 1; i++) {
        for (int j = 0; j < r->count - 1 - i; j++) {
            char* a = get_address(&r->list[j].address, field);
            char* b = get_address(&r->list[j + 1].address, field);
            if (str_cmp(a, b) > 0) {
                swap_student(&r->list[j], &r->list[j + 1]);
            }//양수이면 사전상 뒤이므로 바뀌어야함
        }
    }
}

//학번 검색하는 함수
void search_by_number(memory* r) {
    int num = input_number("검색할 번호: ");
    int found = 0;// 성공 여부 확인하게 해줄 변수
    for (int i = 0; i < r->count; i++) {
        if (r->list[i].number == num) {
            printf("- %s\n", r->list[i].name);// 일치하는 학번을 가진 모든 학생 이름 출력
            found = 1;// 성공할 경우 1
        }
    }
    if (!found) {//실패하여 0일 경우
        printf("해당하는 학생이 없습니다.\n");
    }
    printf("\n");
}

//성적 검색하는 함수
void search_by_score(memory* r) {
    int score = input_score("검색할 성적: ");
    int found = 0;
    for (int i = 0; i < r->count; i++) {
        if (r->list[i].score == score) {
            printf("- %s\n", r->list[i].name);// 같은 성적을 가진 학생의 이름을 모두 출력
            found = 1;
        }
    }
    if (!found) {
        printf("해당하는 학생이 없습니다.\n");
    }
    printf("\n");
}

//주소 검색하는 함수
void search_by_address(memory* r, int field) {
    char d[50];
    char* label;
    if (field == 0) label = "나라: ";
    else if (field == 1) label = "도: ";
    else if (field == 2) label = "시: ";
    else label = "구: ";// 함수 호출 시 입력한 매개변수에 따라 아래에서 나오는 안내문구가 달라짐

    input_name(label, d, sizeof(d));// 문자열 입력

    int found = 0;
    for (int i = 0; i < r->count; i++) {
        char* target = get_address(&r->list[i].address, field);
        if (str_cmp(target, d) == 0) {
            printf("- %s\n", r->list[i].name); //완전 일치할 경우
            found = 1;
        }
    }
    if (!found) {
        printf("해당하는 학생이 없습니다.\n");
    }
    printf("\n");
}

//새로운 학생 추가하는 함수
void add_student(memory* r) {
    Student s;
    s.number = input_number("번호: ");
    input_name("이름: ", s.name, sizeof(s.name));
    input_address(&s.address);
    s.score = input_score("성적: ");//정보 입력하는 코드

    if (r->count == r->capacity) {
        memory_big(r);//용량 부족하면 재할당
    }
    r->list[r->count] = s;//학생 수에 따른 배열에 구조체 배열을 넣어줌
    r->count++;//학생 수 1 증가
    printf("학생이 추가되었습니다.\n");
}

//학생 삭제하는 함수
void delete_student(memory* r) {
    if (r->count == 0) {
        printf("등록된 학생이 없습니다.\n\n");
        return;
    }// 등록된 사람이 없으면 종료

    Student k;
    k.number = input_number("삭제할 학생 번호: ");
    input_name("삭제할 학생 이름: ", k.name, sizeof(k.name));
    input_address(&k.address);
    k.score = input_score("삭제할 학생 성적: ");//모든 정보가 일치하는 대상을 검색할 예정

    int* match_x = (int*)malloc(r->count * sizeof(int));
    if (match_x == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }//일치한 항목의 배열 인덱스를 담아둘 메모리 할당 및 예외 처리
    int match_count = 0;

    for (int i = 0; i < r->count; i++) {
        Student* s = &r->list[i];
        if (s->number == k.number && str_cmp(s->name, k.name) == 0 && s->score == k.score &&
            str_cmp(s->address.country, k.address.country) == 0 &&str_cmp(s->address.province, k.address.province) == 0 && str_cmp(s->address.city, k.address.city) == 0 &&
            str_cmp(s->address.dis, k.address.dis) == 0) 
        {//모든 정보가 일치하는 경우
            match_x[match_count] = i;// 인덱스 번호 저장
            match_count++;
        }
    }

    if (match_count == 0) {
        printf("일치하는 학생이 없습니다.\n\n");
        free(match_x);
        return;
    }//일치하는 사람이 없었던 경우

    int target;
    if (match_count == 1) {
        target = match_x[0];
    }// 한 명이면 즉시 타겟으로 지정
    else {// 복수일 경우 선택
        printf("동일한 정보를 가진 학생이 %d명 있습니다. 선택해주세요.\n", match_count);
        for (int i = 0; i < match_count; i++) {
            printf("%d) ", i + 1);
            print_student(&r->list[match_x[i]]);
        }
        int s = input_number("삭제할 항목 번호 선택: ");
        while (s < 1 || s > match_count) {
            s = input_number("다시 선택해주세요: ");
        }
        target = match_x[s - 1];// 선택한 실제 인덱스를 타겟으로 정함
    }

    for (int i = target; i < r->count - 1; i++) {
        r->list[i] = r->list[i + 1];
    }// 한 칸씩 당겨 삭제한 빈자리를 채움
    r->count--;// 학생 수가 줄었으므로 1 감소
    free(match_x);// 임시로 할당한 메모리 해제
    printf("학생이 삭제되었습니다.\n");
}

//파일 저장하는 함수
void save_file(memory* r) {
    char filename[100];
    get_line("저장할 파일명: ", filename, sizeof(filename));

    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n\n");
        return;
    }//예외 처리

    for (int i = 0; i < r->count; i++) {
        Student* s = &r->list[i];
        fprintf(fp, "%d,%s,%s,%s,%s,%s,%d\n",
            s->number, s->name,
            s->address.country, s->address.province,
            s->address.city, s->address.dis, s->score);
    }// 쉼표로 구분해서 기록

    fclose(fp);// 파일 닫기
    printf("저장이 완료되었습니다.\n");
}

//쉼표 기준으로 읽는 위치를 구분하면서 추출하는 함수
int next_field(char* line, int* p1, char* d, int max) {
    int i = 0;
    int p = *p1;// 읽은 위치 인덱스

    
        if (line[p] == '\0') {
            return 0;
         }// 끝에 도달할 경우 종료

        //쉼표나 줄 바꿈 만날 때까지 한 글자씩 가져온다
    while (line[p] != '\0' && line[p] != ',' && i < max - 1) {
        d[i] = line[p];
        i++;
        p++;
    }
    d[i] = '\0';// 잘라온 문자열을 마감한다

    if (line[p] == ',') p++;// 쉼표는 건너뛰기
    *p1 = p;// 읽기 위치를 포인터 변수를 통해 저장
    return 1;
}

//파일 불러오는 함수
void load_file(memory* r) {
    char filename[100];
    get_line("불러올 파일명: ", filename, sizeof(filename));

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("파일을 열 수 없습니다.\n\n");
        return;
    }// 예외 처리

    memory_free(r);//메모리 해제
    memory_init(r);//초기화

    char line[300];
    char field[50];

    while (fgets(line, sizeof(line), fp) != NULL) {
        remove_last(line);
        if (line[0] == '\0') {
            continue;
        }// 한 줄 씩 읽어오기

        int p = 0;
        Student s;

        //데이터를 추출
        next_field(line, &p, field, sizeof(field));
        s.number = str_t_num(field);//학번

        next_field(line, &p, field, sizeof(field));
        str_copy(s.name, field);//이름

        next_field(line, &p, field, sizeof(field));
        str_copy(s.address.country, field);//나라

        next_field(line, &p, field, sizeof(field));
        str_copy(s.address.province, field);//도

        next_field(line, &p, field, sizeof(field));
        str_copy(s.address.city, field);//시

        next_field(line, &p, field, sizeof(field));
        str_copy(s.address.dis, field);//구

        next_field(line, &p, field, sizeof(field));
        s.score = str_t_num(field);//점수

        if (r->count == r->capacity) {
            memory_big(r);
        }//메모리 크기 확인 및 재할당 예외 처리
        r->list[r->count] = s;//동적 배열에 등록
        r->count++;
    }

    fclose(fp);
    printf("불러오기가 완료되었습니다.\n\n");
}

//메인 메뉴 선택 화면 출력
void print_menu(void) {
    printf("< 출석부 프로그램 > \n");
    printf("1. 학생 추가\n");
    printf("2. 학생 삭제\n");
    printf("3. 정렬\n");
    printf("4. 검색\n");
    printf("5. 전체 출력\n");
    printf("6. 저장\n");
    printf("7. 불러오기\n");
    printf("0. 종료\n");
}

//선택에 따라 정렬 함수를 호출해주는 함수
void sort_menu(memory* r) {
    if (r->count == 0) {
        printf("등록된 학생이 없습니다.\n");
        return;
    }
    printf("--- 정렬 기준 ---\n");
    printf("1. 번호순\n2. 이름순\n3. 주소순\n4. 성적순\n");
    int ch = input_number("선택: ");

    if (ch == 1) {
        sort_by_number(r);
    }
    else if (ch == 2) {
        sort_by_name(r);
    }
    else if (ch == 3) {
        printf("1. 나라 2. 도 3. 시 4. 구\n");
        int field = input_number("주소 항목 선택: ");
        while (field < 1 || field > 4) {
            field = input_number("다시 선택: ");
        }
        sort_by_address(r, field - 1);
    }
    else if (ch == 4) {
        sort_by_score(r);
    }
    else {
        printf("잘못된 입력입니다.\n");
        return;
    }
    printf("정렬이 완료되었습니다.\n");
    print_all(r);
}

//선택에 따라 검색 함수를 호출해주는 함수
void search_menu(memory* r) {
    if (r->count == 0) {
        printf("등록된 학생이 없습니다.\n");
        return;
    }
    printf("--- 검색 기준 ---\n");
    printf("1. 번호 2. 주소 3. 성적\n");
    int ch = input_number("선택: ");

    if (ch == 1) {
        search_by_number(r);
    }
    else if (ch == 2) {
        printf("1. 나라 2. 도 3. 시 4. 구\n");
        int field = input_number("주소 항목 선택: ");
        while (field < 1 || field > 4) {
            field = input_number("다시 선택: ");
        }
        search_by_address(r, field - 1);
    }
    else if (ch == 3) {
        search_by_score(r);
    }
    else {
        printf("잘못된 입력입니다.\n");
    }
}

//코드가 너무 길었네요. 자세히 봐주셔서 감사합니다.