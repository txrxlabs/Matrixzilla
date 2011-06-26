/*
 *  MatrixDef.h
 *  final cgol
 *
 *  Created by rtavk3 on 6/25/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
 

/*
 * Each module should declare a function matching this prototype
 * and add this function into the static array funcArr1 in MatrixPlayer.pde
 */
typedef void (*pt2Function)(int x, int y, int seed);

/* 
 * displayList displays a list of numbers as a bar graph on the matrix
 */ 
void displayList(char *list, int length);

/* 
 * board is x by y char's (x and y passed into pt2Function)   
 * to display at coords X, Y, set:  board[X + Y * x] = 1;
 * 0 = off, anything else = on.
 */
void displayBoard(char *board);

/* draw a line on the board from (x1,y1) to (x2,y2) */
void bline(char *board, int x1, int y1, int x2, int y2);

/* plot a point on the board at (x,y) */
void plot(char *board, int x, int y);



