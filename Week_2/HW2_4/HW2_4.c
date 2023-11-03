#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 10

typedef char element;
typedef struct {
	element data[MAX_STRING]; // char data[10]
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
	return (s->top == (MAX_STRING - 1));
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

int palindrome(char str[]) {
	StackType s;
	int i;

	init(&s); // 스택 초기화

	// str의 문자들을 스택에 넣는다.
	for (i = 0; str[i] != '\0'; i++) 
		push(&s, str[i]);

	// 스택에서 하나씩 빼면서 str의 문자들과 차례로 비교
	i = 0;
	while (!is_empty(&s)) {
		if (pop(&s) != str[i]) 
			return 0;
		i++;
	}
	return 1;
}

int main(void) {
	char word[MAX_STRING];
	
	printf("Enter a word to check palindrome: ");
	scanf("%s", word);
	
	if (palindrome(word))
		printf("palindrome입니다.\n");
	else
		printf("palindrome이 아닙니다.\n");

	return 0;
}