/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 *
 * Write a function MyPower() to calculate the result of a 
 * base (floating point number) to the power of an exponent 
 * (integer positive number). The use of pow() function available 
 * in math.h is not permitted
 *
 * Write a main program to read the base from the keyboard, 
 * the exponent (and validate that the exponent is positive). 
 * Then the main program will call the MyPower() function. The prototype is:
 *
 * float MyPower(float base, int e);
 *
 * Finally, the main program will display the result.
 *
 */

#include <stdio.h>

//Function prototypes
float MyPower(float base, int e);

int main(void){
  int exp;
  float base;
  float result;
  printf("Let's calculate the power of a number.");
  printf("\nPlease enter the base: ");
  scanf("%f", &base);
  do{
    printf("Please enter a positive exponent: ");
    scanf("%d", &exp);
  }while(exp < 0);
  result = MyPower(base, exp);
  printf("%.3f^%d = %.3f\n", base, exp, result);
  return 0;
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
