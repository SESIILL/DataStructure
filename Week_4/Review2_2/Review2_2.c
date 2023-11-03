#include <stdio.h>
#include <stdlib.h>

// 자기 참조 구조체 선언
typedef struct ListNode { 
	int number;
	struct ListNode* link;
} ListNode; 

void displayList1(ListNode* head) {
	ListNode* temp = head;
	while (temp != NULL) { // 노드리스트 전부 처리
		printf("%d -> ", temp->number);
		temp = temp->link;
	}
	printf("NULL\n");
}

void displayList2(ListNode* head) {
	ListNode* temp = head;
	if (temp == NULL) 
		printf("NULL\n");
	else {
		printf("%d -> ", temp->number);
		displayList2(temp->link);
	}
}

int main(void) {
	ListNode* head, * newNode, * temp;

	// 1) head -> [10, NULL]
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 10; // value
	newNode->link = NULL;
	head = newNode;

	// 2) head -> 10 -> [20, NULL]
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 20;
	newNode->link = NULL;
	head->link = newNode; // 헤드가 가리키는 곳(10)은 newNode(20)이다.

	// 3) head -> 10 -> 20 -> [30, NULL]
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 30;
	newNode->link = NULL;
	head->link->link = newNode;

	// 4) head -> 10 -> 20 -> 30 -> [44, NULL]
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 44;
	newNode->link = NULL;
	temp = head;
	while (temp->link != NULL) // 마지막 노드까지 전진(마지막 노드는 처리 전)
		temp = temp->link;
	temp->link = newNode; // 마지막 노드(30)가 가리키는 곳은 newNode(44)이다.

	// 5) head -> 1 -> 10 -> 20 -> 30 -> [44, NULL]
	newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->number = 1;
	newNode->link = head; // newNode(1)가 head(10)을 가리키게 하고
	head = newNode; // head(10)이 newNode(1)을 가리키게 한다. (순서가 바뀌면 데이터를 잃게 됨)

	displayList1(head);
	displayList2(head);

	return 0;
}