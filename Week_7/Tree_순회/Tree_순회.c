#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };

TreeNode* root = &n6;

// 중위 순회(왼쪽 -> 루트 -> 오른쪽)
inorder(TreeNode* root) {
	if (root) {
		inorder(root->left); // 왼쪽 서브트리 재귀로 순회
		printf("%d ", root->data); // 루트 노드 출력
		inorder(root->right); // 오른쪽 서브트리 재귀로 순회
	}
}

// 전위 순회(루트 -> 왼쪽 -> 오른쪽)
preorder(TreeNode* root) {
	if (root) {
		printf("%d ", root->data); // 루트 노드 출력
		preorder(root->left); // 왼쪽 서브트리 재귀로 순회
		preorder(root->right); // 오른쪽 서브트리 재귀로 순회
	}
}

// 후위 순회 (왼쪽 -> 오른쪽 -> 루트)
postorder(TreeNode* root) {
	if (root) {
		postorder(root->left); // 왼쪽 서브트리 재귀로 순회
		postorder(root->right); // 오른쪽 서브트리 재귀로 순회
		printf("%d ", root->data); // 루트 노드 출력
	}
}

int main(void) {
	printf("[중위 순회]\n");
	inorder(root);
	printf("\n\n");

	printf("[전위 순회]\n");
	preorder(root);
	printf("\n\n");

	printf("[후위 순회]\n");
	postorder(root);
	printf("\n");

	return 0;
}