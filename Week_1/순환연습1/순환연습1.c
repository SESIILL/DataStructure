#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fact(int n) {
	if (n == 0)
		return 1;
	else
		return n * fact(n - 1); // n! = n * (n-1)!
}

int main(void) {
	int n;
	printf("Enter a number: ");
	scanf("%d", &n);
	printf("%d! = ", n);
	printf("%d\n", fact(n));
	
	return 0;
}