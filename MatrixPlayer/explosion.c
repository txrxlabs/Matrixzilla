#include <string.h> /* for memset */
#include "MatrixDef.h"

static int xdim;
static int ydim;

#define EXPLOSION_ITERATIONS 1500
#define MAXPARTICLES 45
#define EXPLOSION_CHANCE 10 /* out of 100 */

static struct particle {
	char x;
	char y;
	char vx;
	char vy;
	unsigned char alive;
} p[MAXPARTICLES];

static int alloc_particle(void)
{
	int i;

	for (i = 0; i < MAXPARTICLES; i++)
		if (!p[i].alive) {
			p[i].alive = random(10) + 5;
			return i;
		}
	return -1;
}

static void add_explosion(void)
{
	int i, n, pn, ex, ey;

	if (random(100) > EXPLOSION_CHANCE)
		return;

	n = random(15) + 5;
	ex = random(xdim * 4);
	ey = random(ydim * 4);

	for (i = 0; i < n; i++) {
		pn = alloc_particle();
		if (pn == -1)
			return;
		p[pn].x = ex;
		p[pn].y = ey;
		p[pn].vx = random(10) - 5;
		p[pn].vy = random(10) - 5;
	}
}

static void clear_board(char *board)
{
	memset(board, 0, xdim * ydim);
}

static void move_and_draw_particles(char *board)
{
	int i, ix, iy;

	clear_board(board);
	for (i = 0; i < MAXPARTICLES; i++) {
		if (!p[i].alive)
			continue;

		ix = p[i].x;
		iy = p[i].y;

		/* move particle... */
		p[i].x += p[i].vx;
		p[i].y += p[i].vy;

		/* off the board?  Then it's dead to us. */
		if (p[i].x < 0 || p[i].x >= xdim * 4 ||
			p[i].y < 0 || p[i].y >= ydim * 4)
			p[i].alive = 0;
		else
			//bline(board, ix >> 2, iy >> 2, p[i].x >> 2, p[i].y >> 2); 
			plot(board, p[i].x >> 2, p[i].y >> 2);
		if (p[i].alive > 0)
			p[i].alive--;
	}
}

void explosions(char *board, int x, int y, int seed)
{
	int i;

	xdim = x;
	ydim = y;
	randomSeed(seed);
	memset(p, 0, sizeof(p));

	for (i = 0; i < EXPLOSION_ITERATIONS; i++) {
		add_explosion();
		move_and_draw_particles(board);
		displayBoard(board);
	}
}

