/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * The City Hall of a Spanish village has set some mobile radars to control 
 * the speed of its main roads. After two months working, and due to the high 
 * number of fines collected, they have requested a program to control the payment 
 * and administration of these fines.
 *
 * The system will provide two options to load the information, manually or 
 * using files. The option will be selected at the beginning of the program. 
 * If the option selected is by file, we will load the file 
 * “fines.txt” which contains the following information:
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
 * to the exceeded threshold. This information is saved in the file “radars.txt”
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
 * So, if radar1 which limit is 50 km/h, detects a car at 80 km/h, the exceeded 
 * speed would be 30 km/h, that means , will be exceeded 60% and the 
 * fine will be 300 €. The program will display first the information of the 
 * file “ fines.txt ”. The city hall has requested a report containing the 
 * information about all fines with its amount of money, so we will need to calculate 
 * for each record of T_FINE the amount of money to pay. All this information will 
 * be displayed on screen and in a new file called “report.txt”.
 *
 * SECOND PART:
 * For this part, we will allow the user to load the information manually or 
 * using the file “ fines.txt ”. This option will be selected when starting the program. 
 * If the user selects the manual option, the program will follow the instructions 
 * of practice 10 part 3. If the choice is by file, we will first call the 
 * function CalculateNumRadars, to count the number of existing radars:
 * void CalculateNumRadars (FILE *f_radars, int *num_radars);
 *
 * Next, the program will allocate memory to create a vector of radars, 
 * and will read the information from the file “ radars.txt ” through the function:
* void LoadRadarsFile(FILE *f_radars, T_RADAR *radars, int num_radars);
*
* Next, as in the previous project, we will display the content of the vector 
* fines on screen and will calculate the total amount of fines.
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 100
#define PLATE_LEN 8
#define RADAR_FORMAT "%d\t%d\t%lf\t\t%lf\t\t%lf\n"
#define FINE_FORMAT "%d/%d/%d\t%d\t\t%s\t\t%d\n"
#define REPORT_FORMAT "%d/%d/%d\t%d\t\t%s\t\t%d\t%.2lf€\n"
#define RADAR_FILE "radars.txt"
#define FINE_FILE "fines.txt"
#define REPORT_FILE "report.txt"
#define RADAR_INPUT_NUM 5
#define FINE_INPUT_NUM 6
#define REPORT_INPUT_NUM 7

typedef struct {
 	int day;
 	int month;
	int year;
}T_DATE;

