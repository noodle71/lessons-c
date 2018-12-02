/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * Write a program that defines a structure called T_CITY for storing the 
 * following information:
 * City name
 * Vector of temperatures
 * Number of temperatures stored inside the vector
 * Another structure T_MAXMIN to store the maximum and minimum temperatures of the city.
 *
 * The program will read from the keyboard the basic information about one 
 * city (name, and vector of temperatures), and then it will calculate maximum 
 * and minimum temperatures. Finally the program will display on the screen all 
 * the information stored in the structure.
 */
#include<stdio.h>
#include<string.h>
#define NAME 30
#define TEMPERATURES 30

typedef struct{
  float min;
  float max;
}T_MAXMIN;

typedef struct{
  char name[NAME];
  float temperatures[TEMPERATURES];
  int num_temperatures;
  T_MAXMIN max_min;
}T_CITY;

int main(void){
  T_CITY city;
  int i;
  
  printf("\nEnter city name: ");
  fgets(city.name, NAME, stdin);
  //Change \n character with \0
  city.name[strlen(city.name) - 1] = '\0';
  //Store number of temperatures
  do{
    printf("\nEnter number of temperatures to store: ");
    scanf("%d", &city.num_temperatures);
    if(city.num_temperatures <= 0 || city.num_temperatures > TEMPERATURES){
      printf("\nERROR: Number of temperatures must be greater than 0 and less than %d", TEMPERATURES);
    }
  }while(city.num_temperatures <= 0 || city.num_temperatures > TEMPERATURES);

  //Store temperatures
  for(i = 0; i < city.num_temperatures; i++){
    printf("\nEnter temperature %d: ", i + 1);
    scanf("%f", &city.temperatures[i]);
    if(i == 0){
      city.max_min.max = city.temperatures[i];
      city.max_min.min = city.temperatures[i];
    }else{
      if(city.temperatures[i] < city.max_min.min){
        city.max_min.min = city.temperatures[i];
      }
      if(city.temperatures[i] > city.max_min.max){
        city.max_min.max = city.temperatures[i];
      }
    }
  }

  //Print struct details
  printf("\nCity: %s", city.name);
  printf("\nCity temperatures: ");
  for(i = 0; i < city.num_temperatures; i++){
    printf("%.2f  ", city.temperatures[i]);
  }
  printf("\nCity max temperature: %.2f", city.max_min.max);
  printf("\nCity min temperature: %.2f\n", city.max_min.min);


  return 0;
}
