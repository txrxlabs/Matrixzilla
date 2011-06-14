/*
 *  CGOLAlgo.h
 *  
 *
 *  Created by rtavk3 on 6/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#define MAX_GEN 1500

typedef void (*pt2Func)(char*);
int hasChanged(char *ar1, char *ar2, int x, int y);
int aliveCount (char *ar1, int x, int y);
void fillBoard(char *ar1, int x, int y, int seed);
char* generate(char *ar1, char *ar2, int x, int y);
void executeCGOL(int x, int y, int seed, pt2Func pf);
