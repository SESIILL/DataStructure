#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_STACK_SIZE 3
#define MAX_STRING 100

// element: [int, string]
typedef struct {
	int num;
	char numString[MAX_STRING];
} element;

// stackType: [int, string], top
typedef struct {
	element stack[MAX_STACK_SIZE];
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
		s->stack[++(s->top)] = item;
}

// 삭제 함수
element pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->stack[(s->top)--];
}

// 피크 함수
element peek(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}
	else
		return s->stack[s->top];
}

// 현재 스택의 모습 출력
void stack_print(StackType* s) {
	int i;
	if (is_empty(s))
		printf("(empty)\n");
	else {
		printf("[%d, %s] <- top\n", s->stack[s->top].num, s->stack[s->top].numString);
		for (i = s->top - 1; i >= 0; i--) 
			printf("[%d, %s]\n", s->stack[i].num, s->stack[i].numString);
	}
	printf("--\n");
}

int main(void) {
	StackType s;
	element e;

	init(&s);
	stack_print(&s);

	e.num = 10; // element의 num 부분
	strcpy(e.numString, "ten"); // element의 numString 부분
	push(&s, e); // element가 구조체 타입이므로 push에 element 자체를 넣는다.
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
