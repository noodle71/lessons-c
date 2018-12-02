/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * The City Hall of a Spanish village has set some mobile radars to control 
 * the speed of its main roads. After two months working, and due to the high 
 * number of fines collected, they have requested a program to control the 
 * payment and administration of these fines. Each fine contains the following information:
 *
 * Date		Radar	Car license plate	Speed (Km/h)
 * 07/10/2017	1	6645 GLV		75
 * 08/10/2017	3	3345 FXR		150
 * 08/10/2017	2	6645 GLV		120
 * 09/10/2017	1	1475 HXT		80
 *
 * To hold this information, we will use this structure:
 * typedef struct {
 * 	T_DATE date;
 * 	int id_radar;
 * 	char plate[8];
 * 	int speed;
 * 	double fine;
 * }T_FINE; 
 *
 * Being T_DATE this structure:
 * typedef struct {
 * 	int day;
 * 	int month;
 * 	int year;
 * }T_DATE;
 *
 * Each radar contains information about the speed limit and the fines according 
 * to the exceeded threshold:
 *
 * Radar	Speed (Km/h)	Threshold (0-20%) €	(20-40%) €	>40% €
 * 1		50		120			200		300
 * 2		90		100			150		200
 * 3		120		150			250		500
 *
 * This information is stored in the structure:
 * typedef struct {
 * 	int id_radar;
 * 	int limit_speed;
 * 	int threshold20;
 * 	int threshold30;
 * 	int threshold _rest;
 * }T_RADAR;
 *
 * So, if radar1 which limit is 50 km/h, detects a car at 80 km/h, the exceeded speed 
 * would be 30 km/h, that means , will be exceeded 60% and the fine will be 300 €.
 *
 * FIRST PART:
 * For this part, the user must introduce by keyboard the information about 
 * radars through the function:
 * 
 * void LoadRadarsManually (T_RADAR *radars, int num_radars);
 * 
 * Previously you have to ask to the user for the number of radars and 
 * allocate memory for the radars vector.
 *
 * Next, we will load the existing fines. For that, we must ask 
 * to the user the number of fines, and allocate memory for all of them. 
 * The load will be through the function:
 *
 * void LoadFinesManually(T_FINE *fines, int num_fines);
 * 
 * Once filled the vector, the process will calculate the total amount of the 
 * fines and update the value double fine of the structure T_FINE by means of 
 * the function:
 *
 * void CalculateFines(T_FINE *fines, int num_fines, T_RADAR *radars, int num_radars);
 * 
 * Display the information of the vector fines on screen.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100

typedef struct {
 	int day;
 	int month;
	int year;
}T_DATE;

typedef struct {
	T_DATE date;
	int id_radar;
 	char plate[8];
 	int speed;
 	double fine;
}T_FINE; 

typedef struct {
 	int id_radar;
 	int limit_speed;
 	double threshold20;
	double threshold40;
 	double threshold_rest;
}T_RADAR;
 
//Mandatory functions 
void LoadRadarsManually (T_RADAR *radars, int num_radars);
void LoadFinesManually(T_FINE *fines, int num_fines, T_RADAR *radars, int num_radars);
void CalculateFines(T_FINE *fines, int num_fines, T_RADAR *radars, int num_radars);
//Optional functions
T_RADAR CreateRadar(void);
T_FINE CreateFine(T_RADAR *radars, int num_radars);
int IndexOfRadar(int id_radar, T_RADAR *radars, int num_radars);
int AskAmount(char label[6]);
void PrintFines(T_FINE *fines, int num_fines);
void PrintRadars(T_RADAR *radars, int num_radars);

int main(void){
  int num_radars = AskAmount("radars");
  int num_fines = AskAmount("fines");

  T_RADAR *radars;
  T_FINE *fines;

  radars = (T_RADAR *)calloc(num_radars, sizeof(T_RADAR));
  fines = (T_FINE *)calloc(num_fines, sizeof(T_FINE));

  if(radars != NULL & fines != NULL){
    LoadRadarsManually (radars, num_radars);
    LoadFinesManually(fines, num_fines, radars, num_radars);
    CalculateFines(fines, num_fines, radars, num_radars);
    PrintFines(fines, num_fines);
    PrintRadars(radars, num_radars);
  }else{
    printf("\nERROR: Not enought memory");
  }

  return 0;
}

/*
 * Load all radars manually.
 * INPUT: Radar pointer to store all radars and the number of radars.
 * OUTPUT: None.
 */ 
void LoadRadarsManually (T_RADAR *radars, int num_radars){
  int i;
  for(i = 0; i < num_radars; i++){
    printf("\nRadar %d details", i + 1);
    radars[i] = CreateRadar();
  }
  return;
}

/*
 * Load all fines manually.+
 * INPUT: Fines pointer to store all fines and the number of fines. Also we receive the radars
 * to check that the radar id exists.
 * OUTPUT: None.
 */ 
void LoadFinesManually(T_FINE *fines, int num_fines, T_RADAR *radars, int num_radars){
  int i;
  for(i = 0; i < num_radars; i++){
    printf("\nFine %d details", i + 1);
    fines[i] = CreateFine(radars, num_radars);
  }
  return;
}

/*
 * Update fines to store the amount to pay.
 * INPUT: Fines, the number of fines, radars and the number of radars.
 * OUTPUT: None.
 */ 
