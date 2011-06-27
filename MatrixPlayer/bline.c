
#ifndef X_SIZE
#define X_SIZE 25
#define Y_SIZE 15
#endif

void plot(char *board, int x, int y)
{
	if (y >= Y_SIZE || y < 0 || x >= X_SIZE || x < 0)
		return;
	board[X_SIZE * y + x] = 1;
}

/*
 * Bresenham's line drawing algorithm.
 */
void bline(char *board, int x1, int y1, int x2, int y2)
{
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;

	dx = x2 - x1;
	if (dx < 0)
		dx = -dx;

	dy = y2 - y1;
	if (dy < 0)
		dy = -dy;

	incx = (x2 < x1) ? -1 : 1;
	incy = (y2 < y1) ? -1 : 1;

	if (dx > dy) {
		plot(board, x1, y1);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for (i = 0; i < dx; i++) {
			if (e >= 0) {
				y1 += incy;
				e += inc1;
			} else {
				e += inc2;
			}
			x1 += incx;
			plot(board, x1, y1);
		}
	} else {
		plot(board, x1, y1);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for (i = 0; i < dy; i++) {
			if (e >= 0) {
				x1 += incx;
				e += inc1;
			} else {
				e += inc2;
			}
			y1 += incy;
			plot(board, x1, y1);
		}
	}
}
