#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct _Node {
    int data;
    struct _Node* next;
} Node;

typedef struct{
    Node* head;
    Node* tail;
    int size;
} LinkedList;// 과제 7번에서 제시된 구조체 사용


void list_init(LinkedList* list); //리스트 초기 설정
Node* create_node(int data); //새 노드를 만드는 함수

void insert(LinkedList* list, int index, int data); //원하는 위치에 새 노드를 넣는 함수
void insert_before_data(LinkedList* list, int target_data, int data); // 데이터 값을 바탕으로 새 노드를 넣는 함수
void insert_first(LinkedList* list, int data); //맨 앞에 새 노드를 넣는 함수
void insert_back(LinkedList* list, int data); // 맨 뒤에 새 노드를 넣는 함수

void delete_by_index(LinkedList* list, int index); //원하는 위치 노드 삭제
void delete_by_data(LinkedList* list, int data); //데이터 값을 바탕으로 노드 삭제
void delete_first(LinkedList* list); // 맨 첫 노드 지우는 함수
void delete_back(LinkedList* list); //맨 뒤 노드 지우는 함수

int get_entry_by_data(LinkedList* list, int data); // 값으로 위치 찾기
int get_entry_by_index(LinkedList* list, int index, int* out_data); //위치로 값 찾는 함수

int get_length(LinkedList* list); // 리스트 전체 길이 반환
void print_list(LinkedList* list); //노드 속 모든 요소 출력하는 함수
void reverse(LinkedList* list); //리스트 방향 뒤집는 함수
void list_free(LinkedList* list); //전체 메모리를 정리하는 함수

int main() { // 테스트용
    LinkedList list;
    list_init(&list);

    insert_back(&list, 100);
    insert_back(&list, 200);
    insert_back(&list, 300);
    print_list(&list);

    insert(&list, 1, 999);
    print_list(&list);

    delete_by_index(&list, 2);
    print_list(&list);

    reverse(&list);
    print_list(&list);

    int data;
    if (get_entry_by_index(&list, 1, &data)) {
        printf("index 1의 값: %d\n", data);
    }
    printf("300의 index: %d\n", get_entry_by_data(&list, 300));
    printf("리스트 길이: %d\n", get_length(&list));

    list_free(&list);
    return 0;
}

// 함수 상세 정의

//리스트 초기 설정
void list_init(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

//새 노드를 만드는 함수
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node)); // 노드 크기만큼 메모리 할당
    if (new_node == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }// 메모리 할당 실패 시의 예외 처리
    new_node->data = data; // 호출 시 받은 값을 입력.
    new_node->next = NULL; // 어느 곳에 연결될 지 모르기 때문에 NULL 상태로 둠.
    return new_node;// 호출된 쪽으로 노드의 주소를 반환함.
}

//맨 앞에 새 노드를 넣는 함수
void insert_first(LinkedList* list, int data) {
    Node* new_node = create_node(data);// 새 노드 만들기, next는 아직 NULL인 상태 유지
    new_node->next = list->head;// 새 노드의 next가 헤드 노드를 가리키게 함
    list->head = new_node;//head 표시를 새 노드로 바꿔줌.

    if (list->size == 0) {
        list->tail = new_node;// 리스트가 완전히 빈 상태였을 경우 head이자 tail이어야 함.
    }
    list->size++;// 노드 개수가 늘었으므로 1 증가
}

// 맨 뒤에 새 노드를 넣는 함수
void insert_back(LinkedList* list, int data) {
    Node* new_node = create_node(data);// 새 노드 만들기, next는 아직 NULL인 상태 유지

    if (list->size == 0) {
        list->head = new_node;// 리스트가 완전히 빈 상태였을 경우, head이자 tail이 되어야함
        list->tail = new_node;
    }
    else {
        list->tail->next = new_node;// 현재의 tail의 next가 새 노드를 가리킴
        list->tail = new_node;// tail 표시를 새 노드로 바꿔준다.
    }
    list->size++;// 노드 개수가 늘었으므로 1 증가
}

//원하는 위치에 새 노드를 넣는 함수
void insert(LinkedList* list, int index, int data) {
    if (index <= 0) {
        insert_first(list, data);
        return;// 맨 앞일 경우, 이미 만든 함수로 처리
    }
    if (index >= list->size) {
        insert_back(list, data);
        return;// 맨 뒤일 경우 이미 만든 함수로 처리.
    }

    Node* new_node = create_node(data);// 새 노드 만들기

    //index번째 바로 앞 노드 찾기
    Node* prev = list->head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next; //next를 가리켜 index번째 앞 노드로 prev를 두고자 함
    }

    new_node->next = prev->next;// 새 노드의 next가 index번째 앞 노드가 next로 둔 노드를 가리킴
    prev->next = new_node;//index번째 앞 노드가 next로 새 노드를 둠, 위 순서대로 하지 않으면 뒷 순서 노드를 잃어버림
    list->size++;// 노드 개수가 늘었으므로 1 증가
}

// 데이터 값을 바탕으로 새 노드를 넣는 함수
void insert_before_data(LinkedList* list, int target_data, int data) {
    int x = get_entry_by_data(list, target_data);
    if (x != -1) {// 찾는 데이터와 일치하는 값이 있는 경우
        insert(list, x, data); // 원하는 위치에 새 노드를 넣는 함수
    }
    else {
        printf("해당 데이터를 찾을 수 없습니다.\n"); // 찾는 데이터와 일치하는 값이 없는 경우
    }
}

