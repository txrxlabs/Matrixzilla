#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char myboard[25*15];
char *board = (char *) myboard;

void randomSeed(int x)
{
	return;
}

char getrandom(char x);

/* arduino style random conflicts with libc style random... */
#define random(x) getrandom((x))

#include "bline.c"
#include "explosion.c"

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

	for (y = 0; y < 15; y++) {
		for (x = 0; x < 25; x++) {
			printf("%c", board[y * 25 + x] ? '*' : '.');
		}
		printf("\n");
	}
	usleep(100000);	
}

int main(int argc, char *argv[])
{
	srand(250);
	explosions(board, 25, 15, 250);
}
