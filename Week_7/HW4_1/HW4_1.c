#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TRUE 1
#define FALSE 0
#define MAX_TREE_SIZE 20

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right;
} TreeNode;

TreeNode n1 = { 15, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 15, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode* root = &n6;

TreeNode m1 = { 15, NULL, NULL };
TreeNode m2 = { 4, &n1, NULL };
TreeNode m3 = { 16, NULL, NULL };
TreeNode m7 = { 28, NULL, NULL }; // 추가
TreeNode m4 = { 25, NULL, &m7 }; // 변경
TreeNode m5 = { 15, &m3, &m4 };
TreeNode m6 = { 15, &m2, &m5 };
TreeNode* root2 = &m6;

// 전위 순회(루트 -> 왼쪽 -> 오른쪽)
void preorder(TreeNode* root) {
	if (root) {
		printf("%d ", root->data); // 루트 노드 출력
		preorder(root->left); // 왼쪽 서브트리 재귀로 순회
		preorder(root->right); // 오른쪽 서브트리 재귀로 순회
	}
}

// 비단말노드의 개수를 반환
int get_nonleaf_count(TreeNode* t) {
	if (t == NULL) 
		return 0;
	else if (t->left == NULL && t->right == NULL) // 단말 노드인 경우
		return 0;
	else // 비단말 노드인 경우
		return 1 + get_nonleaf_count(t->left) + get_nonleaf_count(t->right); // 1 + 오른쪽, 왼쪽 자식에 대해 함수 호출
}

// 자식이 하나인 노드의 개수를 반환
int get_oneleaf_count(TreeNode* t) {
	int count = 0;
	if (t != NULL) { 
		if ((t->left != NULL && t->right == NULL) || (t->left == NULL && t->right != NULL))
			count++;
		if (t->left != NULL) // t->left에 자식이 있는 경우
			count += get_oneleaf_count(t->left); // 그 자식에 대해 함수 호출
		if (t->right != NULL) // t->right에 자식이 있는 경우
			count += get_oneleaf_count(t->right); // 그 자식에 대해 함수 호출
	}
	return count;
}

// 자식이 둘인 노드의 개수를 반환
int get_twoleaf_count(TreeNode* t) {
	int count = 0;
	if (t != NULL) {
		if (t->left != NULL && t->right != NULL)
			count++;
		if (t->left != NULL) // t->left에 자식이 있는 경우
			count += get_twoleaf_count(t->left); // 그 자식에 대해 함수 호출
		if (t->right != NULL) // t->right에 자식이 있는 경우
			count += get_twoleaf_count(t->right); // 그 자식에 대해 함수 호출
	}
	return count;
}

// 이진 트리 노드의 최댓값을 반환
int get_max(TreeNode* t) {
	int max = -1;
	int leftMax, rightMax;
	if (t != NULL) {
		if (t->data > max)
			max = t->data;
		leftMax = get_max(t->left);
		if (max < leftMax)
			max = leftMax;
		rightMax = get_max(t->right);
		if (max < rightMax)
			max = rightMax;
	}
	return max;
}

// 이진 트리 노드의 최솟값을 반환
int get_min(TreeNode* t) {
	int min = 99;
	int leftMin, rightMin;
	if (t != NULL) {
		if (t->data < min)
			min = t->data;
		leftMin = get_min(t->left);
		if (min > leftMin)
			min = leftMin;
		rightMin = get_min(t->right);
		if (min > rightMin)
			min = rightMin;
	}
	return min;
}

// 이진 트리의 노드들의 값을 1씩 증가
void node_increase(TreeNode* t) {
	if (t != NULL) {
		t->data++;
		node_increase(t->left);
		node_increase(t->right);
	}
}

// 두 개의 이진 트리의 동일 여부
int equal(TreeNode* node1, TreeNode* node2) { 
	if (node1 == NULL && node2 == NULL) 
		return 1;
	else if (node1 == NULL || node2 == NULL)
		return 0;
	else if (node1->data != node2->data)
		return 0;
	else // node1->data == node2->data
		return equal(node1->left, node2->left) && equal(node1->right, node2->right);
	return 0;
}

// 주어진 이진 트리를 복제한 새로운 트리를 반환
TreeNode* copy(TreeNode* node) {
	TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL)
		return NULL;
	else {
		newNode->data = node->data;
		newNode->left = copy(node->left);
		newNode->right = copy(node->right);
	}
	return newNode;
}

int main(void) {
	TreeNode* result[MAX_TREE_SIZE];
	TreeNode* clone;
	int i, num;

	printf("가)\n");
	printf("트리 root 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root));
	printf("트리 root2 중 비단말노드의 개수는 %d.\n", get_nonleaf_count(root2));
	printf("트리 root 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root));
	printf("트리 root2 중 자식이 하나만 있는 노드의 개수는 %d.\n", get_oneleaf_count(root2));
	printf("트리 root 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root));
	printf("트리 root2 중 자식이 둘이 있는 노드의 개수는 %d.\n", get_twoleaf_count(root2));
	printf("트리 root 에서 가장 큰 수는 %d.\n", get_max(root));
	printf("트리 root2 에서 가장 큰 수는 %d.\n", get_max(root2));
 	printf("트리 root 에서 가장 작은 수는 %d.\n", get_min(root));
	printf("트리 root2 에서 가장 작은 수는 %d.\n", get_min(root2));

	printf("\n다)\n");
	preorder(root);
	node_increase(root);
	printf("\n");
	preorder(root);
	printf("\n");

	printf("%s\n", equal(root, root) ? "같다" : "다르다");
	printf("%s\n", equal(root2, root2) ? "같다" : "다르다");
	printf("%s\n", equal(root, root2) ? "같다" : "다르다");
	
	printf("\n라)\n");
	clone = copy(root);
	preorder(root);
	printf("\n");
	preorder(clone);
	printf("\n");

	return 0;
}