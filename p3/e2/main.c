/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * We define a number as “special” if can be expressed as the addition of a 
 * set of consecutives integer numbers starting with the number 1. For example, 
 * the following numbers are considered to be special numbers:
 * 1 = 1
 * 3 = 1 + 2
 * 6 = 1 + 2 + 3
 * 10 = 1 + 2 + 3 + 4
 * etc.
 *
 * Write a program that prompts the user to enter a number n (check it to be greater 
 * than zero). Then analyze if that number is a special number of not.
 */

#include <stdio.h>

int main(void){
	//Define variables
	int n; //Number to check if is special
	int i; //Loop counter
	int sum = 0; //Sum of numbers to check if it's special

	//Ask user for input till is ok
	do{
		printf("\nIntroduce a positive number to check if is special => ");
		scanf("%d", &n);
	}while(n <= 0);

	//Iterate and check if number is special to end the loop
	for(i = 1; (i <= n && n != sum); i++){
		sum += i;
	}

	//Print results
	if(n == sum){
		printf("\n\nNumber %d is especial\n", n);
	}else{
		printf("\n\nNumber %d is not especial\n", n);
	}
	return 0;
}
