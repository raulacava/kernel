/* Proceso 2
 * La Pelotita
 */
#include <graphics.h>
#include <conio.h>

#define ESC 27

int main() {
	int gd = DETECT, gm;
	int r = 10;
	int xs = 2, ys = 2;
	int x = r, y = r, x0 = r, y0 = r;
	char key;

	initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
//	setviewport(getmaxx()/2, 0, getmaxx(), getmaxy()/2, 1);

	while(key != ESC) {
		if (kbhit()) key = getch();

		x += xs;
		y += ys;
//		rectangle(0,0,getmaxx()/2,getmaxy()/2);
		circle(x, y, r);
		floodfill(x, y, WHITE);
		line(x0, y0, x, y);
		if (x >= getmaxx() - r || x <= r) { xs = -xs; 
			x0 = x; y0 = y;
		}
		if (y >= getmaxy() - r || y <= r) { ys = -ys; 
			x0 = x; y0 = y;
		}
		delay(5);
		clearviewport();
	}

	closegraph();
	return 0;
}
