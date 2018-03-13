/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 *
 * DO NOT ALLOCATE MEMORY
 *
 * Write a program that, given a vector of product codes (initialized reading 
 * them from the keyboard. It can be assumed that the user inserts them 
 * in increasing order), displays the following menu:
 *
 * Remove: Look for a product code typed in by the user, and remove it 
 * from the vector.
 * A function Remove() has to be implemented. Then, the main program will 
 * display the resulting vector.
 *
 * Insert: Insert a product code specified by the user in the correct location of 
 * the vector (it has to be sorted in increasing order). Use a function 
 * Insert().Then, the main program will display the resulting vector.
 *
 * Exit
 */

#include <stdio.h>
#define MAX 100

//MANDATORY FUNCTIONS
void Remove(int codes[], int code, int *num_codes);
void Insert(int codes[], int code, int *num_codes);

//OPTIONAL FUNCTIONSX
int FindCode(int codes[], int code, int num_codes);
void FillCodes(int codes[], int num_codes);
int AskCodesSize(void);
void ShowMenu(int *option);
void HandleMenuOption(int codes[], int *num_codes, int option);
void AskForCode(int codes[], int *code, int num_codes, int error_value, char error_msg[]);
void ShowCodes(int codes[], int num_codes);
int IndexOfCode(int codes[], int code, int num_codes);

int main(void){
  int size = AskCodesSize();
  int codes[MAX];
  int option;
  FillCodes(codes, size);
  do{
    ShowMenu(&option);
    HandleMenuOption(codes, &size, option);
  }while(option != 4);
  return 0;
}

/*
 * Insert a code within the array of codes.
 * INPUT: The array of codes, the code and the number of codes.
 * OUTPUT: None.
 */
void Insert(int codes[], int code, int *num_codes){
  codes[*num_codes] = code;
  (*num_codes)++;
  return;
}

/*
 * Remove a code within the array of codes.
 * INPUT: The array of codes, the code and the number of codes.
 * OUTPUT: None.
 */
void Remove(int codes[], int code, int *num_codes){
  int i;
  int index = IndexOfCode(codes, code, *num_codes);
  for(i = index; i < *num_codes - 1; i++){
    codes[i] = codes[i + 1];
  }
  (*num_codes)--;
  return;
}

/*
 * Fill the codes array.
 * INPUT: The array of codes and the total number of codes.
 * OUTPUT: None.
 */
void FillCodes(int codes[], int num_codes){
  int i;
  int found;
  for(i = 0; i < num_codes; i++){
    do{
      printf("\nEnter code %d: ", i + 1);
      scanf("%d", &codes[i]);
      found = FindCode(codes, codes[i], i);
      if(found == 1){
	printf("\nERROR: Code already present, please, enter a new one.");
      }else if(codes[i] <= 0){
        printf("\nERROR: Code must be greater than 0.");
      }
    }while(found == 1 || codes[i] <= 0);
  }
  return;
}

/*
 * Look for the code within the array of codes.
 * INPUT: The codes array, the code to search and the total number of codes.
 * OUTPUT: Returns an integer, 1 if it's found, otherwise 0,
 */
int FindCode(int codes[], int code, int num_codes){
  int found = IndexOfCode(codes, code, num_codes);
  if(found < 0){
    return 0;
  }else{
    return 1;
  }
}

/*
 * Look for the code index within the array of codes.
 * INPUT: The codes array, the code to search and the total number of codes.
 * OUTPUT: Returns the index of the code within the array if it's found, otherwise, returns -1,
 */
int IndexOfCode(int codes[], int code, int num_codes){
  int i;
  int found = -1;
  for(i = 0; i < num_codes && found == -1; i++){
    if(code == codes[i]){
      found = i;
    }
  }
  return found;
}

/*
 * Ask the number of codes to the user.
 * INPUT: None.
 * OUTPUT: The number of codes as integer.
 */ 
int AskCodesSize(void){
  int size;
  do{
    printf("\nEnter the number of codes you want to insert: ");
    scanf("%d", &size);
    if(size <= 0){
      printf("\nERROR: The number of codes should be greater than 0.");
    }
  }while(size <= 0);
  return size;
}

/*
 * Show menu to insert and remove codes.
 * INPUT: The option varable where the option menu is stored (using pointers).
 * OUTPUT: None.
 */
void ShowMenu(int *option){
  
  printf("\nEnter option");
  printf("\n1 - Insert code");
  printf("\n2 - Remove code");
  printf("\n3 - Show all codes");
  printf("\n4 - Exit\n");
  printf("\nOption: ");
  scanf("%d", option);
  return;
}

/*
 * Handle the menu option.
 * INPUT: Codes array, the total number of codes and the menu option.
 * OUTPUT: None.
 */
void HandleMenuOption(int codes[], int *num_codes, int option){
  int code;
  int found = 0;
  
  switch(option){
    case 1:
      AskForCode(codes, &code, *num_codes, 1, "Code exists");
      Insert(codes, code, num_codes);
      break;
    case 2:
      if(*num_codes <= 0){
        printf("\nERROR: There aren't codes to remove.");
      }else{
        AskForCode(codes, &code, *num_codes, 0, "Code doesn't exist");
        Remove(codes, code, num_codes);
      }
      break;
    case 3:
      ShowCodes(codes, *num_codes);
      break;
    case 4:
      printf("\nGoodbye!\n");
      break;
    default:
      printf("\nERROR: Invalid menu option.");
      break;
  }
  return;
}

/*
 * Ask for the code to insert or delete and returns if it's found.
 * INPUT: The codes array, the code variable to store the value, the total of codes, 
 * the error value to compare and the error message when the error value is found.
 * OUTPUT: None.
 */ 
void AskForCode(int codes[], int *code, int num_codes, int error_value, char error_msg[]){
  int found;
  do{
    printf("\nEnter the code: ");
    scanf("%d", code);
    found = FindCode(codes, *code, num_codes);
    if(found == error_value){
      printf("\nERROR: %s", error_msg);
    }
  }while(found == error_value);
  return;
}

/*
 * Show all the codes.
 * INPUT: Codes array and the total amount of codes.
 * OUTPUT: None.
 */
void ShowCodes(int codes[], int num_codes){
  int i;
  printf("\n");
  if(num_codes <= 0){
    printf("No codes to show");
  }
  for(i = 0; i < num_codes; i++){
    printf("%d\t", codes[i]);
  }
  printf("\n");
  return;
}
