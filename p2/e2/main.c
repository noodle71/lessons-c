/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 14/01/2018
 *
 * DESCRIPTION:
 * The Body Mass Index (BMI) of that person is measure that correlates mass 
 * and height of a person. It was defined by the Belgian statistician 
 * L. A. J. Quetelet and such measure is also known as the Quételet index.
 *
 * The mathematical expression to compute BMI in the International 
 * System of Units of measurement is:
 * BMI = weight (kg) / (height)^2 (m)
 * According to the World Health Organization different categories are defined :
 * [http://en.wikipedia.org/wiki/Body_mass_index]
 *
 * Category 		BMI range - km/m^2
 * Underweight		x < 18.5
 * Normal		18.5 >= x < 25
 * Overweight		25 >= x < 30
 * Obese		x >= 30
 *
 * Write a program that:
 * Requests the weight in kg and the height in m.
 * Compute the BMI by using the former equation.
 * Display the category as defined by the BMI.
 *
 */
#include <stdio.h>
#include <math.h>

int main(void){
	float weight; //User weight
	float height;; //User height
	float bmi; //User BMI

	//This will keep asking the user for a valid weight (greater than 0)
	do{
		//Clear console to help user focus on the input
		system("clear");
		//Tell user to enter input for weight
		printf("Introduce your weight in kg (Must be a number greater than 0) => ");
		//Store user input into weight
		scanf("%f", &weight);
	}while(weight <= 0);

	//This will keep asking the user for a valid height (greater than 0)
	do{
		//Clear console to help user focus on the input
		system("clear");
		//Tell user to enter input for height
		printf("Introduce your height in m (Must be a number greater than 0) => ");
		//Store user input into height
		scanf("%f", &height);
	}while(height <= 0);

	//Calculate BMI
	bmi = weight / pow(height, 2);
	
	//Clear console to help user focus on the input
	system("clear");
	printf("Weight:\t\t%f\nHeight:\t\t%f\nBMI:\t\t%f\n",weight,height,bmi);
	if(bmi < 18.5){
		printf("Category:\tUnderweight\n");
	}else if(bmi >= 18.5 && bmi < 25){
		printf("Category:\tNormal\n");
	}else if(bmi >= 25 && bmi < 30){
		printf("Category:\tOverweight\n");
	}else if(bmi >= 30){
		printf("Category:\tObese\n");
	}

	return 0;
}
