/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * Write a program to read the text file ( temperatures.txt ) previously created, 
 * and display that information on the screen. The program will declare two 
 * variables: an integer for the day and a double for the temperature. At each step 
 * the day and temperature is displayed on the screen. Additionally the program will 
 * count and display the number of temperatures stored in the file. The use of 
 * vectors is not permitted. 
 * Note: The file will be read checking the error code returned by fscanf :
 * do {
 *   ctrl=fscanf(ftp,“%d %lf\n”, &day, &temp);
 *   if (ctrl==2) {
 *     etc...
 *     etc...
 *   }
 * } while (ctrl==2);
 */ 
#include<stdio.h>

int main(void){
  int read_check;
  FILE *pf;
  int day;
  float temp;
  pf = fopen("temperatures.txt", "r");
  if(pf == NULL){
    printf("ERROR: File doesn't exist.");
  }else{
    do{
      read_check = fscanf(pf, "%d\t%f\n", &day, &temp);
      if(read_check == 2){
        printf("\n%d\t%.2f", day, temp);
      }
    }while(read_check == 2);
    if(fclose(pf) != 0){
      printf("\nERROR: Can't close file.");
    }
  }
  printf("\n");
  return 0;
}
