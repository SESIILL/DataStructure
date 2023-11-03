#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert_next(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link; // pre가 가리키는 곳을 p가 가리키게 한다.
	pre->link = p; // pre는 p를 가리킨다.
	return head;
}

ListNode* insert_first(ListNode* head, int value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head; // 먼저 p가 헤드를 가리키고
	head = p; // 헤드는 p를 가리킨다.
	return head;
}

ListNode* insert_last(ListNode* head, int value) {
	ListNode* temp = head;
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;
	if (head == NULL) // 공백 리스트이면
		head = p; // head가 p를 가리키게 해 줌.
	else {
		while (temp->link != 0) // null이 아닐 때까지
			temp = temp->link; // temp 전진
		temp->link = p; // 현재 temp가 p를 가리키게 한다.
	}
	return head;
}

ListNode* insert_pos(ListNode* head, int pos, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = NULL;

	if (pos == 0) { // 헤드에 노드를 삽입하는 경우
		p->link = head;
		head = p;
	}
	else {
		ListNode* temp = head;
		int currentPos = 0; // 현재 위치
		while (temp != NULL && currentPos < pos - 1) { // temp: pos - 1 까지 전진
			temp = temp->link;
			currentPos++;
		}
		p->link = temp->link; // p가 pos(pos-1이 가리키는 곳)를 가리키게 함.
		temp->link = p; // pos가 p를 가리키게 함.
	}
	return head;
}

// pre가 가리키는 노드의 다음 노드를 삭제한다.
ListNode* delete_next(ListNode* head, ListNode* pre) {
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL) error("삭제할 항목이 없음");
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete_last(ListNode* head) {
	ListNode* temp = head;
	ListNode* prevTemp = temp; // 항상 temp의 직전에 있음
	ListNode* removed;
	if (head == NULL) error("삭제할 항목이 없음");
	if (temp->link == NULL) { // 경우1: 노드가 하나(head가 마지막 노드)
		removed = temp->link;
		temp->link = NULL; // 빈 노드로 변경
		free(removed);
		return NULL;
	}
	else { // 경우2: 노드가 2개 이상
		while (temp->link != NULL) {
			prevTemp = temp;
			temp = temp->link;
		}
		removed = temp;
		prevTemp->link = NULL; // prevTemp를 마지막 노드로 변경
		free(removed); // removed 없애기
		return head;
	}
}

void display(ListNode* head) {
	ListNode* p;
	printf("[ ");
	for (p = head; p != NULL; p = p->link) // 마지막 노드까지 전부 처리
		printf("%d ", p->data);
	printf("]\n");
}

ListNode* search(ListNode* head, int x) {
	ListNode* p;
	p = head;
	while (p != NULL) { // 마지막 노드까지 전부 처리 
		if (p->data == x) return p; // 탐색 성공
		p = p->link;
	}
	return NULL; // 탐색 실패일 경우 NULL 반환
}

ListNode* concat(ListNode* head1, ListNode* head2) {
	ListNode* p;
	if (head1 == NULL) return head2; // head1이 비어 있는 경우
	else if (head2 == NULL) return head1; // head2이 비어 있는 경우
	else {
		p = head1;
		while (p->link != NULL) // 마지막 노드까지 전부 처리
			p = p->link; // 맨 끝 노드까지 이동
		p->link = head2; // 맨 끝 노드의 link를 head2에 연결
		return head1; // head = head1
	}
}

ListNode* reverse(ListNode* head) {
	ListNode* p, * q, * r; // (후) r -> q -> p (전)
	p = head; // p는 역순으로 만들 리스트
	q = NULL; // q는 역순으로 만들 노드
	while (p != NULL) { // 마지막 노드까지 전부 처리
		r = q;
		q = p;
		p = p->link;
		q->link = r; // q의 링크 방향을 바꾼다.
	}
	return q; // q는 역순으로 된 리스트의 헤드 포인터
}

