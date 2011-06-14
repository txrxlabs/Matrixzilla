/*
 *  CGOLAlgo.c
 *  
 *
 *  Created by rtavk3 on 6/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "CGOLAlgo.h"
#include "WProgram.h"
char *b1;
char *b2;


int hasChanged(char *ar1, char *ar2, int x, int y) {
  int j;
	for(j=0;j<x*y;j++) {
		if(*(ar1+j)!=*(ar2+j)) return 1;
	}
	return 0;
}

int aliveCount (char *ar1, int x, int y){
	int i, sum=0;
	for (i=0; i<x*y; i++) {
		sum+=*(ar1+i);
	}
	return sum;
	
}

void fillBoard(char *ar1, int x, int y, int seed) {
	randomSeed(seed);
	int j;
        for(j=0;j<x*y;j++) {
		if(random(300)<150) {
			*(ar1+j) = 1;
		}
		else {
			*(ar1+j) = 0;   
		}
	}
}

//gameoflife is a function that an input array 
//and then calculates the output array using the rules defined in Conway's game of life
//and puts the result in an output array

char* generate(char *ar1, char *ar2, int x, int y){
	
	//allocates memory for the output array by calculating the width and length of the input array
	
	//iterate through each cell to evaluate neighbors	
	//replace indices with referenced pointers from width x and length y
	int down_index, up_index, left_index, right_index;
        int yidx;	
for (yidx=0; yidx<y; yidx++) {
		
		down_index= yidx+1;
		up_index= yidx-1;
		
		if (down_index>=y)
			down_index=0;
		if (up_index<0) {
			up_index=y-1;
		}
		int xidx;
		for (xidx=0; xidx<x; xidx++){
			//take the values of the adjacent matrices and store them initialize to zero
			left_index = xidx-1;
			right_index = xidx+1;
			
			if (left_index<0) {
				left_index=x-1;
			}
			if (right_index>=x) {
				right_index=0;
			}
			//if at the end of a column, add the top or bottom side
			
			//if at the beginning or end of a row, add the left or right side
			
			//sum values of the adjacent matrices
			//neighbors map:
			// 0,-0, 0,-0 0,-0
			// -0,0    --   0,0
			// -0,0   0,0   0,0
			
			
			int sumneighbors = *(ar1+(x*up_index)+left_index);//[up_index][left_index];
			
			sumneighbors+= *(ar1+(x*up_index)+xidx);//[up_index][xidx];
			sumneighbors+= *(ar1+(x*up_index)+right_index);//[up_index][right_index];
			sumneighbors+= *(ar1+(x*yidx)+left_index);//[yidx][left_index];
			sumneighbors+= *(ar1+(x*yidx)+right_index);//[yidx][right_index];
			sumneighbors+= *(ar1+(x*down_index)+left_index);//[down_index][left_index];
			sumneighbors+= *(ar1+(x*down_index)+xidx);//[down_index][xidx];
			sumneighbors+= *(ar1+(x*down_index)+right_index);//[down_index][right_index];
			/*printf("%i %i %i %i %i %i %i %i\n",
			 (x*up_index)+left_index, (x*up_index)+xidx, (x*up_index)+right_index,
			 (x*yidx)+left_index, (x*yidx)+right_index, (x*down_index)+left_index,
			 (x*down_index)+xidx, (x*down_index)+right_index);
			 
			 printf("%i %i %i %i %i %i %i %i\n",
			 *(ar0+(x*up_index)+left_index), *(ar0+(x*up_index)+xidx), *(ar0+(x*up_index)+right_index),
			 *(ar0+(x*yidx)+left_index), *(ar0+(x*yidx)+right_index), *(ar0+(x*down_index)+left_index),
			 *(ar1+(x*down_index)+xidx), *(ar1+(x*down_index)+right_index));*/
			
			
			
			//if 2 or 3 its living
			//write 1 to the second array
			//else death
			//write 0 to the the second array
			
			if ((*(ar1+(x*yidx)+xidx))==0) {
				*(ar2+(yidx*x)+xidx)= (sumneighbors==3?1:0);
			}
			else *((ar2+(yidx*x)+xidx)) =(sumneighbors==2||sumneighbors==3)?1:0;
			
		}
	}
	
	
	
	return ar2;
	
}

void executeCGOL(int x, int y, int seed, pt2Func pf) {
	b1 = (char*)malloc(sizeof(char)*x*y);
	b2 = (char*)malloc(sizeof(char)*x*y);
	fillBoard((char*)b1, x, y, seed);
	long itercount =0;
	while (itercount<MAX_GEN && aliveCount(b1, x,y)<3) {
		char *artemp = b1;
		b1=generate(b1,b2, x, y);
        b2 = artemp;
        // display board
		pf(b1);
		delay(1000);
		if(!hasChanged(b1, b2, x, y)) {
			delay(60000);
			break;
		}
  	}		
}






