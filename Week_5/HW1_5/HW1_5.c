// [이중연결리스트로 구현된 ADT]
#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct DListNode { // 이중연결 노드 타입
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

// 이중 연결 리스트를 초기화
void init(DListNode* phead) {
	phead->llink = phead;
	phead->rlink = phead;
}

// 이중 연결 리스트의 노드를 출력
void print_dlist(DListNode* phead) {
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

// 새로운 데이터를 노드 before의 오른쪽에 삽입한다.
void dinsert(DListNode* before, element data) {
	DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
	newNode->data = data;
	newNode->llink = before;
	before->rlink->llink = newNode;
	newNode->rlink = before->rlink;
	before->rlink = newNode;
}

// 노드 removed를 삭제한다.
void ddelete(DListNode* head, DListNode* removed) {
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

void print_reverse_dlist(DListNode* phead) {
	DListNode* p;
	for (p = phead->llink; p != phead; p = p->llink) {
		printf("<-| |%d| |-> ", p->data);
	}
	printf("\n");
}

DListNode* search(DListNode* head, element data) {
	DListNode* p;
	if (head == NULL) { // 노드 0개
		return NULL;
	}
	else { // 노드 1개 이상
		p = head->rlink;
		while (p != head) {
			if (p->data == data)
				return p;
			p = p->rlink; // 마지막 노드까지 이동
		}
		return NULL;
	}
	return NULL;
}

// 이중 연결 리스트 테스트 프로그램
int main(void) {
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	
	init(head);

	dinsert(head, 10);
	dinsert(head, 20);
	dinsert(head, 30);
	dinsert(head, 40);
	dinsert(head, 50);

	print_dlist(head); // 50 -> 40 -> 30 -> 20 -> 10
	print_reverse_dlist(head); // 10 -> 20 -> 30 -> 40 -> 50

	head = search(head, 10);
	printf("%d\n", head->data);

	free(head);

	return 0;
}