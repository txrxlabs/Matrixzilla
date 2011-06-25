/*
 *  QSortAlgo.cpp
 *  
 *
 *  Created by rtavk3 on 6/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "QSortAlgo.h"
#include "WProgram.h"





void genList(char *list, int x, int y, int seed) {

  
}

void executeQSort(int x, int y, int seed, pt2Func pf) {
	char *board = (char*)malloc(sizeof(char)*x*y);
	char *list = (char*)malloc(sizeof(char)*x);
	genList((char*)list, x,y, seed);
        qsort(board,list, x, y, 0, x-1, pf);	
        free(board);
        free(list);	
}





void qsort(char* board, char* list, int x, int y, int left, int right,pt2Func pf){
 if (right > left) {
       int pivotIndex =list[right]; // select a pivotIndex in the range left ≤ pivotIndex ≤ right  
             // see Choice of pivot for possible choices
        int pivotNewIndex = partition(board,list,x,y, left, right, pivotIndex, pf);
             // element at pivotNewIndex is now at its final position
         qsort(board, list,x,y, left, pivotNewIndex - 1,pf);
             // recursively sort elements on the left of pivotNewIndex
         qsort(board, list,x,y, pivotNewIndex + 1, right,pf);
             // recursively sort elements on the right of pivotNewIndex
     }
     }
     
     // left is the index of the leftmost element of the array
  // right is the index of the rightmost element of the array (inclusive)
  //   number of elements in subarray: right-left+1
  int partition(char* board, char*list, int x, int y, int left, int right, int pivotIndex, pt2Func pf) {
     int pivotValue = list[pivotIndex];
     char tempa = list[pivotIndex];
     list[pivotIndex] = list[right];
     list[right]=tempa;  // Move pivot to end
     dispBoard(board, list, x, y, pf);
     int storeIndex = left;
     for(int i=left;i<right;i++) {// left ≤ i < right
         if(list[i] < pivotValue) {
             char tempb=list[i];
            list[i]=list[storeIndex];
            list[storeIndex]=tempb;
             storeIndex++;
                  dispBoard(board, list, x, y, pf);
         }
     }
     char tempc = list[storeIndex];
    list[storeIndex]=list[right];  // Move pivot to its final place
    list[right]=tempc;
         dispBoard(board, list, x, y, pf);
     return storeIndex;
  }
  
 
  
     
     
