/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * The formula to calculate the area of a trapezium is:
 * Trapezium area =((B + b) * a) / 2
 *
 * Write a program to calculate the area of a trapezium, following the steps:
 * Declare variables B, b and a as input, and for the area.
 * Read from the keyboard the three variables
 * Calculate the area
 * Display the result on the screen
 * Write the program in the computer, then compile and execute.
 *
 * Run the program step-by-step using the debugger and check
 * that all three variables change values according to the code.
 */
#include <stdio.h>

int main(void){
	float B; //B length (large base)
	float b; //b length (small base)
	float a; //Trapezium height
	float area; //Trapezium area

	//Tell user to enter input for large base
	printf("Introduce large base => ");
	//Store user input into B
	scanf("%f", &B);
	//Tell user to enter input for small base
	printf("Introduce small base => ");
	//Store user input into b
	scanf("%f", &b);
	//Tell user to enter input for trapezium height
	printf("Introduce height => ");
	//Store user input into a
	scanf("%f", &a);

	//Calculate trapezium area
	area = ((B + b) * a) / 2;

	//Print results
	printf("Large base => %f \n", B);
	printf("Small base => %f \n", b);
	printf("Trapezium height => %f \n", a);
	printf("Trapezium area => %f \n", area);

	return 0;
}
