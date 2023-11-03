#include <stdio.h>

#define MAX_STACK_SIZE 3

typedef int element;
typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
} stackType;

// 스택 초기화 함수
void init_stack(stackType* s) {
	s->top = -1;
}

// 공백 상태 검출 함수
int is_empty(stackType* s) {
	return (s->top == -1);
}

// 포화 상태 검출 함수
int is_full(stackType* s) {
	return (s->top == (MAX_STACK_SIZE - 1));
}

// 삽입 함수
void push(stackType* s, element item) {
	if (is_full(s)) {
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}
	else 
		s->data[++(s->top)] = item; // top + 1 하고 그 자리에 item 삽입
}

// 삭제 함수
element pop(stackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[(s->top)--]; // top의 값을 반환하고 top - 1
}

// 피크 함수
element peek(stackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->data[s->top];
}

void stack_print(stackType* s) {
	if (is_empty(s))
		printf("<empty>\n");
	else {
		printf("%d <- top\n", s->data[s->top]);
		for (int i = s->top - 1; i >= 0; i--)
			printf("%d\n", s->data[i]);
	}
	printf("--\n");
}

int main(void) {
	stackType s;

	init_stack(&s);
	stack_print(&s);
	push(&s, 10);
	stack_print(&s);
	push(&s, 20);
	stack_print(&s);
	push(&s, 30);
	stack_print(&s);
	push(&s, 40);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	push(&s, 50);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);
	pop(&s);
	stack_print(&s);

	return 0;
}