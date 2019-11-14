#include <stdio.h>

int main() {
	int i;
	char z[10][20] = {"m0","m1","m2","m3","m4","m5","m6","m7","m8","m9"};
	clrscr();
	for (i = 0; i < 10; i++) {
		printf("%s\n", z[i]); // %s is format specifier
	}
	getch();
	return 0;
}
