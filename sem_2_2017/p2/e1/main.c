/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * Write a program to request the values of coefficients a,b and c
 * for the equation ax 2 + bx + c = 0. and displays the
 * roots of that equation.
 *
 * The program must consider the following possible cases:
 *
 * The user entered a = 0 , b = 0
 * Linear case: ( a = 0 ).
 * One double root ( b^2 - 4ac = 0 ).
 * Two roots ( b^2 - 4ac > 0 ).
 * Complex roots ( b^2 - 4ac < 0 ).
 *
 */
#include <stdio.h>
#include <math.h>

int main(void){
	float a; //Coefficient a
	float b; //Coefficient b
	float c; //Coefficient c
	float diff; //Discriminant
	float x1; //Result 1
	float x2; //Result 2
	float real; //Real result
	float i; //Imaginary result

	//Tell user to enter input for coefficient a
	printf("Introduce coefficient a => ");
	//Store user input into a
	scanf("%f", &a);
	//Tell user to enter input for coefficient b
	printf("Introduce coefficient b => ");
	//Store user input into b
	scanf("%f", &b);
	//Tell user to enter input for coefficient c
	printf("Introduce coefficient c => ");
	//Store user input into c
	scanf("%f", &c);

	//Check if it's a double root equation
	if(a == 0 && b == 0){
		printf("Error. (c should be 0).\n");
	}
	else if(a == 0){
		x1 = -c/b;
		printf("Linear case:\n\tx = %f\n", x1);
	}else{
		diff = pow(b,2) - 4*a*c;
		if(diff == 0){
			x1 = -b/(2*a);
			x2 = x1;
			printf("One double root:\n\tx1 = %f\n\tx2 = %f\n", x1, x2);
		}else if(diff > 0){
			x1 = (-b+sqrt(diff))/(2*a);
			x2 = (-b-sqrt(diff))/(2*a);
			printf("Two roots:\n\tx1 = %f\n\tx2 = %f\n", x1, x2);
		}else if(diff < 0){
			real = -b/(2*a);
			i = sqrt(-diff)/(2*a);
			printf("Complex roots:\n\tx1 = %f+%fi\n\tx2 = %f-%fi\n", real, i, real, i);
		}
	}
	return 0;
}
