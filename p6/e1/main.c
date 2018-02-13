/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a program to calculate the average grade, the maximum and the minimum 
 * grade of the students.
 * Declare a vector of floating point numbers (maximum size 50, 
 * declare this value as a constant). The program will read from the 
 * keyboard the number of students in the class (integer variable n). Then 
 * then grades will be read and stored into the declared array 
 * (vector, float grades[50];). Remember grades should be validated..
 *
 * Then, a menu will be displayed with the following options:
 * a) Calculate the average grade
 * b) Find the maximum grade and display also the student 
 * with that grade (that is, the index or location of that grade in the vector).
 * c) Find the minimum grade and display also the student 
 * with that grade (that is, the index or location of that grade in the vector).
 * Modify options b and c to display all the students 
 * if the maximum (or minimum) grade is the same for several students.
 * Note: all of the above operations are carried out within the function main().
 */

#include <stdio.h>
#include <ctype.h>

#define MAX_STUDENTS 50

int main(void){

  int n; //Number of students
  int i;
  float grades[MAX_STUDENTS];
  float grade;
  char option;
  float max = 0;
  float min = 10;
  float sum = 0;
  float avg;
  //Get number of students
  do{
    printf("\nNumber of students [1, %d]: ", MAX_STUDENTS);
    scanf("%d", &n);
  }while(n < 1 || n > MAX_STUDENTS);

  //Get grade for each student
  for(i = 0; i < n; i++){
    do{
      printf("\nGrade of student #%d: ", i+1);
      scanf("%f", &grade);
      if(grade < 0 || grade > 10){
	printf("\nInvalid grade. Range: [0, 10]");
      }
    }while(grade < 0 || grade > 10);
    grades[i] = grade;

    //Store max, min and sum
    sum += grade;
    if(grade > max){
      max = grade;
    }
    if(grade < min){
      min = grade;
    }
  }
  //Calculate avg
  avg = sum / n;

  do{
    printf("\nMenu:");
    printf("\nA -> Calculate average grade");
    printf("\nB -> Calculate maximum grade");
    printf("\nC -> Calculate minimum grade");
    printf("\nD -> Exit");
    printf("\n\nSelect one option: ");
    scanf(" %c", &option);
    option = toupper(option);

    switch(option){
      case 'A':
	printf("\nThe average is: %.2f\n", avg);
	break;
      case 'B':
	printf("\nThe maximum is:\n");
	for(i = 0; i < n; i++){
	  if(grades[i] == max){
            printf("\tStudent %d: %.2f\n", i+1, grades[i]);
	  }
	}
	break;
      case 'C':
	printf("\nThe minimum is:\n");
	for(i = 0; i < n; i++){
	  if(grades[i] == min){
            printf("\tStudent %d: %.2f\n", i+1, grades[i]);
	  }
	}
	break;
      case 'D':
	printf("\nBye!\n");
	break;
      default:
	printf("\nInvalid option\n");
    }

  }while(option != 'D');

  return 0;
}
