// 6일차 과제 3번입니다.

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    int data;
    struct _Node* next;
} Node;

typedef struct {
    Node* front;// 나가야하는 쪽
    Node* rear; // 넣는 쪽
    int size;
} queue; 

void queue_init(queue* q); // queue을 초기화하는 함수
Node* create_node(int data); //새 노드를 만드는 함수
void Enqueue(queue* q, int data); //정수를 Enqueue하는 함수
void printQueue(queue* q); //queue 내 모든 값 출력, queue이 비어있는 경우 관련 내용 출력
void Dequeue(queue* q); //front을 Dequeue하고 그 값을 출력, 비어있는 경우 관련 내용 출력
int front(queue* q); // front에 위치한 값을 반환하는 함수
int rear(queue* q); // rear에 위치한 값을 반환하는 함수
void q_size(queue* q); //queue 크기를 출력하는 함수
int isEmpty(queue* q); //queue에 데이터의 유무를 반환하는 함수

int main() {
    queue q;

    //기본 기능 확인
    queue_init(&q);
    Enqueue(&q, 10);
    Enqueue(&q, 20);
    Enqueue(&q, 30);
    printQueue(&q); // 10 20 30
    Dequeue(&q); // 10
    if (!isEmpty(&q)) {// queue가 비어있는지를 먼저 확인하고 front을 실행시킨다.
        printf("front 값은 %d입니다.\n", front(&q));
    } // 20
    else {
        printf("front 값이 비어있습니다.\n");
    }
    if (!isEmpty(&q)) {// queue가 비어있는지를 먼저 확인하고 rear을 실행시킨다.
        printf("rear 값은 %d입니다.\n", rear(&q));
    } // 30
    else {
        printf("rear 값이 비어있습니다.\n");
    }

    q_size(&q);// 2

    if (isEmpty(&q)) {
        printf("queue 안에 데이터가 없습니다.\n");
    }
    else {
        printf("queue 안에 데이터가 존재합니다\n");
    }//존재합니다.

    //예외처리 확인

    Dequeue(&q);
    Dequeue(&q);
    printQueue(&q);// 비어있습니다.
    Dequeue(&q);// 비어있습니다.
    if (!isEmpty(&q)) {// queue가 비어있는지를 먼저 확인하고 front을 실행시킨다.
        printf("front 값은 %d입니다.\n", front(&q));
    } 
    else {
        printf("front 값이 비어있습니다.\n");
    }//비어있습니다
    if (!isEmpty(&q)) {// queue가 비어있는지를 먼저 확인하고 rear을 실행시킨다.
        printf("rear 값은 %d입니다.\n", rear(&q));
    }
    else {
        printf("rear 값이 비어있습니다.\n");
    }//비어있습니다

    q_size(&q);// 0
    if (isEmpty(&q)) {
        printf("queue 안에 데이터가 없습니다.\n");
    }//없습니다
    else {
        printf("queue 안에 데이터가 존재합니다\n");
    }

    // 비어있고, 없는데도 코드가 진행되는 이유는 exit를 안 쓰고 return을 썼기 때문입니다.
     // 현재 예시 코드에서는 모든 메모리를 해제했으므로 free를 쓰지 아니함.
    return 0;
}

// queue을 초기화하는 함수
void queue_init(queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
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

//정수를 Enqueue하는 함수
void Enqueue(queue* q, int data) {
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

//queue 내 모든 값 출력, queue이 비어있는 경우 관련 내용 출력
void printQueue(queue* q)
{
    Node* cur = q->front;// front부터 시작
    if (cur == NULL) {
        printf("queue가 비어있습니다.\n");
        return;
    }//비어있을 경우 비어있다고 출력
    while (cur != NULL) {
        printf("%d ", cur->data);//data 출력
        cur = cur->next;// 다음 노드로 이동
    }

    printf("\n");

}

//front을 Dequeue하고 그 값을 출력, 비어있는 경우 관련 내용 출력
void Dequeue(queue* q) {
    if (q->front == NULL) {
        printf("queue가 비어있습니다.\n");
        return;
    }// 비어있다는 내용 출력

    Node* temp = q->front;// front을 임시로 temp에 저장
    q->front = temp->next;//front을 temp(기존 front)의 next로 옮겨줌으로서 문제 예방 (순서가 틀리면 다 사라지거나 손상될 수 있음.)
    printf("%d \n", temp->data);//temp인 기존 front의 데이터를 출력함.
    free(temp);// temp를 메모리 해제함.
    if (q->front == NULL) {
        q->rear = NULL;// front가 NULL이면 rear도 NULL이여야함.
    }
    q->size--; //노드가 하나 줄었으므로 1 감소

}

// front에 위치한 값을 반환하는 함수
int front(queue* q) {
    if (q->front != NULL) {
        return q->front->data;
    }
}

// rear에 위치한 값을 반환하는 함수
int rear(queue* q) {
    if (q->rear != NULL) {
        return q->rear->data;
    }
}


//queue 크기를 출력하는 함수
void q_size(queue* q) {
    printf("queue 크기는 %d입니다.\n", q->size);
}

//queue에 데이터의 유무를 반환하는 함수
int isEmpty(queue* q) {
    if (q->front == NULL) {
        return 1;
    }
    return 0;
}
/*함수에서 true or false로 반환해야하는데 bool이 있는 외부 라이브러리를 못 쓰므로 0 / 1로 바꿨습니다.
인터넷 검색을 해보니 매크로 상수로 가능하다고 하지만, 문제에서 말하는 true, false가 이것을 의미하는 게 아닌 것 같아 위와 같이 진행하였습니다. */