typedef struct {
	T_DATE date;
	int id_radar;
 	char plate[PLATE_LEN];
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
void LoadFinesManually(T_FINE *fines, int num_fines);
void CalculateFines(T_FINE *fines, int num_fines, T_RADAR *radars, int num_radars);
void CalculateNumRadars (FILE *f_radars, int *num_radars);
void CalculateNumFines (FILE *f_fines, int *num_fines);
void LoadRadarsFile(FILE *f_radars, T_RADAR *radars, int num_radars);
void LoadFinesFile(FILE *f_fines, T_FINE *fines, int num_fines);

//Radar functions
void AddRadarsToFile(T_RADAR *radars, int num_radars);
void AddRadarToFile(T_RADAR radar);
T_RADAR CreateRadar(void);
void ErrorIdRadar();
int IndexOfRadarInFile(int id);
void LoadRadarsFromFile(T_RADAR *radars);
int NumberOfRadarsInFile();
void PrintRadar(T_RADAR radar);
void PrintRadarHeader();
void PrintRadarInFile(void);
void RadarFactory(T_RADAR *radar, int id, int speed, double t_20, double t_40, double t_rest);
int ReadRadarFromFile(FILE *f_radar, T_RADAR *radar);
int WriteRadarToFile(T_RADAR radar);

//Fine functions
void AddFinesToFile(T_FINE *fines, int num_fines);
void AddFineToFile(T_FINE fine);
T_FINE CreateFine(void);
void LoadFinesFromFile(T_FINE *fines);
int NumberOfFinesInFile();
void PrintFine(T_FINE fine);
void PrintFineHeader();
void PrintFineInFile(void);
void FineFactory(T_FINE *fine, int day, int month, int year, int id_radar, char plate[], int speed);
int ReadFineFromFile(FILE *f_fine, T_FINE *fine);
int WriteFineToFile(T_FINE fine);

//Common functions
void ErrorLoadFile(char filename[]);
void ErrorAllocate(char msg[]);
void Error(char msg[]);
int Menu(void);
int HandleMenu(int option);
void AskAmount(char label[6], int *n);
void GenerateReport(void);
void PrintReport(T_FINE fine);

int main(void){
  while(HandleMenu(Menu()) != 6);
  return 0;
}

/*
 * Handle menu option.
 * INPUT: Option selected.
 * OUTPUT: Menu option.
 */
int HandleMenu(int option){
  int num_radars = 0;
  int num_fines = 0;
  T_RADAR *radars;
  T_FINE *fines;
  switch(option){
    case 1:
      AskAmount("radars", &num_radars);
      radars = (T_RADAR *) calloc(num_radars, sizeof(T_RADAR));
      if(radars != NULL){
	LoadRadarsManually(radars, num_radars);
	free(radars);
      }else{
        ErrorAllocate("HandleMenu: Loading radar");
      }
      break;
    case 2:
      PrintRadarInFile();
      break;
    case 3:
      AskAmount("fines", &num_fines);
      fines = (T_FINE *) calloc(num_fines, sizeof(T_FINE));
      if(fines != NULL){
	LoadFinesManually(fines, num_fines);
	free(fines);
      }else{
        ErrorAllocate("HandleMenu: Loading fine");
      }
      break;
    case 4:
      PrintFineInFile();
      break;
    case 5:
      GenerateReport();
      break;
    case 6:
      printf("\nGoodbye!\n");
      break;
    default:
      Error("Invalid option");
  }
  return option;
}

void GenerateReport(void){
  int i;
  int read;
  T_RADAR *radars;
  int num_radars = NumberOfRadarsInFile();
  FILE *f_radars;
  T_RADAR radar;
  
  T_FINE *fines;
  int num_fines = NumberOfFinesInFile();
  FILE *f_fines;
  T_FINE fine;
  
  f_radars = fopen(RADAR_FILE, "r");
  f_fines = fopen(FINE_FILE, "r");
  if(f_radars != NULL && f_fines != NULL){
    rewind(f_radars);
    rewind(f_fines);
    radars = (T_RADAR *) calloc(num_radars, sizeof(T_RADAR));
    fines = (T_FINE *) calloc(num_fines, sizeof(T_FINE));
    if(radars != NULL && fines != NULL){

      for(i = 0; i < num_radars; i++){
	read = ReadRadarFromFile(f_radars, &radar);
	if(read == RADAR_INPUT_NUM){
	  radars[i] = radar;
	}
      }

      for(i = 0; i < num_fines; i++){
        read = ReadFineFromFile(f_fines, &fine);
        if(read == FINE_INPUT_NUM){
          fines[i] = fine;
        }
      }
      CalculateFines(fines, num_fines, radars, num_radars);
      free(radars);
      free(fines);
    }else if(radars != NULL){
      ErrorAllocate("GenerateReport: loading fines");
      free(radars);
    }else if(fines != NULL){
      ErrorAllocate("GenerateReport: loading radars");
      free(fines);
    }
    fclose(f_radars);
    fclose(f_fines);
  }
  else{
    Error("Can't open file radars.txt and fines.txt");
  }
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
  double total = 0;
  FILE *f_report;
  f_report = fopen(REPORT_FILE, "w");
  if(f_report != NULL){
    printf("\nREPORT");
    PrintReportHeader();
    for(i = 0; i < num_fines; i++){
      radar_index = IndexOfRadarInFile(fines[i].id_radar);
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
        total += fine_amount;
        PrintReport(fines[i]);

        fprintf(f_report, REPORT_FORMAT,
		  fines[i].date.day, 
		  fines[i].date.month,
		  fines[i].date.year,
		  fines[i].id_radar,
		  fines[i].plate,
                  fines[i].speed,
                  fines[i].fine);
      }
    }
    fclose(f_report);
    printf("\nTotal fines balance: %.2lf€\n\n", total);   
  }else{
    ErrorLoadFile(REPORT_FILE);
  }  

  return;
}

