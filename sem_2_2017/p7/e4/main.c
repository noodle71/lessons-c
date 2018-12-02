/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 19/02/18
 * DESCRIPTION: 
 * Write a program to create and display a magic square of size N, being N an integer, 
 * positive, and odd number. 
 * A magic square of size N is a square matrix NxN, filled with 
 * integer numbers from 1 to N² , so that the sum of any row, any column 
 * and any of the two diagonals yields the same number. A magic square can be built 
 * following the rules published by de la Loubère in 1693. 
 *
 * 1. Set a number 1 in the middle of the first row.
 * 
 * 2. Next number is positioned on the previous row, and following column. 
 * 
 * 3. If the number minus one is a multiple of N, then rule 2 is canceled and 
 * the number is positioned on the following row and same column. 
 * 
 * 4. The last row is considered the previous row of the first row. The first 
 * row is considered following to the last. 
 *
 * Write a program to request the size of the matrix, validating the input and 
 * checking that it is smaller than 25. Then call function 
 * void BuildMagicSquare(int mat[][25], int dim); 
 * to generate the magic square. 
 *
 * Finally the main program will display the result on the screen.
 */

#include <stdio.h>
#include <math.h>
#define N 25

//MANDATORY FUNCTIONS
void BuildMagicSquare(int mat[][N], int dim); 
//OPTIONAL FUNCTIONS
void DisplayMatrix(int mat[][N], int dim);
int NormalizeCoordinate(int dim, int x);

int main(void){
  int n;
  int mat[N][N];

  do{
    printf("\nEnter matrix size: ");
    scanf("%d", &n);
    if(n <= 0 || n > N || n % 2 == 0){
      printf("\nERROR: Matrix size is not valid. Must be an odd number. Range: [1, %d]", N);
    }
  }while(n <= 0 || n > N || n % 2 == 0);

  BuildMagicSquare(mat, n);
  printf("\nMagic square matrix:\n");
  DisplayMatrix(mat, n);

  return 0;
}

/*
 * Build a magic square matrix.
 * INPUT: Matrix where the magic square is going to be stored (passed by reference) 
 * and the matrix size limit (odd number).
 * OUTPUT: None.
 */
void BuildMagicSquare(int mat[][N], int dim){
  int i;
  int j;
  int num = 1;
  int x = 0;
  int y = 0;
  for(i = 0; i < dim; i++){
    for(j = 0; j < dim; j++){

      if(num == 1){
	x = dim / 2;
      }else{
	if((num - 1) % dim == 0){ //Following row, same column
          y++;
	}else{ //Previous row, following column
	  y--;
	  x++;
	}
      }

      x = NormalizeCoordinate(dim, x);
      y = NormalizeCoordinate(dim, y);

      mat[y][x] = num;
      num++;
    }
  }
  return;
}

/*
 * Normalize coordinates to follow the 4th rule.
 * INPUT: Matrix dimension and coordinate.
 * OUTPUT: Coordinate normalized.
 */
int NormalizeCoordinate(int dim, int x){
  if(x < 0){
    x = dim - 1;
  }
  if(x >= dim){
    x = 0;
  }
  return x;
}

/*
 * Display matrix content.
 * INPUT: Matrix (passed by reference) and the matrix size.
 * OUTPUT: None.
 */
void DisplayMatrix(int mat[][N], int dim){
  int i;
  int j;
  for(i = 0; i < dim; i++){
    for(j = 0; j < dim; j++){
      printf("%d\t", mat[i][j]);
    }
    printf("\n");
  }
  return;
}
