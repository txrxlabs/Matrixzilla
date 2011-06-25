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