/*
 * Show a menu.
 * INPUT: None.
 * OUTPUT: None.
 */ 
int Menu(void){
  int option;
  printf("\nMENU:");
  printf("\n1 - Add radar");
  printf("\n2 - Show radars");
  printf("\n3 - Add fine");
  printf("\n4 - Show fines");
  printf("\n5 - Generate report");
  printf("\n6 - Exit");
  printf("\nSelect option: ");
  scanf("%d", &option);
  return option;
}

////////////////////////////////////////
///////////RADAR FUNCTIONS//////////////
////////////////////////////////////////

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
  AddRadarsToFile(radars, num_radars);
  return;
}

/**
 * Add a collection of radars into the radars file.
 * INPUT: Collection of radars and the number of radars.
 * OUTPUT: None.
 */ 
void AddRadarsToFile(T_RADAR *radars, int num_radars){
  int i = 0;
  for(i = 0; i < num_radars; i++){
    AddRadarToFile(radars[i]);
  }
  return;
}

/**
 * Add a radar into the radars file.
 * INPUT: Radar.
 * OUTPUT: None.
 */ 
void AddRadarToFile(T_RADAR radar){
  FILE *f_radar;
  int index_of = IndexOfRadarInFile(radar.id_radar);
  if(index_of >= 0){ 
    ErrorIdRadar();
    PrintRadarHeader();
    PrintRadar(radar);
  }else{
    WriteRadarToFile(radar);
  }	
  return;
}

/*
 * Print all radars in the radars.txt file.
 * INPUT: None.
 * OUTPUT: None.
 */ 
void PrintRadarInFile(void){
  int count = NumberOfRadarsInFile();
  int i;
  T_RADAR *radars;
  
  radars = (T_RADAR *) calloc(count, sizeof(T_RADAR));

  if(radars != NULL){
    LoadRadarsFromFile(radars);
    printf("\nRADARS:");
    PrintRadarHeader();
    for(i = 0; i < count; i++){
      PrintRadar(radars[i]);
    }
    free(radars);
  }else{
    ErrorAllocate("PrintRadarInFile");
  }
  return;
}

/*
 * Look for a radar in the radars.txt file.
 * INPUT: Id of the radar to look for.
 * OUTPUT: -1 if it's not found, otherwise, returns the index of the element within the array.
 */ 
int IndexOfRadarInFile(int id){
  int index = -1;
  int count = NumberOfRadarsInFile();
  int i;
  T_RADAR *radars;
  
  radars = (T_RADAR *) calloc(count, sizeof(T_RADAR));

  if(radars != NULL){
    LoadRadarsFromFile(radars);
    for(i = 0; i < count && index == -1; i++){
      if(id == radars[i].id_radar){
	index = i;
      }
    }
    free(radars);
  }else{
    ErrorAllocate("IndexOfRadarInFile");
  }
  return index;
}

/*
 * Load all radars from file.
 * INPUT: Radars vector to store them.
 * OUTPUT: None.
 */ 
void LoadRadarsFromFile(T_RADAR *radars){
  FILE *f_radar;  
  int counter = NumberOfRadarsInFile();

  f_radar = fopen(RADAR_FILE, "r");
  if(f_radar != NULL){
    rewind(f_radar);
    LoadRadarsFile(f_radar, radars, counter);
    fclose(f_radar);
  }
  return;
}

/*
 * Load all radars from file.
 * INPUT: Radars vector to store them.
 * OUTPUT: None.
 */ 
void LoadRadarsFile(FILE *f_radars, T_RADAR *radars, int num_radars){
  int read;
  T_RADAR radar;
  int i = 0;
  if(f_radars != NULL){
    rewind(f_radars);
    do{
      read = ReadRadarFromFile(f_radars, &radar);
      if(read == RADAR_INPUT_NUM){
        radars[i] = radar;
	i++;
      }
    }while(read != 0 && read != EOF);
  }else{
    ErrorLoadFile(RADAR_FILE);
  }
  return;
}

