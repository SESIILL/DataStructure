#include <stdio.h>
#include <malloc.h>

typedef int element; // 요소의 타입

typedef struct QueueNode { // 큐의 노드의 타입
	element item;
	struct QueueNode* link;
} QueueNode;

typedef struct { // 큐 ADT 구현
	QueueNode* front, * rear;
} QueueType;

// 오류 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화 함수
void init(QueueType* q) {
	q->front = q->rear = NULL;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) {
	return (q->front == NULL);
}

// 포화 상태 검출 함수(항상 거짓)
int is_full(QueueType* q) {
	return 0;
}

// 맨 뒤에 노드 삽입
void enqueue(QueueType* q, element item) {
	QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("메모리를 할당할 수 없습니다.");
	else {
		temp->item = item; // temp에 item 저장
		temp->link = NULL; // 마지막 노드이므로 link = null
		if (is_empty(q)) { // 큐가 공백이면
			q->front = temp;
			q->rear = temp;
		}
		else { // 큐가 공백이 아니면(순서 중요)
			q->rear->link = temp; // 맨 끝 노드는 temp를 가리킨다.
			q->rear = temp; // rear는 temp를 가리킨다.
		}
	}
}

// 맨 앞 노드 삭제
element dequeue(QueueType* q)
{
	QueueNode* temp = q->front; // temp = 첫 번째 노드
	element item;
	if (is_empty(q)) // 공백상태
		error("큐가 비어 있습니다.");
	else {
		item = temp->item; // 반환할 데이터 넣어 둠.
		q->front = q->front->link; // front가 temp의 다음 노드를 가리키도록 함.
		if (q->front == NULL) // 노드가 한 개여서 front가 null을 가리키게 되었다면
			q->rear = NULL; // rear도 null을 가리키게 해서 공백 상태를 만들어 준다.
		free(temp);
		return item;
	}
}

int main(void) {
	QueueType q;

	init(&q);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	printf("dequeue()=%d\n", dequeue(&q));
	printf("dequeue()=%d\n", dequeue(&q));
	printf("dequeue()=%d\n", dequeue(&q));

	return 0;
}