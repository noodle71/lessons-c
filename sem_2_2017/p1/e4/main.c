/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * Write a program to calculate the following piecewise defined function:
 *
 * f(x) 
 * x^2 for x <= 3
 * 2x/3 for x > 3
 *
 * The program will read from the keyboard the value for x 
 * and then calculate the correct value of the function and 
 * display it on the screen.
 *
 * Is the result of the program correct? Why?
 */
#include <stdio.h>
#include <math.h>

int main(void){
	float x; //Piecewise function argument
	float result; //Piecewise function result

	//Tell user to enter input for picewise function input
	printf("Introduce piecewise function input => ");
	//Store user input into x
	scanf("%f", &x);

	//Calculate result of piecewise function
	if(x > 3){
		result = (2*x) / 3;
	} else {
		result = pow(x,2);
	}

	//Print results
	printf("Using as input X = %f the result of the piecewise function is Y = %f \n", x, result);
	return 0;
}
