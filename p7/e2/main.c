/*
 * AUTHOR: Angel Fernandez Camba
 * DATE: 18/02/18
 * DESCRIPTION: 
 * Write a C program that declares a matrix float kilometers[N][N] (N is 4) 
 * to store distances among cities in Andalusia, Spain (Andalucía). 
 * It will also be necessary to declare a matrix char capitals[N][M] (M is 30) 
 * to store the names of the capitals of 4 provinces in 
 * Andalusia (Jaen, Cordoba, Sevilla, Huelva). 
 * It is requested:
 *
 * Write a function void LoadNames(char cities[][M]); to read from the 
 * keyboard the names of all the cities. 
 * This would be the resulting matrix: 
 *
 * Jaen 
 * Cordoba 
 * Sevilla 
 * Huelva
 *
 *
 * Write a function void LoadDistances(char cities[][M], float dist[][N]); 
 * to read from the keyboard the distances among all cities. 
 * The message used to ask the user for a distance must include the city names. 
 * This would be the resulting matrix: 
 * 
 * 0 104 242 336
 * 104 0 138 232
 * 242 138 0 94
 * 336 232 94 0
 *
 * 
 * The main program should display the matrix of distances after 
 * calling LoadDistances:
 *
 * Write a function int Validate(char name[], char cities[][M]); that receives 
 * the name of a city and searches the matrix of cities. 
 * If the city is found the index (row) in matrix cities is returned; 
 * otherwise a value -1 is returned.
 * 
 *
 * Write a function float FindKilometers(float dist[][N], int i_origin, int i_destination); 
 * that return de distance (in km) between two cities. The distance will be displayed 
 * using printf in the main program
 */

#include <stdio.h>
#include <string.h>
#define N 4
#define M 30

//MANDATORY FUNCTIONS
void LoadDistances(char cities[][M], float dist[][N]);
void LoadNames(char cities[][M]);
int Validate(char name[], char cities[][M]); 
float FindKilometers(float dist[][N], int i_origin, int i_destination);
//OPTIONAL FUNCTIONS
void PrintCapitalsMatrix(char cities[][M]);
void PrintKilometersMatrix(char cities[][M], float dist[][N]);
int ShowMenu(void);
void CalculateDistances(char cities[][M], float dist[][N]);
int FindCity(char cities[][M], char label[20]);

int main(void){
  float kilometers[N][N];
  char capitals[N][M];
  int opt;

  LoadNames(capitals);
  LoadDistances(capitals, kilometers);

  do{
    opt = ShowMenu();
    switch(opt){
      case 1:
        PrintCapitalsMatrix(capitals);
	break;
      case 2:
        PrintKilometersMatrix(capitals, kilometers);
	break;
      case 3:
        CalculateDistances(capitals, kilometers);
	break;
      case 4:
	printf("\nGoodbye!\n");
	break;
      default:
	printf("\nERROR: Invalid option");
    }
  }while(opt != 4);
  return 0;
}

/*
 * Fill the distances matrix. As it's a symmetric matrix (matrix is equals to its transposed), 
 * we just have to fill the upper part of the matrix.
 * INPUT: Cities and distances matrixes are passed by reference.
 * OUTPUT: None.
 */
void LoadDistances(char cities[][M], float dist[][N]){
  int i;
  int j;
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if(i == j){ //Same cities distance must be 0.
        dist[i][j] = 0;
      }
      else if(j > i){ //Using this condition, we will fill the upper part of the matrix.
	do{
	  printf("\nIntroduce distance between %s and %s: ", cities[i], cities[j]);
	  scanf("%f", &dist[i][j]);
	  if(dist[i][j] <= 0){
	    printf("\nERROR: Invalid distance.");
	  }
	}while(dist[i][j] <= 0);
	dist[j][i] = dist[i][j]; //We fill the lower part of the matrix.
      }
    }
  }
  return;
}

/*
 * Init cities names.
 * INPUT: Cities matrix is passed by reference.
 * OUTPUT: None.
 */
