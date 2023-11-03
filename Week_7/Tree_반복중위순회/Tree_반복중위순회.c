// 반복 중위 순회: 재귀를 사용하지 않고, 스택을 이용해 구현
// 중위 순회(왼쪽 -> 루트 -> 오른쪽)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode; 

typedef TreeNode* element; // TreeNode를 가리키는 포인터

typedef struct StackNode {
	element data;
	struct StackNode* link;
}StackNode;

typedef struct StackType {
	StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) {
	s->top = NULL;
}

int is_empty(LinkedStackType* s) {
	return s->top == NULL;
}

void push(LinkedStackType* s, TreeNode* root) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	if (temp == NULL) {
		fprintf(stderr, "메모리 할당 에러\n");
		return;
	}
	else {
		temp->data = root;
		temp->link = s->top;
		s->top = temp;
	}
}

element pop(LinkedStackType* s) {
	StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
	element item;
	if (is_empty(s)) {
		fprintf(stderr, "스택이 비어 있음.\n");
		exit(1);
	}
	else {
		temp = s->top;
		item = temp->data;
		s->top = s->top->link;
		free(temp);
	}
	return item;
}

void inorder_iter(TreeNode* root) {
	LinkedStackType s;
	init(&s);
	while (1) {
		for (; root; root = root->left) // 루트에서 왼쪽으로 이동하면서
			push(&s, root); // 스택에 push
		if (is_empty(&s))
			break;
		else {
			root = pop(&s);
			printf("%d ", root->data);
		}
		root = root->right; // 오른쪽 자식으로 이동
	}
}

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

int main(void) {
	printf("[중위 순회]\n");
	inorder_iter(root);
	printf("\n");

	return 0;
}