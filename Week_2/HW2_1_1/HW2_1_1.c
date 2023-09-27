#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_STACK_SIZE 3

// 스택을 위한 타입 정의(int)
typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE]; // int data[100]
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
	int i;
	if (is_empty(s)) // 스택이 비어 있는 경우
		printf("(empty)\n");
	else {
		printf("%d <- top\n", s->data[s->top]);
		for (i = s->top - 1; i >= 0; i--)
			printf("%d\n", s->data[i]);
	}
	printf("--\n");
}

int main(void) {
	StackType s;

	init(&s);
	stack_print(&s);
	push(&s, 10); // element가 구조체 타입이 아니므로 push에 정수형을 넣는다.
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