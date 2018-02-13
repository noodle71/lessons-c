/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * Write a program to display the following menu on the screen:
 * A – Area of a circle
 * B – Perimeter of a square
 * C – Perimeter of a triangle
 *
 * According to the option selected by the user, the program will request the
 * required input values, make the computation and display the result.
 *
 * Display an error message if the option selected by the user is not valid.
 *
 */
#include <stdio.h>
#include <math.h>

//Define a global variable to be used within the program
#define PI 3.1415926

int main(void){
	float circle_area; //Area of the circle
	float square_perimeter; //Perimeter of a square
	float triangle_perimeter; //Perimeter of a triangle
	float circle_radius; //Circle radius
	float square_size; //Size of one side of the square
	float triangle_side_1; //Size of 1/3 side of the triangle
	float triangle_side_2; //Size of 2/3 side of the triangle
	float triangle_side_3; //Size of 3/3 side of the triangle

	int option; //Menu option

	do{
		//Show menu to the user
		printf("\n\nPlease, select one option:\n");
		printf("1 => Area of a circle\n");
		printf("2 => Perimeter of a square\n");
		printf("3 => Perimeter of a triangle\n");
		printf("4 => Exit\n\n");

		//Store input value in variable option
		scanf("%d", &option);

		switch(option){
			case 1:
				       do{
					       printf("Please, enter a valid radius for the circle. (Must be greater than 0)\n");
					       scanf("%f", &circle_radius);
				       }while(circle_radius <= 0);
				       circle_area = PI * pow(circle_radius, 2);
				       printf("The area of the circlr is: %.2f\n", circle_area);
				       break;

			case 2:
				       do{
					       printf("Please, enter a valid size for the square side. (Must be greater than 0)\n");
					       scanf("%f", &square_size);
				       }while(square_size <= 0);
				       square_perimeter = 4 * square_size;
				       printf("The perimeter of the square is: %.2f\n", square_perimeter);
				       break;

			case 3:
				       do{
					       printf("Please, enter a valid size for the triangle side 1/3. (Must be greater than 0)\n");
					       scanf("%f", &triangle_side_1);
				       }while(triangle_side_1 <= 0);

				       do{
					       printf("Please, enter a valid size for the triangle side 2/3. (Must be greater than 0)\n");
					       scanf("%f", &triangle_side_2);
				       }while(triangle_side_2 <= 0);

				       do{
					       printf("Please, enter a valid size for the triangle side 3/3. (Must be greater than 0)\n");
					       scanf("%f", &triangle_side_3);
				       }while(triangle_side_3 <= 0);

				       triangle_perimeter = triangle_side_1 + triangle_side_2 + triangle_side_3;
				       printf("The perimeter of the triangle is: %.2f\n", triangle_perimeter);
				       break;

			case 4:
				       break;

			default:
					   printf("Please, enter a valid option\n");

		}

	}while(option != 4);
	printf("Goodbye!\n");

	return 0;
}
