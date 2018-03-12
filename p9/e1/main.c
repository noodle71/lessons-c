/*
 * In his exercise we will first be reading the common dimension of two numeric 
 * arrays entered by the user. Then, memory is requested for the two arrays 
 * in agreement with the selected dimension. Next, the elements of the two 
 * arrays are initialized with values entered through the keyboard. Finally, the scalar 
 * product of the arrays is calculated and displayed. 
 *
 * Following a modular approach separate functions will be written for data entry, 
 * calculation of the scalar product of the arrays and display of the arrays.
 *
 * The above described process will be repeated a number of times at the 
 * discretion of the user. Do not forget to free the allocated dynamic 
 * memory when no longer needed. The scalar product of two n-dimension 
 * arrays vec1 and vec2 is the sumatory of the product of vec1[i] and vec[2] 
 *
 * The prototype of the functions to be used are:
 * Function to read any array:
 * void ReadArray (float *vector, int n);
 *
 * Function to calculate the scalar product of arrays v1 and v2, returning 
 * the value to the main program:
 * float ScalarProduct (float *v1, float *v2, int n);
 *
 * Function to print any of the n-dimension arrays:
 * void PrintArray (float *v, int n);
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void ReadArray (float *vector, int n);
float ScalarProduct (float *v1, float *v2, int n);
void PrintArray (float *v, int n);

int main(void){
  char c;
  float *vector1;
  float *vector2;
  int num_elements;
  float result;
  do{

    do{
      printf("\nIntroduce the array length: ");
      scanf("%d", &num_elements);
      if(num_elements <= 0){
        printf("\nERROR: The number must be greater than 0.");
      }
    }while(num_elements <= 0);

    //Get memory for the two arrays
    vector1 = (float *) calloc(num_elements, sizeof(float));
    vector2 = (float *) calloc(num_elements, sizeof(float));

    //Check if we have enought memory to create those arrays
    if(vector1 == NULL && vector2 == NULL){
      printf("\nERROR: Don't have enought memory to create the arrays");
    }else{
      printf("\nIntroduce the values for vector 1");
      ReadArray(vector1, num_elements);
      printf("\nIntroduce the values for vector 2");
      ReadArray(vector2, num_elements);

      printf("\nCalculating the scalar product of the arrays:");
      PrintArray(vector1, num_elements);
      PrintArray(vector2, num_elements);

      result = ScalarProduct(vector1, vector2, num_elements);
      printf("\nThe result is: %f", result);

      printf("\nDo you wat to continue? Press y to continue, press another key to exit: ");
      scanf(" %c", &c);
      c = tolower(c);
      //We have to release all the memory if we want to continue creating arrays
      free(vector1);
      free(vector2);
    }
  }while(c == 'y');
  return 0;
}

void ReadArray (float *vector, int n){
  int i;
  for(i = 0; i < n; i++){
    printf("\nIntroduce the element %d of the vector: ", i + 1);
    //scanf("%f", &vector[i]);
    scanf("%f", vector + i); //This is the same as above
  }
  return;
}

float ScalarProduct (float *v1, float *v2, int n){
  float res = 0;
  int i;
  for(i = 0; i < n; i++){
    //res += v1[i] * v2[i];
    res += *(v1+i) * *(v2+i); //This is the same as above
  }
  return res;
}

void PrintArray (float *v, int n){
  int i;
  printf("\n");
  for(i = 0; i < n; i++){
    //printf("%f\t", v[i]);
    printf("%f\t", *(v+i)); //This is the same as above
  }
  return;
}
