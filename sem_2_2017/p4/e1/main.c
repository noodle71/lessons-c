/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 *
 * In forensic medicine, the length of some bones can be used to 
 * estimate the height of a person younger than 30 years old. 
 * 
 * For a man the height is computed according to:
 * height (cm) = 69.089 + 2.238 * length_tibia (cm)
 *
 * For a woman the height is computed according to:
 * height (cm) = 61.412 + 2.317 * length_tibia (cm)
 * 
 * Write a function ComputeHeight() that receives the length of 
 * the tibia bone and the gender (either 'M' or 'F') 
 * as arguments and returns the height of the person. 
 * The prototype will be: 
 * double ComputeHeight (double length_tibia, char gender);
 *
 * Also write the main program to test the function. 
 * The main program must read (and validate) input values
 * from the user, then call the function, and finally display 
 * the result (only the main program can display the
 * result, no printf or scanf can be used inside the function.
 *
 * After calculating and displaying the height of a person, 
 * ask the user if he want to enter the length of the
 * tibia for more people and if the answer is yes, ask for new data
 *
 */

#include <stdio.h>
#include <ctype.h>

#define TIBIA_MALE_CONSTANT 2.238
#define MALE_CONSTANT 69.089
#define TIBIA_FEMALE_CONSTANT 2.317
#define FEMALE_CONSTANT 61.412

//Function prototypes
double ComputeHeight (double length_tibia, char gender);

int main(void){
  double tibia_length;
  char gender;
  int age;
  char option;
  double height;

  do{
   
    //Enter valid age
    do{
      printf("Enter your age. (Must be a valid number): ");
      scanf("%d", &age);
    }while(age < 0);

    //This only works when age is less than 30 years old
    if(age >= 30){
      printf("\nSorry, we can't calculate your height using your tibia lenght.");
      printf("\nThis only works for people younger than 30 years old.");
    }else{
      //Enter valid gender
      do{
        printf("\nEnter your gender ('M' for male, 'F' for female): ");
        scanf(" %c", &gender);
	gender = toupper(gender);
      }while(gender != 'M' && gender != 'F');

      //Enter valid tibia length
      do{
        printf("\nEnter your tibia length in cm. (Must be a valid number): ");
        scanf("%lf", &tibia_length);
      }while(tibia_length <= 0);

      height = ComputeHeight(tibia_length, gender);
      if(height == 0){
        printf("\nError. Enter a correct gender");
      }else{
        printf("\nIf the tibia length is %.3lf cm, the height should be %.2lf cm", tibia_length, height);
      }

    }

    printf("\n\n\nDo you want to continue?\nPress Y to continue or any other key to exit: ");
    scanf(" %c", &option);

  }while(toupper(option) == 'Y');

  return 0;
}

/*
 * ComputeHeight
 * Input: Length of the tibia in cm and the gender
 * Output: Height of the person
 */
double ComputeHeight (double length_tibia, char gender){
  double height = 0;
  char gender_uppercase = toupper(gender);
  switch(gender_uppercase){
    case 'M':
      height = MALE_CONSTANT + TIBIA_MALE_CONSTANT * length_tibia;
      break;
    case 'F':
      height = FEMALE_CONSTANT + TIBIA_FEMALE_CONSTANT * length_tibia;
      break;
  }
  //Will return 0 if the gender is not correct
  return height;
}
