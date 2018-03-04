/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION: 
 * Write a program to read from the keyboard a real number ( x ) and the number 
 * of terms ( n ) of a series, and compute:
 * 1/X^1 + 1/X^2 + 1/X^3 + ... + 1/X^n
 *
 * The computation must be performed twice: first using a standard 
 * function that doesn’t use pointers, and the second time using an equivalent 
 * function that uses pointers. The prototypes are: 
 * double ComputeSeries(double x, int n);
 * void ComputeSeriesPointer(double x, int n, double *presult);
 */

#include <stdio.h>
#include <math.h>

double ComputeSeries(double x, int n);
void ComputeSeriesPointer(double x, int n, double *presult);

int main(void){
  double x;
  int n;
  double result;
  double result_pointer = 0;

  printf("\nIntroduce the value of x: ");
  scanf("%lf", &x);

  do{
    printf("\nIntroduce the number of terms of the serie: ");
    scanf("%d", &n);
    if(n <= 0){
      printf("\nERROR: Number should be greater than 0");
    }
  }while(n <= 0);

  result = ComputeSeries(x, n);
  ComputeSeriesPointer(x, n, &result_pointer);
  
  printf("\nResult using normal function: %.3lf", result);
  printf("\nResult using pointer function: %.3lf\n", result_pointer);

  return 0;
}

/*
 * Compute the sum of the series: 1/x^1 + ... + 1/x^n
 * INPUT: Value x of the serie and the number of terms.
 * OUTPUT: The result of the sum.
 */
double ComputeSeries(double x, int n){
  int i;
  double r = 0;
  for(i = 1; i <= n; i++){
    r += 1/pow(x, i);
  }
  return r;
}

/*
 * Compute the sum of the series: 1/x^1 + ... + 1/x^n
 * INPUT: Value x of the serie, the number of terms and a pointer to store the value
 * of the sum.
 * OUTPUT: None.
 */
void ComputeSeriesPointer(double x, int n, double *presult){
  int i;
  for(i = 1; i <= n; i++){
    *presult += 1/pow(x, i);
  }
}

