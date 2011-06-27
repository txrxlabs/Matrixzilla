#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// char myboard[25*15];

// #define BIGSCREEN

#ifdef BIGSCREEN
#define XDIM 79 
#define YDIM 23
#define X_SIZE 79
#define Y_SIZE 23
#else
#define XDIM 25 
#define YDIM 15
#define X_SIZE 25 
#define Y_SIZE 15 
#endif

char myboard[XDIM*YDIM];
char *board = (char *) myboard;

void randomSeed(int x)
{
	return;
}

char getrandom(char x);

/* arduino style random conflicts with libc style random... */
#define random(x) getrandom((x))

#include "bline.c"
#include "cube.cpp"

char getrandom(char x)
{
	int y;
	y = (((rand() & 0x0ff) * (int) x) / 256);
	// printf("x = %d, y = %d\n", x, y);
	return (char) y;
}

void displayBoard(char *board)
{
	int x, y;

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	for (y = 0; y < YDIM; y++) {
		for (x = 0; x < XDIM; x++) {
			printf("%c", board[y * XDIM + x] ? '#' : ' ');
		}
		printf("\n");
	}
	usleep(100000);	
}

int main(int argc, char *argv[])
{
	srand(250);
	docube(board, XDIM, YDIM, 250);
}