/*
 * Get the number of radars stored in the radars.txt file.
 * INPUT: None.
 * OUTPUT: Number of radars.
 */ 
int NumberOfRadarsInFile(){
  FILE *f_radar;
  int counter = 0;

  f_radar = fopen(RADAR_FILE, "r");
  if(f_radar != NULL){
    rewind(f_radar);
    CalculateNumRadars(f_radar, &counter);
    fclose(f_radar);
  }
  return counter;
}

/*
 * Get the number of radars stored in the radars.txt file.
 * INPUT: File of radars and the variable to store the number of radars.
 * OUTPUT: None.
 */
void CalculateNumRadars (FILE *f_radars, int *num_radars){
  int counter = 0;
  int read;
  T_RADAR radar;
  if(f_radars != NULL){
    do{
      read = ReadRadarFromFile(f_radars, &radar);
      if(read == RADAR_INPUT_NUM){
        counter++;
      }
    }while(read != 0 && read != EOF);
  }else{
    ErrorLoadFile(RADAR_FILE);
  }
  *num_radars = counter;
}

/*
 * Read one radar from the radars.txt file.
 * INPUT: Radar file and the radar variable to store within it.
 * OUTPUT: Result of scanf.
 */ 
int ReadRadarFromFile(FILE *f_radar, T_RADAR *radar){
  int id;
  int speed;
  double t_20;
  double t_40;
  double t_rest;
  int read = fscanf(f_radar, RADAR_FORMAT, &id, &speed, &t_20, &t_40, &t_rest);
  if(read == RADAR_INPUT_NUM){
    RadarFactory(radar, id, speed, t_20, t_40, t_rest); 
  }
  return read;
}

/*
 * Writes one radar into the radars.txt file.
 * INPUT: Radar variable.
 * OUTPUT: Result of fprintf.
 */ 
int WriteRadarToFile(T_RADAR radar){
  FILE *f_radar;
  int write;
  f_radar = fopen(RADAR_FILE, "a");
  if(f_radar != NULL){
    write = fprintf(f_radar, RADAR_FORMAT,
		  radar.id_radar, 
		  radar.limit_speed,
		  radar.threshold20,
		  radar.threshold40,
		  radar.threshold_rest);
    fclose(f_radar);
  }
  return write;
}

/*
 * Print a radar.
 * INPUT: Radar.
 * OUTPUT: None.
 */ 
void PrintRadar(T_RADAR radar){
  printf(RADAR_FORMAT,
		  radar.id_radar, 
		  radar.limit_speed,
		  radar.threshold20,
		  radar.threshold40,
		  radar.threshold_rest);
  return;
}

/*
 * Print a radar header.
 * INPUT: Radar.
 * OUTPUT: None.
 */ 
void PrintRadarHeader(){
  printf("\nID\tSPEED\tTRESHOLD 20%\t\tTRESHOLD 40%\t\tTRESHOLD REST\n");  
  return;
}

/*
 * Creates a radar.
 * INPUT: All radar info and the radar where all will be stored in.
 * OUTPUT: None.
 */ 
void RadarFactory(T_RADAR *radar, int id, int speed, double t_20, double t_40, double t_rest){
  radar->id_radar = id;
  radar->limit_speed = speed;
  radar->threshold20 = t_20;
  radar->threshold40 = t_40;
  radar->threshold_rest = t_rest;
  return;
}

/*
 * Create a T_RADAR element.
 * INPUT: None.
 * OUTPUT: A T_RADAR element.
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

////////////////////////////////////////
///////////FINES FUNCTIONS//////////////
////////////////////////////////////////


/*
 * Load all fines manually.
 * INPUT: Fine pointer to store all fines and the number of fines.
 * OUTPUT: None.
 */ 
void LoadFinesManually (T_FINE *fines, int num_fines){
  int i;
  for(i = 0; i < num_fines; i++){
    printf("\nFine %d details", i + 1);
    fines[i] = CreateFine();
  }
  AddFinesToFile(fines, num_fines);
  return;
}

/**
 * Add a collection of fines into the fines file.
 * INPUT: Collection of fines and the number of fines.
 * OUTPUT: None.
 */ 
