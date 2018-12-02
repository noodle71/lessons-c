/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * [Review of Matrices and Vectors. No pointers]
 * In this exercises it is required to read two vectors of the same 
 * length (length requested to the user, but smaller than 100). 
 * The main program must call a function to compute the product of both vectors.
 * Assuming that the first array is a column vector, and the second 
 * array is a row vector, the result of the multiplication is a square 
 * matrix of size length x length. The result will be stored 
 * in a matrix called p of size 100x100.
 * p[i][j] = v1[i] · v2[j]
 * The prototypes of the functions to be developed are:
 * void ReadVector(float v[], int n);
 * void Multiply(float v1[], float v2[], float prod[][TAM], int n);
 * void Display(float prod[][TAM], int n);
 */

#include <stdio.h>
#define TAM 100

void ReadVector(float v[], int n);
void Multiply(float v1[], float v2[], float prod[][TAM], int n);
void Display(float prod[][TAM], int n);

int main(void){
  int len;
  float v1[TAM];
  float v2[TAM];
  float m[TAM][TAM];

  do{
    printf("\nIntroduce vector length: ");
    scanf("%d", &len);
    if(len <= 0 || len > TAM){
      printf("\nERROR: Invalid size, must be greater than 0 and less than %d", TAM);
    }
  }while(len <= 0 || len > TAM);
  printf("\nFill values for vector 1");
  ReadVector(v1, len);
  printf("\nFill values for vector 2");
  ReadVector(v2, len);
  Multiply(v1, v2, m, len);
  printf("\nResult of the product of vector 1 and vector 2:\n\n");
  Display(m, len);
  return 0;
}

/*
 * Fill vector values.
 * INPUT: Vector is passed by reference and the size of the vector is passed by value.
 * OUTPUT: None.
 */
void ReadVector(float v[], int n){
  int i;
  for(i = 0; i < n && i < TAM; i++){
    printf("\nIntroduce element %d of the vector: ", i + 1);
    scanf("%f", &v[i]);
  }
  return;
}

/*
 * Multiply to vectors and store the value within a matrix.
 * INPUT: The two vectors and the matrix where the product is stored, are passed by
 * reference. The size of the vectors is passed by value.
 * OUTPUT: None
 */
void Multiply(float v1[], float v2[], float prod[][TAM], int n){
  int i;
  int j;
  for(i = 0; i < n && i < TAM; i++){
    for(j = 0; j < n && j < TAM; j++){
      prod[i][j] = v1[i] * v2[j];
    }
  }
  return;
}

/*
 * Display a matrix.
 * INPUT: Matrix is passed by reference and the size of the matrix is passed by value.
 * OUTPUT: None.
 */
void Display(float prod[][TAM], int n){
  int i;
  int j;
  for(i = 0; i < n && i < TAM; i++){
    for(j = 0; j < n && j < TAM; j++){
      printf("%.2f\t", prod[i][j]);
    }
    printf("\n");
  }
  return;
}
