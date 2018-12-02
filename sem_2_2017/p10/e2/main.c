/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * Write a program similar to program 1, but using a function Read() to 
 * load all the information of the structure, and Display() to show all 
 * the information on the screen.
 *
 * Write the two possible prototypes for the function Read() : the first version 
 * returns the structure as a value, and the second version receives the 
 * structure by reference. 
 *
 * In order to compute the maximum and minimum temperatures, use the 
 * function MaxMin that will be in charge of filling up the corresponding structure fields.
 * void MaxMin(T_CITY *pc); //structure by reference
 */
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define NAME 50
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

//MANDATORY FUNCTIONS
void ReadByReference(T_CITY *city);
T_CITY ReadByValue();
void Display(T_CITY city);
void MaxMin(T_CITY *pc);
//OPTIONAL FUNCTIONS
void GetName(char name[]);
int GetNumberOfTemperatures();
void GetTemperatures(float temperatures[], int num_temperatures);

int main(void){
  T_CITY city;
  int i;
  char option;

  do{
    printf("\nMENU:");
    printf("\nA -> Read by value");
    printf("\nB -> Read by reference");
    printf("\nC -> Exit");
    printf("\nEnter option: ");
    scanf(" %c", &option);
    option = toupper(option);

    switch(option){
      case 'A':
        city = ReadByValue();
        Display(city);
	break;
      case 'B':
        ReadByReference(&city);
        Display(city);
	break;
      case 'C':
	printf("\nGoodbye!\n");
	break;
      default:
	printf("\nERROR: Invalid option");
    }
  }while(option != 'C');

  return 0;
}

/*
 * Read a city by reference.
 * INPUT: City pointer to store the value.
 * OUTPUT: None
 */ 
void ReadByReference(T_CITY *city){
  GetName(city->name);
  city->num_temperatures = GetNumberOfTemperatures();
  GetTemperatures(city->temperatures, city->num_temperatures);
  MaxMin(city);
  return;
}

/*
 * Read a city and return by value.
 * INPUT: None.
 * OUTPUT: City struct.
 */ 
T_CITY ReadByValue(){
  T_CITY city;
  GetName(city.name);
  city.num_temperatures = GetNumberOfTemperatures();
  GetTemperatures(city.temperatures, city.num_temperatures);
  MaxMin(&city);
  return city;
}

/*
 * Show city struct details
 * INPUT: City struct.
 * OUTPUT: None.
 */ 
void Display(T_CITY city){
  int i;
  //Print struct details
  printf("\nCity: %s", city.name);
  printf("\nCity temperatures: ");
  for(i = 0; i < city.num_temperatures; i++){
    printf("%.2f  ", city.temperatures[i]);
  }
  printf("\nCity max temperature: %.2f", city.max_min.max);
  printf("\nCity min temperature: %.2f\n", city.max_min.min);
  return;
}

/*
 * Set the max and min temperatures of the city.
 * INPUT: City structure.
 * OUTPUT: None.
 */ 
void MaxMin(T_CITY *pc){
  int i;
  if(pc->num_temperatures > 0){
    pc->max_min.max = pc->temperatures[0];
    pc->max_min.min = pc->temperatures[0];
  }
  for(i = 0; i < pc->num_temperatures; i++){
    if(pc->max_min.max < pc->temperatures[i]){
      pc->max_min.max = pc->temperatures[i];
    }
    if(pc->max_min.min > pc->temperatures[i]){
      pc->max_min.min = pc->temperatures[i];
    }
  }
  return;
}

/*
 * Get the city name.
 * INPUT: The city name array.
 * OUTPUT: None.
 */ 
void GetName(char name[]){
  printf("\nEnter city name: ");
  scanf(" %s", name);
  return;
}

/*
 * Get the number of temperatures.
 * INPUT: None.
 * OUTPUT: Returns the number of temperatures.
 */ 
int GetNumberOfTemperatures(){
  int num_temperatures;
  //Store number of temperatures
  do{
    printf("\nEnter number of temperatures to store: ");
    scanf("%d", &num_temperatures);
    if(num_temperatures <= 0 || num_temperatures > TEMPERATURES){
      printf("\nERROR: Number of temperatures must be greater than 0 and less than %d", TEMPERATURES);
    }
  }while(num_temperatures <= 0 || num_temperatures > TEMPERATURES);

  return num_temperatures;
}

/*
 * Get temperatures array.
 * INPUT: Temperatures array and the number of temperatures.
 * OUTPUT: None.
 */ 
void GetTemperatures(float temperatures[], int num_temperatures){
  int i;
  //Store temperatures
  for(i = 0; i < num_temperatures; i++){
    printf("\nEnter temperature %d: ", i + 1);
    scanf("%f", &temperatures[i]);
  }
  return;
}
