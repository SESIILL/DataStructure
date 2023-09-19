#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 3
#include <stdio.h>
#include <string.h>

// [number, string] 형식의 element 구조체
typedef struct {
    int num;
    char str[20]; // 문자열을 저장할 배열 추가
} element;

// element 여러 개를 담을 구조체
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
void push(StackType* s, int num, const char* str) { // 읽기 전용 문자열 포인터
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else {
        s->top++; // top을 증가시킨 후
        s->data[s->top].num = num; // 구조체 s -> 구조체 element -> top -> num -> num 삽입
        strcpy(s->data[s->top].str, str); // 구조체 s -> 구조체 element -> top -> str -> str 삽입
    }
}

// 삭제 함수
void pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        return;
    }
    else 
        s->top--;
}

// 현재 스택의 모습 출력
void stack_print(StackType* s) {
    int temp = s->top; // temp에 top 값을 옮겨 둠.
    if (is_empty(s)) // 스택이 비어 있는 경우
        printf("<empty>\n");
    else {
        while (!is_empty(s)) {
            if (temp == s->top)
                printf("[%d, \"%s\"] <- top\n", s->data[s->top].num, s->data[s->top].str);
            else
                printf("[%d, \"%s\"]\n", s->data[s->top].num, s->data[s->top].str);
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
    push(&s, 10, "ten");
    stack_print(&s);
    push(&s, 20, "twenty");
    stack_print(&s);
    push(&s, 30, "thirty");
    stack_print(&s);
    push(&s, 40, "forty");
    stack_print(&s);
    pop(&s);
    stack_print(&s);
    push(&s, 50, "fifty");
    stack_print(&s);
    pop(&s);
    stack_print(&s);
    pop(&s);
    stack_print(&s);
    pop(&s);
    stack_print(&s);

    return 0;
}