void CalculateFines(T_FINE *fines, int num_fines, T_RADAR *radars, int num_radars){
  int i;
  int radar_index;
  T_RADAR radar;
  int speed;
  int limit_speed;
  float pct;
  double fine_amount;
  for(i = 0; i < num_fines; i++){
    radar_index = IndexOfRadar(fines[i].id_radar, radars, num_radars);
    if(radar_index >= 0){
      radar = radars[radar_index];
      speed = fines[i].speed;
      limit_speed = radar.limit_speed;
      pct = (speed * 100) / limit_speed;
      fine_amount = 0;
      if(pct > 100 && pct <= 120){
        fine_amount = radar.threshold20;
      }else if(pct > 120 && pct <= 140){
        fine_amount = radar.threshold40;
      }else if(pct > 140){
        fine_amount = radar.threshold_rest;
      }else{
        fine_amount = 0;
      }
      fines[i].fine = fine_amount;
    }
  }
  return;
}

/*
 * Create a T_FINE element.
 * INPUT: None.
 * OUTPUT: A T_Fine element.
 */
T_RADAR CreateRadar(void){
  T_RADAR radar;
  
  printf("\nEnter radar id: ");
  scanf("%d", &radar.id_radar);

  printf("\nEnter speed limit: ");
  scanf("%d", &radar.limit_speed);

  printf("\nEnter fine amout <= 20%%: ");
  scanf("%lf", &radar.threshold20);
  
  printf("\nEnter fine amout <= 40%%: ");
  scanf("%lf", &radar.threshold40);
  
  printf("\nEnter fine amout > 40%%: ");
  scanf("%lf", &radar.threshold_rest);

  return radar;
}

/*
 * Create a T_FINE element.
 * INPUT: All the radars and the amount of radars. It's used to check the radar exists.
 * OUTPUT: A T_Fine element.
 */ 
T_FINE CreateFine(T_RADAR *radars, int num_radars){
  T_FINE fine;
  int index_of_radar;
  do{
    printf("\nEnter the radar id: ");
    scanf("%d", &fine.id_radar);
    index_of_radar = IndexOfRadar(fine.id_radar, radars, num_radars);
    if(index_of_radar < 0){
      printf("\nERROR: Radar not found");
    }
  }while(index_of_radar < 0);

  printf("\nEnter speed: ");
  scanf("%d", &fine.speed);

  fine.fine = 0;

  do{
    printf("\nEnter day: ");
    scanf("%d", &fine.date.day);
  }while(fine.date.day < 1 || fine.date.day > 31);

  do{
    printf("\nEnter month: ");
    scanf("%d", &fine.date.month);
  }while(fine.date.month < 1 || fine.date.month > 12);  

  do{
    printf("\nEnter year: ");
    scanf("%d", &fine.date.year);
  }while(fine.date.year < 1977);
  
  printf("\nEnter car plate: ");
  scanf(" %s", fine.plate);
  
  return fine;
}

/*
 * Look for radar id and returns the index.
 * INPUT: The id of the radar, all the radars and the amount of radars.
 * OUTPUT: The index where the id of the radar is. If it's -1, it's not found.
 */ 
int IndexOfRadar(int id_radar, T_RADAR *radars, int num_radars){
  int found = -1;
  int i;
  for(i = 0; i < num_radars && found == -1; i++){
    if(radars[i].id_radar == id_radar){
      found = i;
    }
  }
  return found;
}

/*
 * Ask the amount of elements.
 * INPUT: Label to print.
 * OUTPUT: Integer as the amount of elements.
 */
int AskAmount(char label[6]){
  int amount;
  do{
    printf("\nEnter the number of %s you want to enter manually: ", label);
    scanf("%d", &amount);
    if(amount <= 0 || amount > MAX){
      printf("\nERROR: Invalid amount. Must be greater than 0 and less than %d", MAX);
    } 
  }while(amount <= 0 || amount > MAX);
  return amount;
}

/*
 * Print all fines details.
 * INPUT: Fines and the amount of fines.
 * OUTPUT None.
 */ 
void PrintFines(T_FINE *fines, int num_fines){
  int i;
  printf("\nFINES:");
  printf("\nDate\t\tRadar\tPlate\tSpeed\tFine");
  for(i = 0; i < num_fines; i++){
    printf("\n%0d/%0d/%2d\t%d\t%s\t%d\t%.2lf", 
		    fines[i].date.day,
		    fines[i].date.month,
		    fines[i].date.year,
		    fines[i].id_radar,
		    fines[i].plate,
		    fines[i].speed,
		    fines[i].fine);
  }
  printf("\n");
  return;
}

/*
 * Print all radars details.
 * INPUT: Radars and the amount of radars.
 * OUTPUT None.
 */ 
void PrintRadars(T_RADAR *radars, int num_radars){
  int i;
  printf("\nRADARS:");
  printf("\nId\tLimit\tFine <= 20%%\tFine <= 40%%\tFine > 40%%");
  for(i = 0; i < num_radars; i++){
    printf("\n%d\t%d\t%lf\t\t%lf\t\t%lf", 
		    radars[i].id_radar,
		    radars[i].limit_speed,
		    radars[i].threshold20,
		    radars[i].threshold40,
		    radars[i].threshold_rest);
  }
  printf("\n");
  return;
}