void AddFinesToFile(T_FINE *fines, int num_fines){
  int i = 0;
  for(i = 0; i < num_fines; i++){
    AddFineToFile(fines[i]);
  }
  return;
}

/**
 * Add a fine into the fines file.
 * INPUT: Fine.
 * OUTPUT: None.
 */ 
void AddFineToFile(T_FINE fine){
  WriteFineToFile(fine);	
  return;
}

/*
 * Print all fines in the fines.txt file.
 * INPUT: None.
 * OUTPUT: None.
 */ 
void PrintFineInFile(void){
  int count = NumberOfFinesInFile();
  int i;
  T_FINE *fines;
  
  fines = (T_FINE *) calloc(count, sizeof(T_FINE));

  if(fines != NULL){
    LoadFinesFromFile(fines);
    printf("\nFINES:");
    PrintFineHeader();
    for(i = 0; i < count; i++){
      PrintFine(fines[i]);
    }
    free(fines);
  }else{
    ErrorAllocate("PrintFineInFile");
  }
  return;
}

/*
 * Load all fines from file.
 * INPUT: Fines vector to store them.
 * OUTPUT: None.
 */ 
void LoadFinesFromFile(T_FINE *fines){
  FILE *f_fine;  
  int counter = NumberOfFinesInFile();

  f_fine = fopen(FINE_FILE, "r");
  if(f_fine != NULL){
    rewind(f_fine);
    LoadFinesFile(f_fine, fines, counter);
    fclose(f_fine);
  }
  return;
}

/*
 * Load all fines from file.
 * INPUT: Fines vector to store them.
 * OUTPUT: None.
 */ 
void LoadFinesFile(FILE *f_fines, T_FINE *fines, int num_fines){
  int read;
  T_FINE fine;
  int i = 0;
  if(f_fines != NULL){
    rewind(f_fines);
    do{
      read = ReadFineFromFile(f_fines, &fine);
      if(read == FINE_INPUT_NUM){
        fines[i] = fine;
	i++;
      }
    }while(read != 0 && read != EOF);
  }else{
    ErrorLoadFile(FINE_FILE);
  }
  return;
}

/*
 * Get the number of fines stored in the fines.txt file.
 * INPUT: None.
 * OUTPUT: Number of fines.
 */ 
int NumberOfFinesInFile(){
  FILE *f_fine;
  int counter = 0;

  f_fine = fopen(FINE_FILE, "r");
  if(f_fine != NULL){
    rewind(f_fine);
    CalculateNumFines(f_fine, &counter);
    fclose(f_fine);
  }
  return counter;
}

/*
 * Get the number of fines stored in the fines.txt file.
 * INPUT: File of radars and the variable to store the number of radars.
 * OUTPUT: None.
 */
void CalculateNumFines (FILE *f_fines, int *num_fines){
  int counter = 0;
  int read;
  T_FINE fine;
  if(f_fines != NULL){
    do{
      read = ReadFineFromFile(f_fines, &fine);
      if(read == FINE_INPUT_NUM){
        counter++;
      }
    }while(read != 0 && read != EOF);
  }else{
    ErrorLoadFile(FINE_FILE);
  } 
  *num_fines = counter;
}

/*
 * Read one fine from the fines.txt file.
 * INPUT: Fine file and the fine variable to store within it.
 * OUTPUT: Result of scanf.
 */ 
int ReadFineFromFile(FILE *f_fine, T_FINE *fine){
  int day;
  int month;
  int year;
  int id;
  char plate[PLATE_LEN];
  int speed;
  int read = fscanf(f_fine, FINE_FORMAT, &day, &month, &year, &id, plate, &speed);
  if(read == FINE_INPUT_NUM){
    FineFactory(fine, day, month, year, id, plate, speed);
  }
  return read;
}

/*
 * Writes one fine into the fines.txt file.
 * INPUT: Fine variable.
 * OUTPUT: Result of fprintf.
 */ 
