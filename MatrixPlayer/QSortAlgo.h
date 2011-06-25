/*
 *  QSortAlgo.h
 *  
 *
 *  Created by rtavk3 on 6/14/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#define MAX_GEN 1500




void genList(char *list, int x, int seed);
void executeQSort(int x, int y, int seed);
void qsort(char* list, int x, int left, int right);
int partition(char*list, int x, int left, int right, int pivotIndex);
     
     
     
     
