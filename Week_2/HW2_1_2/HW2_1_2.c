#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 3
#define MAX_STRING 100

typedef struct {
	int num;
	char numString[MAX_STRING];
} element;

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
		printf("[%d, %s] <- top\n", s->data[s->top].num, s->data[s->top].numString);
		for (int i = s->top - 1; i >= 0; i--)
			printf("[%d, %s]\n", s->data[i].num, s->data[i].numString);
	}
	printf("--\n");
}

int main(void) {
	stackType s;
	element e;

	init_stack(&s);
	stack_print(&s);

	e.num = 10;
	strcpy(e.numString, "ten");
	push(&s, e);
	stack_print(&s);

	e.num = 20;
	strcpy(e.numString, "twenty");
	push(&s, e);
	stack_print(&s);

	e.num = 30;
	strcpy(e.numString, "thirty");
	push(&s, e);
	stack_print(&s);

	e.num = 40;
	strcpy(e.numString, "forty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);
	
	e.num = 50;
	strcpy(e.numString, "fifty");
	push(&s, e);
	stack_print(&s);

	pop(&s);
	stack_print(&s);

	pop(&s);
	stack_print(&s);
	
	pop(&s);
	stack_print(&s);

	return 0;
}