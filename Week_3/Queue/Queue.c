#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_QUEUE_SIZE 100

typedef int element;

typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 초기화 함수
void init(QueueType* q) {
	q->front = q->rear = 0; // front와 rear을 0으로 설정
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) {
	return (q->front == q->rear); // front와 rear의 값이 같으면
}

// 포화 상태 검출 함수
int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front); // front가 rear보다 하나 앞에 있으면
}

// 삽입 함수
void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화 상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE; // rear을 하나 늘리고
	q->queue[q->rear] = item; // 그 자리에 요소 삽입
}

// 삭제 함수
element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백 상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE; // front를 하나 늘리고
	return q->queue[q->front]; // 그 자리에 있는 원소 반환
}

// 엿보기 함수: 큐의 맨 앞 데이터를 읽어서 반환
element peek(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백 상태입니다.");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE]; // 큐의 길이를 넘어서는 경우를 대비해 MQS의 나머지로
}

int main(void) {
	QueueType q;

	init(&q);
	printf("front= %d, rear= %d\n", q.front, q.rear); // 0, 0(f = r 이므로 공백 상태)
	
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	
	// 큐는 선입선출 방식이다.
	printf("dequeue()= %d\n", dequeue(&q));
	printf("dequeue()= %d\n", dequeue(&q));
	printf("dequeue()= %d\n", dequeue(&q));

	printf("front= %d, rear= %d\n", q.front, q.rear); // 3, 3(f = r 이므로 공백 상태)

	return 0;
}