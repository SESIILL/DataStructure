#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 3
#include <stdio.h>

// 스택을 위한 타입 정의
typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} StackType;

// 스택 초기화 함수
void init(StackType* s) {
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(StackType* s) {
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(StackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(StackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else
		s->data[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

// 피크 함수
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}

// 현재 스택의 모습 출력
void stack_print(StackType* s) {
	int temp = s->top; // temp에 top 값을 옮겨 둠.
	if (is_empty(s)) // 스택이 비어 있는 경우
		printf("<empty>\n");
	else {
		while (!is_empty(s)) {
			if (temp == s->top) // 진짜 top 값일 때
				printf("%d <- top\n", peek(s)); // top 표시
			else // 진짜 top 값이 아닐 때
				printf("%d\n", peek(s)); // 스택의 요소만 표시
			(s->top)--; // 스택의 값을 제거하는 것이 아니라, 스택의 top을 한 칸씩 내린다는 의미
		}
	}
	s->top = temp; // top 복원
	printf("--\n");
}

int main(void) {
	StackType s;

	init(&s);
	stack_print(&s);
	push(&s, 10);
	stack_print(&s);
	push(&s, 20);
	stack_print(&s);
	push(&s, 30);
	stack_print(&s);
	push(&s, 40);
	stack_print(&s);
	pop(&s, 30);
	stack_print(&s);
	push(&s, 50);
	stack_print(&s);
	pop(&s, 50);
	stack_print(&s);
	pop(&s, 20);
	stack_print(&s);
	pop(&s, 10);
	stack_print(&s);

	return 0;
}