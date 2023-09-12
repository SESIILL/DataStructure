#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct { 
	int midterm;
	int final;
} Score;

void printScore(Score* p) {
	printf("중간고사 성적은 %d\n", p->midterm);
	printf("학기말고사 성적은 %d\n", p->final);
}

Score* biggerScore(Score* p1, Score* p2) {
	if (p1->midterm + p1->final >= p2->midterm + p2->final) 
		return p1;
	else 
		return p2;
}

Score* totalScore(Score* p1, Score* p2) {
	Score* temp;
	temp = (Score*)malloc(sizeof(Score));
	temp->midterm = p1->midterm + p2->midterm;
	temp->final = p1->final + p2->final;
	return temp;
}

Score* createScore(int m, int f) {
	Score* temp;
	temp = (Score*)malloc(sizeof(Score));
	temp->midterm = m;
	temp->final = f;
	return temp;
}

int main(void) {
	Score* p1, * p2, * p3;

	// p1, p2에 Score을 저장하기 위한 메모리를 할당
	p1 = (Score*)malloc(sizeof(Score));
	p2 = (Score*)malloc(sizeof(Score));

	// 값 대입
	p1->midterm = 50;
	p1->final = 100;
	p2->midterm = 70;
	p2->final = 70;

	printScore(p1);
	printScore(p2);
	
	printf("-----------------------------\n");
	printf("둘중 성적이 좋은 점수:\n");
	printScore(biggerScore(p1, p2));
	printf("-----------------------------\n");
	printf("두 성적의 총합:\n");
	printScore(totalScore(p1, p2));
	printf("-----------------------------\n");
	
	p3 = createScore(100, 100);
	printScore(p3);

	free(p1);
	free(p2);
	free(p3);

	return 0;
}