// [원형연결리스트로 구현된 ADT]
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode { // 노드 타입
	element data;
	struct ListNode* link;
} ListNode;

void print_list(ListNode* head) {
	ListNode* p;
	if (head == NULL) return;
	p = head->link;
	while (p != head) { // 마지막 노드 직전까지
		printf("%d -> ", p->data);
		p = p->link;
	}
	printf("%d -> ", p->data); // 마지막 노드 출력
	printf("[리스트 끝]\n");
}

ListNode* insert_first(ListNode* head, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) { // 노드가 없는 경우
		head = node;
		node->link = head;
	}
	else { // 노드가 하나 이상
		node->link = head->link;
		head->link = node;
	}
	return head;
}

ListNode* insert_last(ListNode* head, element data) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->data = data;
	if (head == NULL) { // 노드가 없는 경우
		head = node;
		node->link = head;
	}
	else { // 노드가 하나 이상
		node->link = head->link;
		head->link = node;
		head = node;
	}
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* temp;
	if (head == NULL) {
		printf("리스트가 비어 삭제를 못함.\n");
		return NULL;
	}
	else if (head == head->link) { // 노드가 하나인 경우
		temp = head;
		head = NULL;
		free(temp);
	}
	else {
		temp = head->link;
		head->link = temp->link;
		free(temp);
	}
	return head;
}

// 함수 추가
ListNode* delete_last(ListNode* head) {
	ListNode* last, * prev;
	if (head == NULL) { // 노드 0개
		printf("리스트가 비어 삭제를 못함\n");
		return NULL;
	}
	else if (head->link == head) { // 노드 1개
		free(head); // 노드 해제
		head = NULL; // head를 NULL로 설정하여 빈 리스트로 만듦
	}
	else { // 노드 2개 이상
		last = head->link;
		prev = NULL;
		while (last != head) { 
			prev = last; // 마지막 노드의 직전까지 이동
			last = last->link; // 마지막 노드까지 이동
		}
		prev->link = head->link;
		head = prev;
		free(last);	
	}
	return head;
}

int get_size(ListNode* head) {
	ListNode* p;
	int size = 1;
	if (head == NULL) return 0;
	for (p = head; p->link != head; p = p->link) // 리스트 전체 순회
		size++;
	return size;
}

ListNode* search(ListNode* head, element data) {
	ListNode* p;
	if (head == NULL) { // 노드 0개
		return NULL;
	}
	else { // 노드 1개 이상
		p = head->link;
		while (p != head) {
			if (p->data == data)
				return p;
			p = p->link; // 마지막 노드까지 이동
		}
		return NULL;
	}
	return NULL;
}

int main(void) {
	ListNode* head = NULL;

	head = insert_last(head, 10);
	head = insert_last(head, 20);
	head = insert_last(head, 30);
	head = insert_last(head, 30);
	head = insert_last(head, 50);
	print_list(head); // 10 -> 20 -> 30 -> 30 -> 50

	head = delete_last(head);
	print_list(head); // 10 -> 20 -> 30 -> 30

	head = search(head, 30);
	printf("%d\n", head->data);

	printf("리스트 사이즈: %d\n", get_size(head));

	return 0;
}