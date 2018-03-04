/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * Write a program that uses a function to compute and return the maximum 
 * and the minimum values of a matrix. 
 * The maximum size of matrix is 20x20. Within the main program, the number of rows 
 * and columns must be requested to the user (validate the input). 
 * Then, all the elements of the matrix must be read from the keyboard. 
 * The functions Search for finding the maximum and minimum values will receive 
 * the matrix and the sizes, and it will return the maximum and minimum values 
 * using pointers (because there is no way to return more that one result using return).
 * The result will be displayed on the screen by calling printf within the main program.
 * The prototype is:
 *
 * void Search(float mat[][N], int nr, int nc, float *pmax, float *pmin);
 */
#include <stdio.h>
#include <float.h>
#define N 20

//Mandatory functions
void Search(float mat[][N], int nr, int nc, float *pmax, float *pmin);
//Optional functions
int AskSize(char label[]);
void FillMatrix(int num_rows, int num_columns, float mat[][N]);

int main(void){
  int row_size = AskSize("rows");
  int column_size = AskSize("columns");
  float mat[N][N];
  float max = -FLT_MAX;
  float min = FLT_MAX;
  FillMatrix(row_size, column_size, mat);
  Search(mat, row_size, column_size, &max, &min);
  printf("\n\nThe max value is %.3f and the min is %.3f\n", max, min);
  return 0;
}

/*
 * Search min and max values within a matrix.
 * INPUT: Matrix passed by reference, the number of rows and columns, and 2 pointers to
 * store the max and min.
 * OUTPUT: None.
 */
void Search(float mat[][N], int nr, int nc, float *pmax, float *pmin){
  int i;
  int j;
  float x;
  for(i = 0; i < nr; i++){
    for(j = 0; j < nc; j++){
      x = mat[i][j];
      if(x > *pmax){
        *pmax = x;
      }
      if(x < *pmin){
        *pmin = x;
      }
    }
  }
  return;
}

/*
 * Ask size for rows or columns.
 * INPUT: A label to display a different message to the user.
 * OUTPUT: None.
 */
int AskSize(char label[]){
  int n;
  do{
    printf("\nEnter the number of %s: ", label);
    scanf("%d", &n);
    if(n <= 0 || n > N){
      printf("\nERROR: Invalid size. Should be greater than 0 and less equals %d", N);
    }
  }while(n <= 0 || n > N);
  return n;
}

/*
 * Fill all matrix positions.
 * INPUT: The number or rows and columns. The matrix where the values will be stored is 
 * passed by reference.
 * OUTPUT: None.
 */
void FillMatrix(int num_rows, int num_columns, float mat[][N]){
  int i;
  int j;
  for(i = 0; i < num_rows; i++){
    for(j = 0; j < num_columns; j++){
      printf("\nEnter value for matrix at [%d,%d]: ", i, j);
      scanf("%f", &mat[i][j]);
    }
  }
  return;
}
