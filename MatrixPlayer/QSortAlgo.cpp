/*
 *  QSortAlgo.cpp
 *  
 *
 *  Created by rtavk3 on 6/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "QSortAlgo.h"
#include "MatrixDef.h"
#include "WProgram.h"





void genList(char *list, int x, int y, int seed) {
randomSeed(seed);
	int j;
        for(j=0;j<x;j++) {
		*(list+j) = random(y);
	}
  
}

void executeQSort(int x, int y, int seed) {
	char *list = (char*)malloc(sizeof(char)*x);
	genList((char*)list, x,y, seed);
        qsort(list,x,  0, x-1);
        free(list);	
}





void qsort(char* list, int x, int left, int right){
 if (right > left) {
       int pivotIndex =list[right]; // select a pivotIndex in the range left ≤ pivotIndex ≤ right  
             // see Choice of pivot for possible choices
        int pivotNewIndex = partition(list,x, left, right, pivotIndex);
             // element at pivotNewIndex is now at its final position
         qsort(list,x, left, pivotNewIndex - 1);
             // recursively sort elements on the left of pivotNewIndex
         qsort(list,x, pivotNewIndex + 1, right);
             // recursively sort elements on the right of pivotNewIndex
     }
     }
     
     // left is the index of the leftmost element of the array
  // right is the index of the rightmost element of the array (inclusive)
  //   number of elements in subarray: right-left+1
  int partition(char*list, int x, int left, int right, int pivotIndex) {
     int pivotValue = list[pivotIndex];
     char tempa = list[pivotIndex];
     list[pivotIndex] = list[right];
     list[right]=tempa;  // Move pivot to end
     displayList( list, x);
     int storeIndex = left;
     for(int i=left;i<right;i++) {// left ≤ i < right
         if(list[i] < pivotValue) {
             char tempb=list[i];
            list[i]=list[storeIndex];
            list[storeIndex]=tempb;
             storeIndex++;
                  displayList( list, x);
         }
     }
     char tempc = list[storeIndex];
    list[storeIndex]=list[right];  // Move pivot to its final place
    list[right]=tempc;
                          displayList( list, x);
     return storeIndex;
  }
  
 
  
     
     
