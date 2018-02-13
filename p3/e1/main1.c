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
	int i; //Loop counter
	float result = 0; //Result where the addition is stored 
	int sign; //Store the number sign
	float power; //X power
	float previous_result; //Previous calculation

	printf("Let\'s calculate 1/(1+x)\n");

	//Ask user for input till is ok
	do{
		printf("\nIntroduce a positive number as number of terms of the infinite serie => ");
		scanf("%d", &n);
	}while(n <= 0);

	//Ask user for input X
	do{
	  printf("\nIntroduce the value x => ");
	  scanf("%f", &x);
	  if(x <= 0 || x >= 1){
	    printf("\nError: x value should be greater than 0 and less than 1");
	  }
	}while(x <= 0 || x >= 1);

	for(i = 0; i < n; i++){
		//Option 1: Obtain general term of the series
		power = pow(x, i);
		sign = pow(-1, i);
		previous_result = result;
		result = result + (sign * power);
		printf("\nIteration %d: %.3f + (%d * %.3f) = %.3f", i+1, previous_result, sign, power, result);
	}


	printf("\n\nResult => %.3f\n", result);
	return 0;
}
