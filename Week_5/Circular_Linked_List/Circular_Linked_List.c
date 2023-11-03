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
	printf("%d", p->data); // 마지막 노드 출력
	printf("\n");
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

ListNode* insert_last(ListNode * head, element data) {
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

int main(void) {
	ListNode* head = NULL;

	head = insert_last(head, 20);
	print_list(head); // 20
	head = insert_last(head, 30);
	print_list(head); // 20 -> 30
	head = insert_last(head, 40);
	print_list(head); // 20 -> 30 -> 40
	head = insert_first(head, 10);
	print_list(head); // 10 -> 20 -> 30 -> 40
	head = delete_first(head);
	print_list(head); // 20 -> 30 -> 40

	return 0;
}