void LoadNames(char cities[][M]){
  int i;
  for(i = 0; i < N; i++){
    printf("\nIntroduce city name %d: ", i + 1);
    //gets(cities[i]); 
    scanf(" %[^\n]", cities[i]); //Another way to simulate 'gets'
    //Because scanf("%s", cities[i]) just read one word (skip when space is found)
  }
  return;
}

/*
 * Show capitals matrix content.
 * INPUT: Cities matrix is passed by reference.
 * OUTPUT: None.
 */
void PrintCapitalsMatrix(char cities[][M]){
  int i;
  printf("\nCapitals matrix:\n");
  for(i = 0; i < N; i++){
    //puts(cities[i]);
    printf("%s\n", cities[i]); //Another way to simulate 'puts'
  }
  return;
}

/*
 * Show kilometers matrix content.
 * INPUT: Kilometers matrix and cities are passed by reference.
 * OUTPUT: None.
 */
void PrintKilometersMatrix(char cities[][M], float dist[][N]){
  int i;
  int j;
  printf("\n");
  for(i = 0; i < N; i++){
    printf("\t%s", cities[i]);
  }

  for(i = 0; i < N; i++){
    printf("\n%s\t",cities[i]);
    for(j = 0; j < N; j++){
      printf("%.2f\t", dist[i][j]);
    }
  }
  printf("\n");
  return;
}

/*
 * Show menu
 * INPUT: None.
 * OUTPUT: Menu option.
 */
int ShowMenu(void){
  int option;
  printf("\n\nMENU");
  printf("\n1.- Show cities");
  printf("\n2.- Show distances");
  printf("\n3.- Calculate distances");
  printf("\n4.- Exit");
  printf("\nEnter option: ");
  scanf("%d", &option);
  return option;
}

/*
 * Ask the user to enter a city. If it's not found, try again.
 * INPUT: Cities matrix is passed by reference. The label is used to display different messages
 * one message for asking the origin and another for the destination.
 * OUTPUT: City index according to the cities matrix.
 */
int FindCity(char cities[][M], char label[20]){
  char city[M];
  int index;
  do{
    printf("\nEnter %s city: ", label);
    scanf(" %[^\n]", city);
    index = Validate(city, cities);
    if(index == -1){
      printf("\nERROR: City not found.");
    }
  }while(index == -1);
  return index;
}

/*
 * Ask the user for an origin and destination and calculate the distance.
 * INPUT: Cities and distances matrixes are passed by reference.
 * OUTPUT: None.
 */
void CalculateDistances(char cities[][M], float dist[][N]){
  char city[M];
  int origin = FindCity(cities, "origin");
  int destination = FindCity(cities, "destination");
  float distance = FindKilometers(dist, origin, destination);
  char origin_str[M];
  char destination_str[M];
  //We can't do origin_str = cities[origin]; instead of that we have to use the function
  //strcpy(str1, str2) to copy the content of str2 into str1.
  strcpy(origin_str, cities[origin]);
  strcpy(destination_str, cities[destination]);
  printf("\nDistance between %s and %s is %.2f km", origin_str, destination_str, distance);
  return;
}

/*
 * Find the city index according to the cities matrix. 
 * We use the function strcmp(string1, string2) using "string.h" library. 
 * INPUT: City name and cities matrix are passed by reference.
 * OUTPUT: Returns -1 if it's not found, otherwise, returns the index.
 */
int Validate(char name[], char cities[][M]){
  int i;
  int found = -1;
  for(i = 0; i < N && name != cities[i]; i++){
    if(strcmp(name, cities[i]) == 0){ //Strings are equal 
      found = i;
    }
  }
  return found;
}

/*
 * Find cities distance.
 * INPUT: Distances matrix and origin/destination indexes.
 * OUTPUT: Distance.
 */
float FindKilometers(float dist[][N], int i_origin, int i_destination){
  return dist[i_origin][i_destination];
}
