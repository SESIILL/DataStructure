#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void print_reverse(char *str, int end) {
	if (end < 0)
		printf("\n");
	else {
		printf("%c", str[end]);
		print_reverse(str, end - 1);
	}
}

int main(void) { 
	char str[100]; 
	printf("Enter any string: "); 
	scanf("%s", str); 
	printf("Reversed String is: "); 
	print_reverse(str, strlen(str) - 1); // str과 마지막 인덱스를 매개변수로 
	
	return 0;
} 