// [단순연결리스트]
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_PER_LINE 100

typedef struct { // 한 라인을 포함하는 노드를 구성하기 위해 element의 타입 변경
    char line[MAX_CHAR_PER_LINE];
}element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
}ListNode;

char askChoice(void) {
    char choice;
    printf("------------------------------\n");
    printf("a: 텍스트 끝에 라인 추가\n");
    printf("i: 라인 번호로 라인 추가\n");
    printf("d: 라인 번호로 라인 삭제\n");
    printf("v: 라인 번호로 해당 라인 출력\n");
    printf("p: 전체 텍스트 출력\n");
    printf("q: 끝\n");
    printf("메뉴 선택: ");
    scanf("%c", &choice);
    return choice;
}

// 오류 처리 함수
void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void display_te(ListNode* head) {
	int i = 1;
	ListNode* p;
	if (head == NULL)
		return;
	printf("--------text edited--------\n");
	for (p = head; p != NULL; p = p->link) 
		printf("(%d) %s", i++, p->data.line);
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert_next(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link; // pre가 가리키는 곳을 p가 가리키게 한다.
	pre->link = p; // pre는 p를 가리킨다.
	return head;
}

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head; // 먼저 p가 헤드를 가리키고
	head = p; // 헤드는 p를 가리킨다.
	return head;
}

ListNode* insert_last(ListNode* head, element value) {
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

int get_length(ListNode* head) {
	ListNode* p = head;
	int size = 0;
	while (p != NULL) { // 마지막 노드까지 전부 처리
		size++;
		p = p->link;
	}
	return size;
}

element* get_entry(ListNode* head, int pos) {
	ListNode* p = head;
	if (pos < 0 || pos >= get_length(head))
		error("위치 오류");
	if (head == NULL) // 노드 개수 0개
		return NULL;
	else { // 노드 개수 1개 이상
		for (int i = 0; i < pos; i++)
			p = p->link;
		return p->data.line;
	}
	return NULL;
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

int main(void) {
    ListNode* list = NULL;
    char choice;
    int lineNb;
    element newElement;

    while ((choice = askChoice()) != 'q') {
        switch (choice) {
        case 'a':
            printf("텍스트 끝에 삽입할 라인: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
            list = insert_last(list, newElement);
            display_te(list);
            break;
        case 'i':
            printf("삽입할 라인 번호: ");
            scanf("%d", &lineNb);
            printf("삽입할 라인: ");
            while (getchar() != '\n');
            fgets(newElement.line, MAX_CHAR_PER_LINE, stdin);
            list = insert_pos(list, lineNb - 1, newElement);
            display_te(list);
            break;
        case 'd':
            printf("삭제할 라인 번호: ");
            scanf("%d", &lineNb);
            while (getchar() != '\n');
            list = delete_pos(list, lineNb - 1);
            display_te(list);
            break;
        case 'v':
            printf("출력할 라인 번호: ");
            scanf("%d", &lineNb);
            while (getchar() != '\n');
            printf("(%d) %s", lineNb, get_entry(list, lineNb - 1));
            break;
        case 'p':
            display_te(list);
            while (getchar() != '\n');
        }
    }
    
    return 0;
}