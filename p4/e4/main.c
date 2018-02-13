/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a program that reads from the keyboard the height of a 
 * triangle (validate it is positive) and then calls a function DrawTriang() 
 * that draws it on the screen. 
 * This function will call another one DrawLine() to draw each line 
 * of asterisks. The triangle with a height of 5 would be the following:
 * *****
 * ****
 * ***
 * **
 * *
 *
 */

#include <stdio.h>

//Function prototypes
void DrawTriang(int num_lines);
void DrawLine(int num_asterisks);

int main(void){
  int h;
  do{
    printf("Enter the height of the triangle: ");
    scanf("%d", &h);
  }while(h < 0);
  DrawTriang(h);
  return 0;
}

/*
 * DrawTriang
 * Input: Number of lines for the triangle
 * Output: None
 */
void DrawTriang(int num_lines){
  int i = num_lines;
  while(i > 0){
    DrawLine(i);
    i--;
    printf("\n");
  }
  
  /*Another way
  int i;
  for(i = num_lines; i > 0; i--){
    DrawLine(i);
    printf("\n");
  }*/
}

/**
 * DrawLine
 * Input: Number of asterisks to draw
 * Output: None
 */
void DrawLine(int num_asterisks){
  int i;
  for(i = 0; i < num_asterisks; i++){
    printf("*");
  }
}