int WriteFineToFile(T_FINE fine){
  FILE *f_fine;
  int write;
  f_fine = fopen(FINE_FILE, "a");
  if(f_fine != NULL){
    write = fprintf(f_fine, FINE_FORMAT,
		  fine.date.day, 
		  fine.date.month,
		  fine.date.year,
		  fine.id_radar,
		  fine.plate,
                  fine.speed);
    fclose(f_fine);
  }
  return write;
}

/*
 * Print a fine.
 * INPUT: Fine.
 * OUTPUT: None.
 */ 
void PrintFine(T_FINE fine){
  printf(FINE_FORMAT,
		  fine.date.day, 
		  fine.date.month,
		  fine.date.year,
		  fine.id_radar,
		  fine.plate,
                  fine.speed);
  return;
}

/*
 * Print a fine header.
 * INPUT: Fine.
 * OUTPUT: None.
 */ 
void PrintFineHeader(){
  printf("\nDay/Month/Year\tID RADAR\tPLATE\t\tSPEED\n");  
  return;
}

/*
 * Creates a fine.
 * INPUT: All fine info and the fine where all will be stored in.
 * OUTPUT: None.
 */ 
void FineFactory(T_FINE *fine, int day, int month, int year, int id_radar, char plate[], int speed){
  fine->date.day = day;
  fine->date.month = month;
  fine->date.year = year;
  fine->id_radar = id_radar;
  strcpy(fine->plate, plate);
  fine->speed = speed;
  fine->fine = 0;
  return;
}

/*
 * Create a T_FINE element.
 * INPUT: None.
 * OUTPUT: A T_Fine element.
 */
T_FINE CreateFine(void){
  T_FINE fine;
 
  printf("\nEnter fine day: ");
  scanf("%d", &fine.date.day);

  printf("\nEnter fine month: ");
  scanf("%d", &fine.date.month);

  printf("\nEnter fine year: ");
  scanf("%d", &fine.date.year);

  printf("\nEnter radar id: ");
  scanf("%d", &fine.id_radar);

  getchar();
  printf("\nEnter car plate: ");
  fgets(fine.plate, PLATE_LEN, stdin);

  printf("\nEnter speed: ");
  scanf("%d", &fine.speed);
  
  fine.fine = 0;

  return fine;
}


////////////////////////////////////////
//////////COMMON FUNCTIONS//////////////
////////////////////////////////////////

/*
 * Show an error message when file can't be opened.
 * INPUT: File name.
 * OUTPUT: None.
 */ 
void ErrorLoadFile(char filename[]){
  Error(strcat("Can't load file: ", filename));
  return;
}

/*
 * Show an error message when can't allocate memory.
 * INPUT: None.
 * OUTPUT: None.
 */ 
void ErrorAllocate(char msg[]){
  Error(strcat("Not enought memory: ", msg));
  return;
}

/*
 * Show an error message when id radar is repeated.
 * INPUT: None.
 * OUTPUT: None.
 */ 
void ErrorIdRadar(){
  Error("Id radar is repeated");
  return;
}

/*
 * Show a custom error message.
 * INPUT: None.
 * OUTPUT: None.
 */ 
void Error(char msg[]){
  printf("\nERROR: %s.\n", msg);
  return;
}

/*
 * Ask for the amount of elements.
 * INPUT: Elements name and the variable to store the number of elements.
 * OUTPUT: None.
 */ 
void AskAmount(char label[6], int *n){
  do{
    printf("\nHow many %s do you want to add? ", label);
    scanf("%d", n);
    if((*n) <= 0 || (*n) > MAX){
      Error("amount must be greater than 0 and less than 100");
    }
  }while((*n) <= 0 || (*n) > MAX);
  return;
}

/*
 * Print a report header.
 * INPUT: Fine.
 * OUTPUT: None.
 */ 
void PrintReportHeader(){
  printf("\nDay/Month/Year\tID RADAR\tPLATE\t\tSPEED\tFINE\n");  
  return;
}

/*
 * Print a fine.
 * INPUT: Fine.
 * OUTPUT: None.
 */ 
void PrintReport(T_FINE fine){
  printf(REPORT_FORMAT,
		  fine.date.day, 
		  fine.date.month,
		  fine.date.year,
		  fine.id_radar,
		  fine.plate,
                  fine.speed,
                  fine.fine);
  return;
}
