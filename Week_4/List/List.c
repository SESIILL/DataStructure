#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
	element array[MAX_LIST_SIZE]; // 배열 정의
	int size; // 현재 리스트에 저장된 항목들의 개수
} ArrayListType;

// 오류 처리 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 리스트 초기화 함수
void init(ArrayListType* L) {
	L->size = 0;
}

// 리스트가 비어 있으면 1 반환, 그렇지 않으면 0 반환
int is_empty(ArrayListType* L) {
	return L->size == 0;
}

// 리스트가 가득 차 있으면 1 반환, 그렇지 않으면 0 반환
int is_full(ArrayListType* L) {
	return L->size == MAX_LIST_SIZE;
}

element get_entry(ArrayListType* L, int pos) {
	if (pos < 0 || pos >= L->size) // 유효하지 않은 인덱스
		error("위치 오류");
	return L->array[pos];
}

void print_list(ArrayListType* L) {
	int i;
	for (i = 0; i < L->size; i++) 
		printf("%d -> ", L->array[i]);
	printf("\n");
}

void insert_last(ArrayListType* L, element item) {
	if (is_full(L))
		error("리스트 오버플로우");
	L->array[L->size] = item;
	L->size++;
}

void insert(ArrayListType* L, int pos, element item) {
	// 리스트가 꽉 차 있지 않고, 0 <= pos <= 마지막 인덱스 + 1 이면(마지막 인덱스에 삽입할 수도 있기 때문)
	if (!is_full(L) && (pos >= 0 && pos <= L->size)) { 
		for (int i = (L->size - 1); i >= pos; i--) // 마지막 인덱스 요소부터 pos 인덱스 요소까지
			L->array[i + 1] = L->array[i]; // 뒷자리로 하나씩 이동
		L->array[pos] = item; // pos 자리에 item 삽입 후
		L->size++; // size 늘려줌.
	}
}

element delete(ArrayListType* L, int pos) {
	element item;
	if (pos < 0 || pos >= L->size) // 유효하지 않은 범위
		error("위치 오류");
	item = L->array[pos]; // 삭제하고 반환할 item 미리 넣어둠.
	for (int i = pos; i < (L->size - 1); i++) // pos 요소부터 마지막 인덱스 - 1 요소까지
		L->array[i] = L->array[i + 1]; // 하나씩 앞으로 이동
	L->size--; // size 하나 감소
	return item;
}

int main(void) {
	ArrayListType list;
	
	init(&list);
	insert(&list, 0, 10); print_list(&list); // 0번째 위치에 10 추가
	insert(&list, 0, 20); print_list(&list); // 0번째 위치에 20 추가
	insert(&list, 0, 30); print_list(&list); // 0번째 위치에 30 추가
	insert_last(&list, 40); print_list(&list); // 맨 끝에 40 추가
	delete(&list, 0); print_list(&list); // 0번째 항목 삭제
	
	return 0;
}
