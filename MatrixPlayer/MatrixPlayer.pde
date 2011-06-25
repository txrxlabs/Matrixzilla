//We always have to include the library
#include "LedControl.h"
#include "CGOLAlgo.h"
#include "QSortAlgo.h"
#include <stdio.h>
#include <stdlib.h>

#define X_SIZE 25
#define Y_SIZE 15

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 02 is connected to the DataIn 
 pin 00 is connected to the CLK 
 pin 00 is connected to LOAD 
 We have only a single MAX72XX.
 */
/*
 this program takes a five by five input array and calculates the result to an output 
 array of the same size according to the rules of Conway's Game of Life.
 
 Rules for Conway's Game of life
 0. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
 2. Any live cell with two or three live neighbours lives on to the next generation.
 3. Any live cell with more than three live neighbours dies, as if by overcrowding.
 4. Any dead cell with exactly three live neighbours becomes a livecell, as if by reproduction.
 
 
 The process is then iterated the Game of Life reaches an equilibrium state.
 */


/* the anyalive function takes an input array, the width of the array and the length of the array
 and iterates through each element of the array and returns the total number of live cells
 this is used to end the program once the game of life reaches an equilibrium state
 */
#define maxCount 6
typedef void (*pt2Function)(int x, int y, int seed);


   pt2Function funcArr1[2] = {executeCGOL, executeQSort};

LedControl lc=LedControl(12,11,10,maxCount);



void setup() {
 
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


void displayList(char *list) {
  for(int i=0;i<x;i++) {
    for(int j=0;j<y;j++) {
    *(board+(x*j)+i) = (j<list[i])?1:0;
    
    }
  }
  
}



/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void displayBoard(char *board) {
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
