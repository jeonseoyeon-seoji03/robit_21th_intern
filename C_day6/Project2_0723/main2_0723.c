// 6일차 과제 2번입니다.

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int data;
    struct _Node* next;
} Node;

typedef struct {
    Node* top;
    int size;
} stack; // 과제에서 주어진 구조체를 사용함. (약간의 변형을 가함.)

void stack_init(stack* s); // stack을 초기화하는 함수
Node* create_node(int data); //새 노드를 만드는 함수
void push(stack* s, int data); //정수를 stack에 push하는 함수
void printStack(stack* s); //stack 내 모든 값 출력, stack이 비어있는 경우 관련 내용 출력
void pop(stack* s); //top을 pop하고 그 값을 출력, 비어있는 경우 관련 내용 출력
int top(stack* s); // top에 위치한 값을 반환하는 함수
void s_size(stack* s); //stack 크기를 출력하는 함수, size라 쓰니 오류가 나서 함수명을 바꿈.
int isEmpty(stack* s); //stack에 데이터의 유무를 반환하는 함수

int main() {
    stack s;

    //기본 기능 확인
    stack_init(&s); //어제 배운대로 함수에서 원하는 매개변수에 맞춰 주소값을 보냄.
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);
    printStack(&s); // 30 20 10
    pop(&s); // 30
    if (!isEmpty(&s)) {// 스택이 비어있는지를 먼저 확인하고 top을 실행시킨다.
        printf("top 값은 %d입니다.\n", top(&s));
    } // 20
    else {
        printf("top 값이 비어있습니다.\n");
    }
    s_size(&s);// 2
    if (isEmpty(&s)) {
        printf("stack 안에 데이터가 없습니다.\n");
    }
    else{
        printf("stack 안에 데이터가 존재합니다\n");
    }//존재합니다.

    //예외처리 확인

    pop(&s);
    pop(&s);
    printStack(&s);// 비어있습니다.
    pop(&s);// 비어있습니다.
    if (!isEmpty(&s)) {
        printf("top 값은 %d입니다.\n", top(&s));
    }
    else {
        printf("top 값이 비어있습니다.\n");
    }// 비어있습니다.
    s_size(&s);// 0
    if (isEmpty(&s)) {
        printf("stack 안에 데이터가 없습니다.\n");
    }//없습니다
    else {
        printf("stack 안에 데이터가 존재합니다\n");
    }
    // 비어있고, 없는데도 코드가 진행되는 이유는 exit를 안 쓰고 return을 썼기 때문입니다.
    // 현재 예시 코드에서는 모든 메모리를 해제했으므로 free를 쓰지 아니함.
    return 0;
}

// stack을 초기화하는 함수
void stack_init(stack* s) {
    s->top = NULL;
    s->size = 0;
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

//정수를 stack에 push하는 함수
void push(stack* s, int data) {
    Node* new_node = create_node(data);// 새 노드 만들기, next는 아직 NULL인 상태 유지
    new_node->next = s->top;//next를 기존 top으로 만듦.
    s->top = new_node;//top 표시를 새 노드로 바꿔줌.
    s->size++;// 노드 개수가 늘었으므로 1 증가

}

//stack 내 모든 값 출력, stack이 비어있는 경우 관련 내용 출력
void printStack(stack* s)
{
    Node* cur = s->top;// top부터 시작
    if (cur == NULL) {
        printf("stack이 비어있습니다.\n");
        return;
    }//비어있을 경우 비어있다고 출력
    while (cur != NULL) {
        printf("%d ", cur->data);//data 출력
        cur = cur->next;// 다음 노드로 이동
    }
   
    printf("\n");

}

//top을 pop하고 그 값을 출력, 비어있는 경우 관련 내용 출력
void pop(stack* s) {
    if (s->top == NULL) {
        printf("stack이 비어있습니다.\n");
        return;
    }// 비어있다는 내용 출력
    Node* temp = s->top;// top을 임시로 temp에 저장
    s->top = temp->next;//top을 temp의 next로 옮겨줌으로서 문제 예방 (순서가 틀리면 다 사라지거나 손상될 수 있음.)
    printf("%d \n", temp->data);//temp인 기존 top의 데이터를 출력함.
    free(temp);// temp를 메모리 해제함.
    s->size--; //노드가 하나 줄었으므로 1 감소

}

// top에 위치한 값을 반환하는 함수
int top(stack* s) {
    if (s->top != NULL) {
        return s->top->data;
    }
}//초기에는 NULL일 경우 특정 값을 반환하고자 했으나, 그럴 경우 data와 똑같은 값을 반환하게 되는 경우 원치 않은 결과가 나올 수 있어 위와 같이 수정함
//호출 전 이미 스택이 비어있는지 확인했으니 별도의 else는 두지 않는다.

//stack 크기를 출력하는 함수
void s_size(stack* s) {
    printf("stack 크기는 %d입니다.\n", s->size);
}

//stack에 데이터의 유무를 반환하는 함수
int isEmpty(stack* s) {
    if (s->top == NULL) {
        return 1;
    }
    return 0;
}
/*함수에서 true or false로 반환해야하는데 bool이 있는 외부 라이브러리를 못 쓰므로 0 / 1로 바꿨습니다. 
인터넷 검색을 해보니 매크로 상수로 가능하다고 하지만, 문제에서 말하는 true, false가 이것을 의미하는 게 아닌 것 같아 위와 같이 진행하였습니다. */