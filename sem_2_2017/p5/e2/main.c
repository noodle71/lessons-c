/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a program to calculate the sine, cosine or tangent of an angle, 
 * depending on the option chosen by the user.
 * To calculate the cosine, use the following expression (being x the angle in radians):
 *
 * 1 - x²/2! + x⁴/4! - x⁶/6! 
 *
 * To calculate the sine, use the following expression (being x the angle in radians):
 *
 * x - x³/3! + x⁵/5! - x⁷/7!
 *
 * The program will first read the angle (in degrees) and 
 * the precision of the calculations (number of terms n of the series to be added). 
 * Then, the angle is transformed into radians. And the following menu is displayed:
 * M E N U
 * 1-Calculate the sine
 * 2-Calculate the cosine
 * 3-Calculate the tangent
 * 4-Exit
 *
 * Write a function for each calculation: Sine(), Cosine(), Tangent(). 
 * Every result is displayed on the main program (functions will not use printf ). 
 * Functions Sine() and Cosine() are iterative.
 * The sine and the cosine functions will make use of the previous factorial function. 
 * Thus, in this programs the
 * functions used are: Sine(), Cosine(), Tangent() and Factorial()
 * The program will be repeated until option 4 is selected.
 */

#include <stdio.h>
#include <math.h>

//Function prototypes
int CalculateFactorialRecursive (int number);
double CalculateSine(double x, int iterations);
double CalculateCosine(double x, int iterations);
double CalculateTangent(double x, int iterations);

int main(void){

  double x; //Angle in radians
  double res; //Result after invoking the functions
  int opt; //Menu option
  int iter; //Number of iterations to calculate sin, cosine or tangent
  do{
    printf("\nM E N U");
    printf("\n1 - Calculate the sine");
    printf("\n2 - Calculate the cosine");
    printf("\n3 - Calculate the tangent");
    printf("\n4 - Exit\n\nOption: ");
    scanf("%d", &opt);
    
    if(opt == 1 || opt ==2 || opt ==3){
      printf("\nEnter the angle in radians: ");
      scanf("%lf", &x);
      do{
	printf("\nEnter a valid number of iterations: ");
        scanf("%d", &iter);
      }while(iter <= 0);
    }

    switch(opt){
      case 1:
	res = CalculateSine(x, iter);
  	printf("\nSin(%lf) = %lf\n", x, res);
	break;
      case 2:
	res = CalculateCosine(x, iter);
  	printf("\nCosin(%lf) = %lf\n", x, res);
	break;
      case 3:
	res = CalculateTangent(x, iter);
  	printf("\nTangent(%lf) = %lf\n", x, res);
	break;
      case 4:
	printf("\nGood bye!\n");
	break;
      default:
	printf("\nInvalid menu option");
    }
  }while(opt != 4);
  return 0;
}

/**
 * Recursive function to calculate factorial
 * Input: number is the integer we want to calculate the factorial
 * Output: Factorial of the number
 */
int CalculateFactorialRecursive (int number){
  int result = 1;
  if(number > 1){
    result = number * CalculateFactorialRecursive(number - 1);
  }
  return result;
}

/*
 * Iterative function to calculate sine
 * Input: The angle in radians and the number of iterations
 * Output: The sine of x
 */
double CalculateSine(double x, int iterations){
  double res = 0;
  int i;
  double numerator;
  double denominator;
  int sign;
  int factor;
  for(i = 0; i < iterations; i++){
    factor = 2*i + 1;
    sign = pow(-1, i);
    numerator = pow(x, factor);
    denominator = CalculateFactorialRecursive(factor);
    res += (sign * (numerator/denominator));
  }
  return res;
}

/*
 * Iterative function to calculate cosine
 * Input: The angle in radians and the number of iterations
 * Output: The cosine of x
 */
double CalculateCosine(double x, int iterations){
  double res = 0;
  int i;
  double numerator;
  double denominator;
  int sign;
  int factor;
  for(i = 0; i < iterations; i++){
    factor = 2*i;
    sign = pow(-1, i);
    numerator = pow(x, factor);
    denominator = CalculateFactorialRecursive(factor);
    res += (sign * (numerator/denominator));
  }
  return res;
}

/*
 * Iterative function to calculate tangent
 * Input: The angle in radians and the number of iterations
 * Output: The tangent of x
 */
double CalculateTangent(double x, int iterations){
  return CalculateSine(x, iterations) / CalculateCosine(x, iterations);
}
