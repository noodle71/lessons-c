/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * Write a program to read two floating-point numbers and display the following
 * menu on the screen:
 * 1. Square of the largest number
 * 2. Average
 * 3. Difference
 * Display an error message if the option selected by the user is not valid.
 */
#include <stdio.h>
#include <math.h>

int main(void){
	float num1; //Input number 1
	float num2; //Input number 2
	float max; //Max
	float square; //Square
	float avg; //Average
	float diff; //Difference
	int option; //Menu option

	//Tell user to enter input number 1
	printf("Introduce number 1 => ");
	//Store user input into num1
	scanf("%f", &num1);
	//Tell user to enter input number 2
	printf("Introduce number 2 => ");
	//Store user input into num2
	scanf("%f", &num2);

	do{
		//Display menu to the user
		printf("\n\nPlease, select one option:\n");
		printf("1 => Square of the largest number\n");
		printf("2 => Average\n");
		printf("3 => Difference\n");
		printf("4 => Exit\n\n");
		scanf("%d", &option);

		switch(option){
			case 1:
                       if(num1 > num2){
                           max = num1;
                       }else{
                           max = num2;
                       }
                       square = pow(max, 2);
                       printf("Square of the largest one (%.2f) is: %.2f\n", max, square);
                       break;

			case 2:
				       avg = (num1+num2)/2;
				       printf("The average of %.2f and %.2f is %.2f\n", num1, num2, avg);
				       break;

			case 3:
				       diff = num1-num2;
				       printf("The difference between %.2f and %.2f is %.2f\n", num1, num2, diff);
				       break;

			case 4:
				       break;

			default:
					   printf("Please, enter a valid option\n\n");

		}

	}while(option != 4);

	return 0;
}
