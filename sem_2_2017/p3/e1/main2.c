/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * The value of the function 1/(1+x) can be calculated approximately by 
 * summing the first n terms of the infinite series:
 * 1 - x + x^2 - x^3 + x^4 + ...
 *
 * Write a program that will read and validate the values for n and x and then display the 
 * approximate value of the function (values of x between 0 and 1).
 *
 * There are two ways to solve this problem:
 * Obtain the general term of the series as a function of the iteration counter (i).
 * Compute the i th term by multiplying the i-1 term by -x.
 *
 * Write the program in two ways.
 *
 */

#include <stdio.h>
#include <math.h>

int main(void){
	//Define variables
	int n; //Number of terms of the infinite serie
	float x; //Variable x of the equation
	int i = 1; //Loop counter
	float previous_term = 1; //Previous series term
	float current_term; //Current series term
	float result = 1; //Series addition result

	printf("Let\'s calculate 1/(1+x)\n");

	//Ask the user for the input till it's ok
	do{
		printf("\nIntroduce a positive number as number of terms of the infinite serie => ");
		scanf("%d", &n);
	}while(n <= 0);

	//Ask the user for the input x
	do{
	  printf("\nIntroduce the value x => ");
          scanf("%f", &x);
	  if(x <= 0 || x >= 1){
	    printf("Error: x value should be greater than 0 and less than 1");
	  }
	}while(x <= 0 || x >= 1);

	while(i < n){
		//Option 2: Multiply the previous term of the series by (-x)
		current_term = previous_term*(-x);
		result = result + current_term;
		previous_term = current_term;
		i++;
	}

	printf("\n\nResult => %.3f\n", result);
	return 0;
}