// item이 리스트에 있으면 1, 없으면 0 반환
int is_in_list(ListNode* head, element item) {
	ListNode* p = head;
	while (p != NULL) { // 마지막 노드까지 전부 처리
		if (p->data == item)
			return 1;
		p = p->link;
	}
	return 0;
}

int get_length(ListNode* head) {
	ListNode* p = head;
	int size = 0;
	while (p != NULL) { // 마지막 노드까지 전부 처리
		size++;
		p = p->link;
	}
	return size;
}

int get_total(ListNode* head) {
	ListNode* p;
	int total = 0;
	p = head;
	while (p != NULL) { // 마지막 노드까지 전부 처리
		total += p->data;
		p = p->link;
	}
	return total;
}

element get_entry(ListNode* head, int pos) {
	ListNode* p = head;
	if (pos < 0 || pos >= get_length(head))
		error("위치 오류");
	if (head == NULL) // 노드 개수 0개
		return NULL;
	else { // 노드 개수 1개 이상
		for (int i = 0; i < pos; i++)
			p = p->link;
		return p->data;
	}
	return NULL;
}

ListNode* delete_by_key(ListNode* head, int key) {
	ListNode* p = head;
	ListNode* prev = NULL;
	if (head == NULL)
		error("삭제할 항목이 없음.");
	while (p != NULL) {
		if (p->data == key) {
			if (prev == NULL)
				head = delete_first(head);
			else
				head = delete_next(head, prev);
			return head; // 수정된 부분: 노드를 찾아 삭제한 경우 head 반환
		}
		prev = p;
		p = p->link;
	}
	printf("삭제하려는 값 %d는 리스트에 없습니다.\n", key);
	return head; // 리스트에 해당 값이 없는 경우 head 반환
}

ListNode* delete_pos(ListNode* head, int pos) {
	ListNode* p = head;
	ListNode* prev = NULL;

	if (pos < 0 || pos >= get_length(head))
		error("위치 오류");
	if (head == NULL) // 노드 개수 0개
		error("삭제할 항목이 없음.");

	// 이제부터는 유효 pos 내의 값만 검사한다.
	for (int i = 0; i < pos; i++) {
		prev = p;
		p = p->link;
	}
	if (prev == NULL) // 첫 번째 노드를 삭제하는 경우
		head = delete_first(head);
	else // 중간이나 마지막 노드를 삭제하는 경우
		head = delete_next(head, prev);
	return head;
}

// 게임 아이템 추가 함수
void add_item(ListNode** phead, int new_item) {
	int total = 0;
	ListNode* temp = *phead;
	while (temp != NULL) { // 노드 끝까지 처리
		total += temp->data;
		temp = temp->link;
	}
	if (total + new_item <= 100) 
		// 리스트의 끝에 새로운 아이템 추가
		*phead = insert_first(*phead, new_item);
	else 
		printf("최대 무게 100kg 초과로 아이템 %d를 추가할 수 없습니다.\n", new_item);
}

ListNode* delete_by_weight(ListNode** phead, int key) {
	ListNode* p = *phead;
	ListNode* prev = NULL;
	if (phead == NULL)
		error("삭제할 항목이 없습니다.");
	while (p != NULL) {
		if (p->data == key) {
			if (prev == NULL)
				*phead = delete_first(*phead);
			else
				*phead = delete_next(*phead, prev);
			return *phead; // 수정된 부분: 노드를 찾아 삭제한 경우 head 반환
		}
		prev = p;
		p = p->link;
	}
	printf("아이템 %d를 보유하고 있지 않습니다.\n", key);
	return *phead; // 리스트에 해당 값이 없는 경우 head 반환
}

int main(void) {
	ListNode* list = NULL;
	char choice;
	int weight;

	while (1) {
		printf("enter a(dd), d(elete), q(uit): ");
		scanf(" %c", &choice);

		if (choice == 'q')
			break;

		printf("enter the weight of the item: ");
		scanf("%d", &weight);

		if (choice == 'a') {
			add_item(&list, weight);
			display(list);
		}
		else {
			list = delete_by_weight(&list, weight);
			display(list);
		}
		while (getchar() != '\n');
	}
	
	return 0;
}