/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a program to calculate the area of 4 different figures: 
 * rectangle, square, circle and triangle.
 * 
 * The program should implement a do-while loop including: 
 * 
 * Display a menu, read the user option, and a switch structure to make the 
 * calculation and display the results.
 * 
 * The options of the main menu are: 
 * ‘r’ or ‘R’ for a rectangle, 
 * ‘s’ or ‘S’ for a square, 
 * ‘c’ or ‘C’ for a circle and 
 * ‘t’ or ‘T’ for a triangle, 
 * 'e' or 'E' to exit the program. 
 *
 * Depending on the option chosen by the user, the program will read the input data:
 *
 * Rectangle: base and height
 * Square: side
 * Circle: radius
 * Triangle: base and height
 *
 * For the options ‘r’, ‘R’, ‘s’, ‘S’, ‘c’, ‘C’, ‘t’ or ‘T’ the program will 
 * compute the area and display the result on the screen. 
 * 
 * For option ‘e’ or ‘E’ it will not make any computation. 
 * In the case of a wrong option, the program will display an error message.
 */

#include <stdio.h>

#define PI 3.1415926

int main(void){
	//Define variables
	int menu_option;
	float rectangle_size_a;
	float rectangle_size_b;
	float rectangle_area;
	float square_size;
	float square_area;
	float circle_radious;
	float circle_area;
	float triangle_base;
	float triangle_height;
	float triangle_area;

	do{
		printf("\nCalculate area of:");
		printf("\n1 -> Rectangle");
		printf("\n2 -> Square");
		printf("\n3 -> Circle");
		printf("\n4 -> Triangle");
		printf("\n5 -> Exit\n\n");
		printf("Enter option:");
		scanf("%d", &menu_option);

		switch(menu_option){
			case 1:{
				do{
					printf("\nIntroduce one side of the rectangle: ");
					scanf("%f", &rectangle_size_a);
				}while(rectangle_size_a <= 0);
				do{
					printf("Introduce the other side of the rectangle: ");
					scanf("%f", &rectangle_size_b);
				}while(rectangle_size_b <= 0);

				rectangle_area = rectangle_size_a * rectangle_size_b;
				printf("Rectangle area => %.2f\n\n", rectangle_area);
				break;
			}
			case 2:{
				do{
					printf("Introduce the side of the square: ");
					scanf("%f", &square_size);
				}while(square_size <= 0);

				square_area = square_size * square_size;
				printf("Square area => %.2f\n\n", square_area);
				break;
			}
			case 3:{
				do{
					printf("Introduce the radious of the circle: ");
					scanf("%f", &circle_radious);
				}while(circle_radious <= 0);

				circle_area = PI * circle_radious * circle_radious;
				printf("Circle area => %.2f\n\n", circle_area);
				break;
			}
			case 4:{
				do{
					printf("\nIntroduce base of the triangle: ");
					scanf("%f", &triangle_base);
				}while(triangle_base <= 0);
				do{
					printf("Introduce height of the triangle: ");
					scanf("%f", &triangle_height);
				}while(triangle_height <= 0);

				triangle_area = (triangle_base * triangle_height) / 2;
				printf("Triangle area => %.2f\n\n", triangle_area);
				break;
			}
			case 5:{
				break;
			}
			default:{
				printf("Invalid option\n");
			}
		}

	}while(menu_option != 5);
	printf("\nGoodbye!\n");
	return 0;
}
