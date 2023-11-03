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
ListNode* delete_next(ListNode *head, ListNode *pre) {
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

void print_list(ListNode* head) {
	ListNode* p;
	for (p = head; p != NULL; p = p->link) // 마지막 노드까지 전부 처리
		printf("%d -> ", p->data);
	printf("NULL\n");
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

int main(void) {
	ListNode* head1 = NULL;
	ListNode* head2;

	int i;
	for (i = 0; i < 5; i++) {
		head1 = insert_last(head1, i * 10);
		print_list(head1);
	}

	head2 = reverse(head1);
	print_list(head2);

	head2 = insert_pos(head2, 1, 99);
	print_list(head2);
	
	head2 = delete_last(head2);
	print_list(head2);
	
	head1 = NULL; // head1 초기화(연결 끊음)
	head1 = insert_first(head1, 100);
	head1 = insert_first(head1, 200);
	print_list(head1);
	
	head1 = concat(head1, head2);
	print_list(head1);
	print_list(head2); // 여전히 40 -> 39 -> 30 -> 20 -> 10

	return 0;
}