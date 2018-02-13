/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 *
 * Write a recursive function to calculate the factorial of an integer number, 
 * and the main program to test it.
 *
 * Optional: write an iterative function to calculate the factorial.
 */

#include <stdio.h>

//Function prototypes
int CalculateFactorialRecursive (int number);
int CalculateFactorialIterative (int number);

int main(void){

  int num; //Number to calculate the factorial
  int res; //Result after invoking the factorial function
  do{
    printf("\nEnter an integer (greater than 0) to calculate factorial: ");
    scanf("%d", &num);
  }while(num < 1);
  res = CalculateFactorialRecursive(num);
  printf("\n\nResursive: %d! = %d\n", num, res);
  res = CalculateFactorialIterative(num);
  printf("Iterative: %d! = %d\n", num, res);
  return 0;
}

/**
 * Recursive function to calculate factorial
 * Input: number is the integer we want to calculate the factorial
 * Output: Factorial of the number
 */
int CalculateFactorialRecursive (int number){
  int result = 1;
  if(number > 1){
    result = number * CalculateFactorialRecursive(number - 1);
  }
  return result;
}

/**
 * Iterative function to calculate factorial
 * Input: number is the integer we want to calculate the factorial
 * Output: Factorial of the number
 */
int CalculateFactorialIterative (int number){
  int i;
  int res = 1;
  for(i = 1; i <= number; i++){
    res *= i;
  }
  return res;
}
