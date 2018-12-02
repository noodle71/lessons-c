/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 21/02/18
 * DESCRIPTION: 
 * Write a C program to declare an integer variable ( i ), a pointer to integer ( pi ), a 
 * variable type double( d ), and a pointer to double ( pd ). 
 *
 * Then implement the following operations:
 *
 * - Adjust the pointer variable to make them point to the normal variables.
 * - Initialize values by means of the normal variables.
 * - Display those initial values, by means of normal variables and also by pointer variables.
 * - Change the original values by means of the pointer variables.
 * - Display the new values, by means of normal variables and also by pointer variables.
 */
#include <stdio.h>
int main(void){
  int i;
  int *pi;
  double d;
  double *pd;

  //Pointers point to the normal variables
  printf("\nPointing pointers to normal variables...");
  pi = &i;
  pd = &d;

  //Initialize normal variables
  printf("\n\nInitialize normal variables...");
  i = 0;
  d = 0;

  //Display normal variables and pointers
  printf("\n\nDisplaying variables and pointers content...");
  printf("\ni -> %d", i);
  printf("\n*pi -> %d", *pi);
  printf("\nd -> %lf", d);
  printf("\n*pd -> %lf", *pd);

  //Change values using pointers
  printf("\n\nChanging normal variables values using pointers...");
  *pi = 1;
  *pd = 1;

  //Display normal variables and pointers
  printf("\n\nDisplaying variables and pointers content...");
  printf("\ni -> %d", i);
  printf("\n*pi -> %d", *pi);
  printf("\nd -> %lf", d);
  printf("\n*pd -> %lf\n", *pd);
  return 0;
}
