#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_QUEUE_SIZE 3
#define MAX_STRING 10

typedef struct {
	char gender;
	char name[10];
} element;

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
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
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

int get_count(QueueType* q) {
	if (q->front <= q->rear) // is_empty(q) 경우도 포함
		return q->rear - q->front; // 그냥 큰 쪽에서 작은 쪽을 빼 주면 된다.
	else // front가 rear보다 앞서 있는 경우(큐가 한 바퀴 이상 돈 경우)
		return MAX_QUEUE_SIZE - (q->front - q->rear);
}

void print_queue(QueueType* q) {
	if (!is_empty(q)) { // 큐가 비어있지 않은 경우에만 출력
		int i = (q->front + 1) % MAX_QUEUE_SIZE; // front + 1부터 시작
		while (i != (q->rear + 1) % MAX_QUEUE_SIZE) { // rear까지 출력
			printf("%s ", (q->queue[i]).name); 
			i = (i + 1) % MAX_QUEUE_SIZE; // MQS로 나눠 주며 다음 인덱스로 이동
		}
	}
	printf("\n");
}

int main(void) {
	QueueType m, f;
	element person;
	char choice = NULL;

	init(&m);
	init(&f);

	printf("미팅 주선 프로그램입니다.\n");
	while (choice != 'q') {
		printf("\n<insert: 고객 입력, check: 대기자 체크, quit: 종료>: ");
		scanf("%c", &choice);

		if (choice == 'i') {
			printf("이름 입력: ");
			scanf("%s", person.name);
			while (getchar() != '\n');
			printf("성별 입력: ");
			scanf(" %c", &person.gender);

			if (person.gender == 'm') { // 성별 남성
				if (is_empty(&f)) { // 여성 대기줄이 비어 있으면
					printf("아직 대상자가 없습니다. ");
					if (is_full(&m)) // 여성 대기줄도 비어 있고, 남성 대기줄도 꽉 차 있을 때
						printf("대기자가 꽉 찼으니 다음 기회를 이용해주세요.\n");
					else { // 여성 대기줄은 비어 있지만 남성 대기줄에는 자리가 있을 때
						printf("기다려 주십시오.\n");
						enqueue(&m, person);
					}
				}
				else { // 여성 대기자가 있을 때
					enqueue(&m, person);
					printf("커플이 탄생했습니다! %s와 %s\n", dequeue(&f).name, dequeue(&m).name);
				}
			}
			else { // 성별 여성
				if (is_empty(&m)) { // 남성 대기줄이 비어 있으면
					printf("아직 대상자가 없습니다. ");
					if (is_full(&f)) // 남성 대기줄도 비어 있고, 여성 대기줄도 꽉 차 있을 때
						printf("대기자가 꽉 찼으니 다음 기회를 이용해주세요.\n");
					else { // 남성 대기줄은 비어 있지만 여성 대기줄에는 자리가 있을 때
						printf("기다려 주십시오.\n");
						enqueue(&f, person);
					}
				}
				else { // 남성 대기자가 있을 때
					enqueue(&f, person);
					printf("커플이 탄생했습니다! %s와 %s\n", dequeue(&f).name, dequeue(&m).name);
				}
			}
		}
		else if (choice == 'c') {
			printf("남성 대기자 %d명: ", get_count(&m));
			print_queue(&m);
			printf("여성 대기자 %d명: ", get_count(&f));
			print_queue(&f);
		}

		while (getchar() != '\n');
	}

	return 0;
}