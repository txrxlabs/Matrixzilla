//We always have to include the library
#include "LedControl.h"
#include "MatrixDef.h"
#include "CGOLAlgo.h"
#include "QSortAlgo.h"
#include <stdio.h>
#include <stdlib.h>

#define X_SIZE 25
#define Y_SIZE 15

#define maxCount 6
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 02 is connected to the DataIn 
 pin 00 is connected to the CLK 
 pin 00 is connected to LOAD 
 We have only a single MAX72XX.
 */



   pt2Function funcArr1[2] = {executeQSort,executeCGOL};

LedControl lc=LedControl(12,11,10,maxCount);



void setup() {
 Serial.begin(9600);
  for(int i=0;i<maxCount;i++) {
    
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(i,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(i,8);
  /* and clear the display */
  lc.clearDisplay(i);
  }
}


char getByte(char *board, int x, int y) {
  char val =0;
for(int i=0;i<8;i++) {
  val |= (*(board+(X_SIZE*y)+x+i))<<i;
}
return val;
}


char getSideByte(char *board, int col, int row, int len, int wid) {
  char val =0;
for(int i=0;i<len;i++) {
  val |= (*(board+(wid*row)-(i*wid)+col))<<i;
}
return val;
}


void displayList(char *list, int length) {
  char *board = (char*)malloc(sizeof(char)*X_SIZE*Y_SIZE);
  for(int i=0;i<X_SIZE;i++) {
    for(int j=0;j<Y_SIZE;j++) {
    *(board+(X_SIZE*j)+i) = (i<length&&j<list[i])?1:0;
    
    }
  }
  displayBoard(board);
  free(board);
  
}



/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void displayBoard(char *board) {
  
  int iy,ix;
  
/*  for(iy=0; iy<Y_SIZE;iy++) {
    for(ix=0;ix<X_SIZE;ix++) {
   Serial.print(*(board+(iy*X_SIZE)+ix),DEC);
    }
    Serial.println("");
  }*/
    for(int i=0;i<maxCount;i++) {
     lc.clearDisplay(i);
   }
 
 
    for(int i=0;i<8;i++) {
     lc.setRow(0,i,getByte(board,0,i));  

  }
for(int k=0;k<7;k++) {
     lc.setRow(1,k,getByte(board,0,k+8));
}
     lc.setRow(1,7,getByte(board,8,14));
    
     for(int o=0;o<8;o++) {
          lc.setRow(2,o,getByte(board,8,13-o));
        }
         for(int g=0;g<6;g++) {
          lc.setRow(3,g,getByte(board,8,5-g));
        }
         lc.setRow(3,6,getByte(board,16,0));
          lc.setRow(3,7,getByte(board,16,1));
         
         for(int h=0;h<7;h++) {
          lc.setRow(4,h,getByte(board,16,2+h));
        } 
         for(int v=0;v<5;v++) {
          lc.setRow(5,v,getByte(board,16,10+v));
        }
          lc.setRow(5,5,getSideByte(board,24,14,8, 25));
          lc.setRow(5,6,getSideByte(board,24,6,7, 25));
        
 
   
 
}

void loop() { 
      funcArr1[0](X_SIZE, Y_SIZE, analogRead(0));
      funcArr1[1](X_SIZE, Y_SIZE, analogRead(0));
 
}
