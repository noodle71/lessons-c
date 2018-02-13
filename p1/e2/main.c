/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * Write a program to compute the monthly net salary of an employee.
 * The gross salary is calculated given the number of work
 * hours and a euro per hour. The income tax is 15% of the gross salary.
 *
 * The program will read the following data from the keyboard:
 * Work hours
 * Euro per hour
 *
 * Calculate the gross salary, taxes and the net salary
 *
 * Is the result of the program correct? Why?
 */
#include <stdio.h>

int main(void){
	int hours; //Number or hours worked
	float euro_per_hour; //Cost of one hour of work (in €)
	float salary_gross; //Total salary
	float salary_net; //Net salary
	float salary_taxes; //Salary taxes

	//Tell user to enter input for the numer of hours worked
	printf("Introduce hours worked => ");
	//Store user input into resistor 1
	scanf("%d", &hours);
	//Tell user to enter input for the price per hour of work
	printf("Introduce price per hour of work => ");
	//Store user input into resistor 2
	scanf("%f", &euro_per_hour);

	//Calculate gross salary
	salary_gross = hours * euro_per_hour;
	//Calculate salary taxes
	salary_taxes = salary_gross * 0.15;
	//Calculate net salary
	salary_net = salary_gross - salary_taxes;

	//Print results
	printf("Total hours worked => %d \n", hours);
	printf("Price per hour => %.2f \n", euro_per_hour);
	printf("Gross salary is => %.2f \n", salary_gross);
	printf("Salary taxes => %.2f \n", salary_taxes);
	printf("Net salary is => %.2f \n", salary_net);
	return 0;
}
