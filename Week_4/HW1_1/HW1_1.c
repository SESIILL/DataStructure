#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 5

typedef int element;
typedef struct {
	element array[MAX_LIST_SIZE]; // 배열 정의
	int size; // 현재 리스트에 저장된 항목들의 개수
} ArrayListType;

// 오류 처리 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
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
	printf("[리스트 끝]\n");
}

void insert_last(ArrayListType* L, element item) {
	if (is_full(L))
		error("리스트 오버플로우");
	L->array[L->size] = item;
	L->size++;
}

void insert(ArrayListType* L, int pos, element item) {
	// 리스트가 꽉 차 있지 않고, 0 <= pos <= 마지막 인덱스 + 1 이면(마지막 인덱스에 삽입할 수도 있기 때문)
	if (is_full(L))
		printf("리스트 오버플로우\n");
	else if (pos >= 0 && pos <= L->size) {
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

/* 함수 추가 */

void clear(ArrayListType* L) {
	for (int i = 0; i < L->size; i++)
		delete(L, 0); // 항상 첫 번째 요소를 삭제
	L->size = 0; // 리스트의 크기를 0으로 설정
}

void insert_first(ArrayListType* L, element item) {
	if (is_full(L))
		printf("리스트 오버플로우\n");
	else {
		for (int i = (L->size - 1); i >= 0; i--) // 마지막 인덱스 ~ 첫 번째 인덱스
			L->array[i + 1] = L->array[i]; // 뒷자리로 하나씩 이동
		L->array[0] = item; // pos 자리에 item 삽입 후
		L->size++; // size 늘려줌.
	}
}

int get_length(ArrayListType* L) {
	return L->size;
}

void replace(ArrayListType* L, int pos, element item) {
	L->array[pos] = item;
}

int is_in_list(ArrayListType* L, element item) {
	for (int i = 0; i < L->size; i++) {
		if (L->array[i] == item)
			return 1;
	}
	return 0;
}

void delete_by_key(ArrayListType* L, element key) {
	int i;
	for (i = 0; i < L->size; i++) {
		if (L->array[i] == key) {
			delete(L, i);
			break;
		}
	}
	if (i == L->size)
		printf("삭제하려는 값 %d는 리스트에 없습니다.\n", key);
}

int main(void) {
	ArrayListType list1;
	
	init(&list1);

	insert(&list1, 0, 20);
	insert(&list1, 0, 10);
	print_list(&list1);
	
	clear(&list1);
	print_list(&list1);
	
	insert_last(&list1, 90);
	print_list(&list1);
	
	insert(&list1, 0, 30);
	insert(&list1, 0, 20);
	insert(&list1, 0, 10);
	print_list(&list1);
	
	delete(&list1, 2);
	print_list(&list1);
	
	printf("\n-이 이후는 HW1_1에서 추가한 함수들 테스트-\n");
	insert_first(&list1, 9); print_list(&list1);
	insert_last(&list1, 99); print_list(&list1);
	insert_first(&list1, 1); print_list(&list1); // 리스트 오버플로우 출력

	printf("길이는 %d\n", get_length(&list1));
	printf("3번째 데이타는 %d\n", get_entry(&list1, 2));
	
	replace(&list1, 3, 40); print_list(&list1); // list1의 3을 40으로 교환

	printf("20은 리스트에 %s\n", is_in_list(&list1, 20) ? "있습니다." : "없습니다.");
	printf("22는 리스트에 %s\n", is_in_list(&list1, 22) ? "있습니다." : "없습니다.");
	
	delete_by_key(&list1, 20); print_list(&list1);
	delete_by_key(&list1, 22); print_list(&list1);

	return 0;
}