#include <DATOS.H>

int main() {
	clrscr();
	gVar1 = 25;
	gVar2 = 50;
	printf("%d %d\n", gVar1, gVar2);
	swap(&gVar1, &gVar2);
	printf("%d %d\n", gVar1, gVar2);
	getch();
	return 0;
}

// void swap(unsigned *a, unsigned *b) {
// 	*a = *a ^ *b;
// 	*b = *a ^ *b;
// 	*a = *a ^ *b;
// }
