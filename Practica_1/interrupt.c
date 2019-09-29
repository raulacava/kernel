#include <stdio.h>
#include <dos.h>
#include <conio.h>

int i = 0; // Increases every 18.2 ms

void interrupt (*old_Routine)(void);

//void interrupt routine(void);
void interrupt routine(void) {
	disable(); // Disable interrupts
//	i++;
	if ((++i % 50) == 0) { // !(i % 50) - 1 seg
		clrscr();
		printf("+------+\n|%2d sec|\n+------+", i/50);
	}
	enable(); // Enable interrupts
	old_Routine();
}

int main() {
	old_Routine = getvect(0x8); // 0x20
	setvect(0x8, routine);
//	while ((i % 1000) != 0); // 20 seg
	while (i <= 1000); // 20 seg
	setvect(0x8, old_Routine);
//	getch();
	return 0;
}
