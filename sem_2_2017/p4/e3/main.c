/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a function Series() to calculate the following series:
 * 1 - x + x 2 - x 3 + x 4 + ...
 * For this purpose, the previous function MyPower() 
 * will be called inside the function Series() , to calculate each term.
 *
 * The prototype of Series() is:
 * float Series(float x, int nt);
 *
 * Write a main program to read the value of x, and the number of terms 
 * of the series (and validate that it is positive).
 * Then, the main program will call the function Series(). 
 * The result obtained will be displayed in the main program
 */

#include <stdio.h>

//Function prototypes
float Series(float x, int nt);
float MyPower(float base, int e);

int main(void){
  int nt;
  float x;
  float result;
  printf("Let's calculate: 1 - x + x^2 - x^3 + x^4 + ... \n");
  do{
    printf("Enter the number of terms to sum: ");
    scanf("%d", &nt);
  }while(nt <= 0);

  printf("Enter the variable X: ");
  scanf("%f", &x);
  result = Series(x, nt);
  printf("The result is: %.3f\n", result);
  return 0;
}

/*
 * Series
 * Input: Variable x and the number of iterations
 * Output: Result of: 1 - x + x^2 - x^3 + x^4 + ...
 */
float Series(float x, int nt){
  int i;
  float result = 0;
  for(i = 0; i < nt; i++){
    result += (MyPower(-1, i) * MyPower(x, i));
  }
  return result;
}

/*
 * MyPower
 * Input: Base and exponent
 * Output: Power of a number
 */
float MyPower(float base, int e){
  int i;
  float result = 1;
  for(i = 1; i <= e; i++){
    result *= base;
  }
  return result;
}
