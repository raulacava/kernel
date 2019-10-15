void proc3() {
	struct text_info initial_info;
	int a, b, c;
	int x, y, xo, yo;
	char key;
	int p = 3;

	gettextinfo(&initial_info);
	xo = p == 1 || p == 3 ? 0 : initial_info.screenwidth /2;
	yo = p == 1 || p == 2 ? 0 : initial_info.screenheight/2;

	x = initial_info.screenwidth /4;
	y = initial_info.screenheight/4;

	// clrscr();
	while (key != ESC) {
		if (kbhit()) key = getch();
		//genera un numero aleatorio
		a = (int)((rand()/32767.1)*100);
		b = 20+(int)((rand()/3276.1)*11);
		c = 30+(int)((rand()/3276.1)*22);
		disable();
		gotoxy(xo + x - 5, yo + y - 1);
		printf("Numero: %3d", a);
		gotoxy(xo + x - 5, yo + y);
		printf("Numero: %3d", b);
		gotoxy(xo + x - 5, yo + y + 1);
		printf("Numero: %3d", c);
		enable();
		delay(100);
	}
}
