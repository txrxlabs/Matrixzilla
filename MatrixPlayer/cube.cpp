#include <string.h> /* for memset */
#include "MatrixDef.h"
#include <stdio.h>
#include <math.h>

#define PI 3.1415927

static int xdim;
static int ydim;

#ifndef BIGSCREEN
static float ez = 10.0;
static float cubescale = 11.5;
#else
static float ez = 18.0;
static float cubescale = 7.5;
#endif

#define ARRAYSIZE(x) (sizeof((x)) / sizeof((x)[0]))

struct point {
	float x, y, z;
} cubept2[] = {
	{ 1, 1, 1 },
	{ -1, 1, 1 },
	{ -1, -1, 1 },
	{ 1, -1, 1 },
	{ 1, 1, -1 },
	{ -1, 1, -1 },
	{ -1, -1, -1 },
	{ 1, -1, -1 },
};

struct point cubept3[ARRAYSIZE(cubept2)];
struct point cubept[ARRAYSIZE(cubept2)];

static float cubetransx = 0;
static float cubetransy = 0;
static float cubetransz = 25.0;

char cube[] = { 0, 1, 2, 3, 0, 4, 5, 6, 7, 4,
		-1, 7, 3, -1, 2, 6, -1, 5, 1, -1};


#define CUBE_ITERATIONS 1500

static void yrotate(struct point *p1, struct point *p2, int npoints, float angle)
{
	int i;
	float cosa, sina;

	cosa = cos(angle);
	sina = sin(angle);

	for (i = 0; i < npoints; i++) {
		p2[i].x = p1[i].x * cosa - p1[i].z * sina;
		p2[i].z = p1[i].x * sina + p1[i].z * cosa;
		p2[i].y = p1[i].y;
	}
}

static void zrotate(struct point *p1, struct point *p2, int npoints, float angle)
{
	int i;
	float cosa, sina;

	cosa = cos(angle);
	sina = sin(angle);

	for (i = 0; i < npoints; i++) {
		p2[i].x = p1[i].x * cosa - p1[i].y * sina;
		p2[i].y = p1[i].x * sina + p1[i].y * cosa;
		p2[i].z = p1[i].z;
	}
}

static void xrotate(struct point *p1, struct point *p2, int npoints, float angle)
{
	int i;
	float cosa, sina;

	cosa = cos(angle);
	sina = sin(angle);

	for (i = 0; i < npoints; i++) {
		p2[i].y = p1[i].y * cosa - p1[i].z * sina;
		p2[i].z = p1[i].y * sina + p1[i].z * cosa;
		p2[i].x = p1[i].x;
	}
}

static void clear_board(char *board)
{
	memset(board, 0, xdim * ydim);
}

void orthographic(float x, float y, float z, float *dx, float *dy)
{
	*dx = x + z * 0.5;
	*dy = y + z * 0.5;
}

void perspective(float x, float y, float z, float *dx, float *dy)
{
	// *dx = (xdim / 2.0) + (ez / z) * (x - (xdim/2.0));
	// *dy = (ydim / 2.0) + (ez / z) * (y - (ydim/2.0));
	*dx = (xdim / 2.0) + (ez / z) * (x);
	*dy = (ydim / 2.0) + (ez / z) * (y);
}

static void (*projection)(float x, float y, float z, float *dx, float *dy) =
	perspective;

void draw_cube(char *board) 
{
	int i, n;
	float x, y, z, lx, ly, nx, ny;
	char x1, y1, x2, y2;

	n = cube[0];
	x = cubept[n].x * cubescale + cubetransx;
	y = cubept[n].y * cubescale + cubetransy;
	z = cubept[n].z * cubescale + cubetransz;
	projection(x, y, z, &lx, &ly);

	// orthographic(x, y, z, &lx, &ly);

	for (i = 1; i < ARRAYSIZE(cube); i++) {
		n = cube[i];
		if (n == -1)
			continue;
		x = cubept[n].x * cubescale + cubetransx;
		y = cubept[n].y * cubescale + cubetransy;
		z = cubept[n].z * cubescale + cubetransz;
		projection(x, y, z, &nx, &ny);

		x1 = (char) lx;
		y1 = (char) ly;
		x2 = (char) nx;
		y2 = (char) ny;
		lx = nx;
		ly = ny;
#if 0
		if (x1 < 0 || x1 >= xdim || x2 < 0 || x2 >= xdim)
			continue;
		if (y1 < 0 || y1 >= ydim || y2 < 0 || y2 >= ydim)
			continue;
#endif
		bline(board, x1, y1, x2, y2);
	}
}

void docube(char *board, int x, int y, int seed)
{
	int i;

	xdim = x;
	ydim = y;
	randomSeed(seed);
	float zvel = 1.0;
	float xvel = 1.0;
	float angle = 0;
	float angle2 = 0;
	float angle3 = 0;

	memcpy(&cubept, &cubept2, sizeof(cubept2));

	for (i = 0; i < CUBE_ITERATIONS; i++) {
		clear_board(board);
		draw_cube(board);
		displayBoard(board);
#if 0
		cubetransz += zvel;
		if (cubetransz > 55)
			zvel = -0.9;
		if (cubetransz < 10.0)
			xvel = 0.9;
		cubetransx += xvel;
		if (cubetransx > 25)
			xvel = -0.9;
		if (cubetransx < -25)
			xvel = 0.9;
#endif
		yrotate(cubept2, cubept, ARRAYSIZE(cubept), PI * angle / 180.0);
		zrotate(cubept, cubept3, ARRAYSIZE(cubept), PI * angle2 / 180.0);
		xrotate(cubept3, cubept, ARRAYSIZE(cubept), PI * angle2 / 180.0);
		angle2 += 2.9;
		if (angle2 > 360)
			angle2 = 0;
		angle += 2.7;
		if (angle > 360)
			angle = 0;
		angle3 += 1.5;
		if (angle3 > 360)
			angle3 = 0;
	}
}

