#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    char data;
    struct _Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} queue;

typedef struct {
    Node* top;
    int size;
} stack; 


void queue_init(queue* q); // queue을 초기화하는 함수
Node* create_node(char data); //새 노드를 만드는 함수
void Enqueue(queue* q, char data); //문자를 Enqueue하는 함수
char Dequeue(queue* q); //front을 Dequeue하고 그 값을 반환, 비어있는 경우 관련 내용 출력


void stack_init(stack* s); // stack을 초기화하는 함수
void push (stack* s, char data); //문자를 stack에 push하는 함수
char pop(stack* s); //top을 pop하고 그 값을 반환, 비어있는 경우 관련 내용 출력
char* input_str(); // 문자열 메모리 할당 및 문자열 입력

int main() {
    char* str=input_str();
    int i = 0;
    queue q;
    stack s;

    queue_init(&q);
    stack_init(&s);// 초기화

    while (str[i] != '\0') {
        Enqueue(&q, str[i]);
        push(&s, str[i]);
        i++;
    }// stack과 queue에 문자열 추가

    int pali = 1; //회문이라고 가정
    for (int j = 0; j <i; j++) {
        char c1 = Dequeue(&q);
        char c2 = pop(&s);
        if (c1 != c2) {
            pali = 0;
            break;
        }
    }//서로 다른 값을 읽어내면 회문이 아니므로 0으로 pali의 값을 바꿔줌,

    if (pali) {
        printf("%s는 회문이 맞습니다.\n", str);
    }
    else {
        printf("%s는 회문이 아닙니다.\n", str);
    }
    
    free(str); //메모리 해제
    return 0;
}

// queue을 초기화하는 함수
void queue_init(queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

//새 노드를 만드는 함수
Node* create_node(char data) {
    Node* new_node = (Node*)malloc(sizeof(Node)); // 노드 크기만큼 메모리 할당
    if (new_node == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }// 메모리 할당 실패 시의 예외 처리
    new_node->data = data; // 호출 시 받은 값을 입력.
    new_node->next = NULL; // 어느 곳에 연결될 지 모르기 때문에 NULL 상태로 둠.
    return new_node;// 호출된 쪽으로 노드의 주소를 반환함.
}

//문자를 Enqueue하는 함수
void Enqueue(queue* q, char data) {
    Node* new_node = create_node(data);// 새 노드 만들기, next는 아직 NULL인 상태 유지
    if (q->rear == NULL) {
        q->rear = new_node;
        q->front = new_node;//  비어있는 경우 rear와 front가 모두 필요함.
    }
    else {
        q->rear->next = new_node;// 기존 rear의 next를 새 노드에 연결
        q->rear = new_node;// rear를 새 노드로 바꿔줌
    }
    q->size++;// 노드 개수가 늘었으므로 1 증가

}


//front을 Dequeue하고 그 값을 반환, 비어있는 경우 관련 내용 출력
char Dequeue(queue* q) {
    if (q->front == NULL) {
        printf("queue가 비어있습니다.\n");
        return '\0';
    }// 비어있다는 내용 출력

    Node* temp = q->front;// front을 임시로 temp에 저장
    q->front = temp->next;//front을 temp(기존 front)의 next로 옮겨줌으로서 문제 예방 (순서가 틀리면 다 사라지거나 손상될 수 있음.)
    char result_1 = temp->data;
    free(temp);// temp를 메모리 해제함.
    if (q->front == NULL) {
        q->rear = NULL;// front가 NULL이면 rear도 NULL이여야함.
    }
    q->size--; //노드가 하나 줄었으므로 1 감소
    return result_1;//앞에서부터 읽은 값을 반환
}


// stack을 초기화하는 함수
void stack_init(stack* s) {
    s->top = NULL;
    s->size = 0;
}

//문자를 stack에 push하는 함수
void push(stack* s, char data) {
    Node* new_node = create_node(data);// 새 노드 만들기, next는 아직 NULL인 상태 유지
    new_node->next = s->top;//next를 기존 top으로 만듦.
    s->top = new_node;//top 표시를 새 노드로 바꿔줌.
    s->size++;// 노드 개수가 늘었으므로 1 증가

}

//top을 pop하고 그 값을 반환, 비어있는 경우 관련 내용 출력
char pop(stack* s) {
    if (s->top == NULL) {
        printf("stack이 비어있습니다.\n");
        return '\0';
    }// 비어있다는 내용 출력

    Node* temp = s->top;// top을 임시로 temp에 저장
    s->top = temp->next;//top을 temp의 next로 옮겨줌으로서 문제 예방 (순서가 틀리면 다 사라지거나 손상될 수 있음.)
    char result_2 = temp->data;
    free(temp);// temp를 메모리 해제함.
    s->size--; //노드가 하나 줄었으므로 1 감소
    return result_2;// 뒤에서부터 읽은 내용을 반환

}

char* input_str() {
    char temp_str[1000]; // 임시로 문자열을 저장하는 배열
    printf("문자열을 입력하세요.");
    if (fgets(temp_str, sizeof(temp_str), stdin) == NULL) {
        printf("입력을 받는 데 실패했습니다 \n");
        exit(1);
   }

    int len= 0;
    while (temp_str[len] != '\0' && temp_str[len] != '\n') {
        len++;
    }// 문자열 길이 재는 코드

    temp_str[len] = '\0';// '\0' 추가하기. (\n이 있었을 수 있기 때문이다.)

    char* str = (char*)malloc((len + 1) * sizeof(char));
    if (str == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }//메모리 할당 및 예외 처리

    for (int i = 0; i <= len; i++) {
        str[i] = temp_str[i];
    }// 할당된 메모리로 문자열 옮기기

    return str;
}