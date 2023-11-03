#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void reverse_string(char* str, int s, int e) {
	char temp;
	for (int i = s; i <= e / 2; i++) {
		temp = str[e - i];
		str[e - i] = str[i];
		str[i] = temp;
	}
}

int main(void) {
	char str[100];
	printf("Enter any string: ");
	scanf("%s", str);
	reverse_string(str, 0, strlen(str) - 1);
	printf("Reversed String is: %s\n", str);

	return 0;
}