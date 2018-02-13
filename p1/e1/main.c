/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * Write a program to calculate the equivalent resistor of two resistors connected in series and in parallel.
 * Given the resistors R1 and R2, the equivalent resistors are calculated as:
 * Series:
 * Req_Series = R1 + R2
 *
 * Parallel:
 * Req_Paral = (R1 * R2) / (R1 + R2)
 *
 * Execute the program typing in the values de r1 = 2.0 y r2 = 1.0.
 * Display 2 decimal places of the calculated resistors (using %.2f).
 */
#include <stdio.h>

int main(void){
	float r1; //Resistor 1, read from the keyboard
	float r2; //Resistor 2, read from the keyboard
	float req_series; //Equivalent series resistor
	float req_par; //Equivalent parallel resistor

	//Tell user to enter input for resistor 1
	printf("Introduce resistor 1 => ");
	//Store user input into resistor 1
	scanf("%f", &r1);
	//Tell user to enter input for resistor 2
	printf("Introduce resistor 2 => ");
	//Store user input into resistor 2
	scanf("%f", &r2);

	//Calculate equivalent resistors (series)
	req_series = r1 + r2;
	//Calculate equivalent resistors (series)
	req_par = (r1 * r2) / (r1 + r2);

	//Print results
	printf("The equivalent resistor for the series connection is %.2f \n", req_series);
	printf("The equivalent resistor for the parallel connection is %.2f \n", req_par);
	return 0;
}
