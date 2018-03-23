/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * Write a program that creates a file ( temperatures.txt ) to register all the 
 * temperatures measured in a month. In a loop, each temperature will be 
 * read: for each measure, the user will enter from the keyboard the number of the 
 * day and the corresponding temperature, and both numbers will be written in the file. 
 * Do not use a vector to store this information, just the variables day (integer) 
 * and temp (double).
 * After the program is executed, each measure will be in a different line 
 * of the file. Example:
 * 
 * 1 23.52
 * 2 23.43
 * 3 23.01
 * 4 22.50
 * ... ...
 * Proposed solution:
 * The program begins by defining a pointer fpt, indicating the beginning of 
 * the data-file buffer area. A new data file, called temperatures.txt, is then open 
 * for writing only. Next, a loop reads days and temperatures from the keyboard and 
 * writes them to the data file: fprintf(ftp,“%d %f\n”, day, temp); 
 * Note: The data file can also be examined using a 
 * text editor or a word processor (i.e., WordPad , Notebook, CodeLite) ).
 */
#include<stdio.h>

int main(void){
  int i;
  FILE *pf;
  int days;
  float temp;
  int write_check;

  do{
    printf("\nEnter the number of days: ");
    scanf("%d", &days);
    if(days <= 0){
      printf("\nERROR: Number must be greater than 0.");
    }
  }while(days <= 0);

  pf = fopen("temperatures.txt", "w");
  if(pf == NULL){
    printf("\nERROR: Can't open file.");
  }else{
    for(i = 0; i < days; i++){
      printf("\nEnter temperature for day %d: ", i + 1);
      scanf("%f", &temp);
      write_check = fprintf(pf, "%d\t%.2f\n", i + 1, temp);
      if(write_check == EOF){
        i--;
	printf("\nERROR: Can't write content in the file.");
      }
    }
    fclose(pf);
  }
  printf("\n");
  return 0;
}
