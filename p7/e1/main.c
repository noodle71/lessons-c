/*
 * AUTHOR: Angel Fernandez Camba
 * DATE: 18/02/18
 * DESCRIPTION: 
 * Write a program to declare two square integer matrices mat and trans 
 * of size NxN (10x10), and request to the user the size of a square matrix 
 * to work with (validate the input). 
 * Then initialize matrix mat by reading values from the keyboard. 
 * Within the main program write the code to compute the 
 * transpose of mat and store it into trans.
 *
 * Write a function to compute the sum of the elements in the 
 * antidiagonal (see graph). The prototype is:
 * int SumAntidiag(int m[][N], int dim);
 *
 * Note: The transpose is obtained by exchanging elements (i,j) and (j,i).
 */

#include <stdio.h>
#define N 10

//MANDATORY FUNCTIONS
int SumAntidiag(int m[][N], int dim);
//OPTIONAL FUNCTIONS
void InitMatrix(int m[][N], int dim);
void TransposeMatrix(int m[][N], int trans[][N], int dim);
int GetMatrixDimension(void);
void PrintMatrix(int m[][N], int dim, char name[20]);

int main(void){
  int mat_dim = GetMatrixDimension();
  int mat[N][N];
  int trans[N][N];
  
  InitMatrix(mat, mat_dim);
  TransposeMatrix(mat, trans, mat_dim);
  PrintMatrix(mat, mat_dim, "Matrix");
  PrintMatrix(trans, mat_dim, "Transposed");

  printf("\nThe sum of elements of the antidiagonal is: %d\n", SumAntidiag(mat, mat_dim));
  return 0;
}

/*
 * Ask for the squared matrix dimension.
 * INPUT: None.
 * OUTPUT: Matrix dimension.
 */
int GetMatrixDimension(void){
  int m;
  do{
    printf("\nEnter matrix dimension: ");
    scanf("%d", &m);
    if(m < 1 || m > N){
      printf("\nERROR: Matrix dimension should be greater than 0 and less than %d", N + 1);
    }
  }while(m < 1 || m > N);
  return m;
}

/*
 * Init matrix values.
 * INPUT: Matrix is passed by reference and matrix dimension is passes by value.
 * OUTPUT: None.
 */
void InitMatrix(int m[][N], int dim){
  int i; //Matrix row counter
  int j; //Matrix column counter
  for(i = 0; i < dim; i++){
    for(j = 0; j < dim; j++){
      printf("\nIntroduce element [%d, %d]: ", i, j);
      scanf("%d", &m[i][j]);
    }
  }
  return;
}

/*
 * Transpose a matrix and store it in another matrix
 * INPUT: Matrix and transposed matrix are passed by reference but matrix dimension is passed
 * by value.
 * OUTPUT: None.
 */
void TransposeMatrix(int m[][N], int trans[][N], int dim){
  int i; //Matrix row counter
  int j; //Matrix column counter
  for(i = 0; i < dim; i++){
    for(j = 0; j < dim; j++){
      trans[j][i] = m[i][j];
    }
  }
  return;
}

/*
 * Get antidiagonal sum of elements.
 * INPUT: Matrix is passed by reference and matrix dimension is passed by value.
 * OUTPUT: The sum of the elements must be an integer.
 */
int SumAntidiag(int m[][N], int dim){
  int sum = 0;
  int i;
  for(i = 0; i < dim; i++){
    sum += m[dim - 1 - i][i];
  }
  return sum;
}

/*
 * Print matrix content.
 * INPUT: Matrix is passed by reference, matrix dimension and name are passed by value.
 * OUTPUT: None.
 */
void PrintMatrix(int m[][N], int dim, char name[20]){
  int i; //Matrix row counter
  int j; //Matrix column counter
  printf("\nMatrix content: %s\n", name);
  for(i = 0; i < dim; i++){
    for(j = 0; j < dim; j++){
      printf("%d\t", m[i][j]);
    }
    printf("\n");
  }
  return;
}