// 맨 첫 노드 지우는 함수
void delete_first(LinkedList* list) {
    if (list->size == 0) {
        return;
    }// 리스트가 비어있는 경우, 삭제할 것이 없으므로 종료

    Node* temp = list->head;// 지울 노드의 주소를 저장해 둔다. 이후 메모리 해제할 때 사용한다.
    list->head = list->head->next;//head를 원래 head의 next로 옮겨준다.

    if (list->size == 1) {
        list->tail = NULL;// 원래 노드가 한 개 뿐일 경우, 리스트가 비게 되므로 tail을 NULL로 만들어야 함.
    }
    free(temp);// 메모리 해제
    list->size--;// 노드 하나가 지워졌으니 개수 1 감소
}

//맨 뒤 노드 지우는 함수
void delete_back(LinkedList* list) {
    if (list->size == 0) return;// 비어있을 경우 종료
    if (list->size == 1) {// 리스트 안에 노드가 하나 뿐일 경우 첫 노드를 지우는 함수와 같은 상황이므로 다른 함수를 호출
        delete_first(list);
        return;
    }

    Node* prev = list->head; // 이전 노드로 가는 화살표가 없으므로 head부터 한 칸씩 이동하며 tail을 찾아야함
    while (prev->next != list->tail) {// tail 직전의 노드를 찾는 코드
        prev = prev->next;
    }

    free(list->tail);// tail 메모리 해제 prev가 tail 직전 노드를 가르키고 있어서 해제해도 괜찮음.
    prev->next = NULL;// prev의 next를 NULL로 만듦으로써 prev이 리스트의 마지막 노드가 됨
    list->tail = prev;//tail 표시를 prev로 바꿔줌
    list->size--;// 노드 개수가  1 감소
}

//원하는 위치 노드 삭제
void delete_by_index(LinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        printf("범위를 벗어났습니다.");
        return; // 범위를 벗어난 인덱스면 종료
    }
    if (index == 0) {
        delete_first(list);
        return;
    }
    if (index == list->size - 1) {
        delete_back(list);
        return;
    }// 맨 앞, 맨 뒤는 이미 만든 함수로 처리함.

    Node* prev = list->head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }// 지울 노드 바로 앞 자리 찾기

    Node* target = prev->next;//target이 지우고 싶은 노드
    prev->next = target->next;// 지워질 노드를 건너뛰고 그 다음으로 바로 연결
    free(target);// 메모리 해제, 위 과정을 순차적으로 거쳐야함. 메모리 해제가 우선적으로 일어날 경우 지워진 노드의 다음 노드가 어떤 값인지 알 수 없음.
    list->size--;// 노드 1 감소
}

//데이터 값을 바탕으로 노드 삭제
void delete_by_data(LinkedList* list, int data) {
    int idx = get_entry_by_data(list, data);
    if (idx != -1) {// 찾는 데이터와 일치하는 값이 있는 경우
        delete_by_index(list, idx);// 원하는 위치의 노드를 삭제
    }
    else {
        printf("해당 데이터를 찾을 수 없습니다.\n"); // 찾는 데이터와 일치하는 값이 없는 경우
    }
}

// 값으로 위치 찾기
int get_entry_by_data(LinkedList* list, int data) {
    Node* cur = list->head; // 현재 보고 있는 노드를 head 노드부터 시작
    int index = 0; //cur가 몇번째 노드인지 센다.

    while (cur != NULL) {// 리스트 끝까지 반복
        if (cur->data == data) {// cur 노드의 데이터가 찾는 값과 같으면 index를 반환함.
            return index;
        }
        cur = cur->next;
        index++;// 다음 노드로 이동 및 몇번째 노드인지 세기 위해 1을 더한다.
    }
    return -1;
}

//위치로 값 찾는 함수
int get_entry_by_index(LinkedList* list, int index, int* out_data) {
    if (index < 0 || index >= list->size) return 0;// 범위 밖이면 0 반환, main에서 조건식에 사용된다.

    Node* cur = list->head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }//head부터 시작해서 index만큼 next로 이동함.
    *out_data = cur->data;// 직접 데이터 넣기
    return 1;// 성공하였으므로 1 반환
}

// 리스트 전체 길이 반환
int get_length(LinkedList* list) {
    return list->size; //size가 길이이므로 반환
}

//노드 속 모든 요소 출력하는 함수
void print_list(LinkedList* list) {
    Node* cur = list->head;// head부터 시작
    while (cur != NULL) {
        printf("%d ", cur->data);//data 출력
        cur = cur->next;// 다음 노드로 이동
    }
    printf("\n");
}

//리스트 방향 뒤집는 함수
void reverse(LinkedList* list) {
    Node* prev = NULL; // 방금 처리하고 지나온 노드, 현재는 없으니 NULL
    Node* cur = list->head;// 지금 뒤집는 노드, head부터 시작
    Node* next = NULL;//지금 뒤집는 노드의 다음 노드를 보관하는 용도

    list->tail = list->head; // 뒤집히면 기존 head가 새로운 tail이 됨

    while (cur != NULL) {// 끝에 도달하지 않은 이상 반복
        next = cur->next;// 원래 다음 노드가 어디였는지 저장
        cur->next = prev; // 뒤집음
        prev = cur;// 한 칸 전진
        cur = next;// 한 칸 전진
    }

    list->head = prev; // 마지막에 prev를 새로운 head로 지정
}

//전체 메모리를 정리하는 함수
void list_free(LinkedList* list) {
    Node* cur = list->head;
    while (cur != NULL) {
        Node* temp = cur;
        cur = cur->next;// 다음 노드 주소 저장
        free(temp);// 메모리 해제
    }
    list->head = list->tail = NULL;
    list->size = 0; //리스트도 빈 상태로 초기화
}


