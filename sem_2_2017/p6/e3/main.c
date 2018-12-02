/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * 
 * Write a program for the management of a bank clients accounts. 
 * Each client is identified by a code number (int). 
 * All the clients codes are stored into a vector of integers, codes (maximum size 100).
 * Similarly, the clients balances are stored into another 
 * vector, balances, real numbers, maximum size 100.
 *
 * The main program will read the number of clients and then will 
 * call the function Read_Data() to read and store the information of the 
 * codes vector and the balances vector. All the data should be validated.
 *
 * Then, the main program will display a menu:
 * a) Operation: To deposit or take out money
 * b) Search clients
 * c) Display information stored in codes and balances vectors
 * d) Exit
 *
 * The menu is repeatedly display until the program is exited. 
 * The following functions must be programmed:
 * 
 * • Function ReadData() to read client codes and balances and store 
 * them in the corresponding arrays. 
 * The prototype of the function is:
 * void ReadData(int codes[], float balance[], int n);
 *
 * • Function Operations(). This function displays 2 options: 
 * 1. Take out money, and 2. Deposit. 
 * In this function the client code for the operation is read from the keyboard.
 * 
 * In option 1, the amount of money to be taken out is read from the 
 * keyboard and the client’s balance is updated. 
 * A message is displayed indicating the operation, the amount taken out and the final balance.
 * Warning: it has to be checked that it is possible to take out the amount of money required.
 *
 * In option 2, the amount of money for the deposit is read from the keyboard 
 * and the client’s balance is updated (adding this amount). 
 * A message is displayed indicating the operation and the final balance.
 * 
 * The prototype of the function is:
 * void Operations(int codes[], float balances[], int n) ;
 *
 * • Function Searchclients(). This function receives both vectors and the 
 * limit amount of money. The client codes of the clients with balances over 
 * that limit will be stored into another vector, wealthy. 
 * Then the function will call another function Display_Integer_Data() 
 * to display the client codes stored in wealthy vector. 
 * The prototype of the function is: 
 * int SearchClients( int codes[], float balances[], int n, float limit, int wealthy[] ) ;
 *
 * • Function DisplayIntegerData() and DisplayRealData(). 
 * These functions will be used also in option c. 
 * They receive just one vector and the number of elements to display the values 
 * stored in it (vector codes and vector balances). 
 * The prototypes of these functions are:
 * void DisplayIntegerData(int codes[], int n);
 * void DisplayRealData(float balances[], int n);
 */

#include <stdio.h>
#include <ctype.h>

#define MAX_CUSTOMERS 100

void ReadData(int codes[], float balances[], int n);
void Operations(int codes[], float balances[], int n);
int SearchClients( int codes[], float balances[], int n, float limit, int wealthy[]);
void DisplayIntegerData(int codes[], int n);
void DisplayRealData(float balances[], int n);

//My custom functions. They're not mandatory but they're useful
int FindCode(int codes[], int code, int n);
char GetMenuOption(void);
void WithdrawMoney(int codes[], float balances[], int n, int code_index);
void DepositMoney(int codes[], float balances[], int n, int code_index);

int main(void){
  int codes[MAX_CUSTOMERS]; //Clients code
  int wealthy[MAX_CUSTOMERS]; //Wealthy clients code
  float balances[MAX_CUSTOMERS]; //Clients balance
  int n; //Num of clients
  char menu_option;
  float limit; //Limit for option 2
  int wealthy_count; //Wealthy count

  //Ask for the number of customers
  printf("\nHow many customers does the bank have?\n");
  scanf("%d", &n);

  //Fill codes and balances arrays
  ReadData(codes, balances, n);

  do{
    menu_option = GetMenuOption();
    switch(menu_option){
      case 'a':
	Operations(codes, balances, n);
	break;
      case 'b':
	printf("\nSearch customer accounts having at least an amount of money");
	do{
	  printf("\nLimit: ");
	  scanf("%f", &limit);
	  if(limit < 0){
            printf("\nError: The limit must be a positive figure");
	  }
	}while(limit < 0);
        wealthy_count =	SearchClients(codes, balances, n, limit, wealthy);
	if(wealthy_count == 0){
	  printf("\n\nThere aren't customers having at least %.2f", limit);
	}else{
	  printf("\n\nCustomer codes having more than %.2f:", limit);
          DisplayIntegerData(wealthy, wealthy_count);
	}
	break;
      case 'c':
	printf("\n\nAll codes:");
        DisplayIntegerData(codes, n);
	printf("\n\nAll balances:");
        DisplayRealData(balances, n);
	break;
      case 'd':
	printf("\nGood bye!\n");
	break;
      default:
	printf("\nError: Invalid option.");
    }
  }while(menu_option != 'd');

  return 0;
}

/**
 * Ask for customer data
 * 
 * Input: Customer codes and balances are passed by reference meanwhile n, the amout of 
 * customers is passed by value
 *
 * Output: None. But as we have passed the codes and balances by reference, we can change
 * the values of those arrays within the function.
 */
void ReadData(int codes[], float balances[], int n){
  int i;
  int code;
  int code_index;
  float balance;
  for(i = 0; i < n; i++){
    
    //Ask and validate customer codes
    do{
      printf("\nIntroduce customer %d code: ", i + 1);
      scanf("%d", &code);
      if(code < 0){
	printf("\nError: Customer code, must be greater than 0");
      }else{
        code_index = FindCode(codes, code, i);
	if(code_index != -1){
	  printf("\nError: Customer code is repeated");
	}
      }
    }while(code < 0 || code_index != -1);

    //Ask and validate balance
    do{
      printf("\nIntroduce customer %d balance: ", i + 1);
      scanf("%f", &balance);

      if(balance < 0){
        printf("\nError: Balance must be greater than 0");
      }
    }while(balance < 0);

    //Once balance & code is ok, we append it into the array
    codes[i] = code;
    balances[i] = balance;
  }
}

/**
 * Show a menu to withdraw or deposit money
 *
 * Input: Customer codes and balances are passed by reference so we can change
 * the values of the arrays within the function. Function also receives the number
 * of customers
 *
 * Output: None. We change codes and balances within the function because they're passed 
 * by reference
 */
void Operations(int codes[], float balances[], int n){
  int menu_option;
  int code_index;
  int code;
  
  do{
    printf("\nEnter customer code: ");
    scanf("%d", &code);
    code_index = FindCode(codes, code, n);
    if(code_index == -1){
      printf("\nError: Customer code not found");
    }
  }while(code_index == -1);

  printf("\nCustomer %d balance: %.2f", codes[code_index], balances[code_index]);
  do{
    printf("\n\nOperations menu:");
    printf("\n1) Withdraw money.");
    printf("\n2) Deposit money.");
    printf("\nEnter option: ");
    scanf("%d", &menu_option);

    switch(menu_option){
      case 1:
	WithdrawMoney(codes, balances, n, code_index);
	break;
      case 2:
	DepositMoney(codes, balances, n, code_index);
	break;
      default:
	printf("\nError: Invalid option");
    }
  }while(menu_option != 1 && menu_option != 2);
  printf("\nCustomer %d balance updated: %.2f", codes[code_index], balances[code_index]);
}

/*
 * Search clients that have more than a specific amount of money
 *
 * Input: The customer codes, balances and wealthy arrays are passed by reference. 
 * The number of customers and limit are passed by value
 *
 * Output: The number of customers which balance are above the limit 
 */
int SearchClients(int codes[], float balances[], int n, float limit, int wealthy[]){
  int i;
  int wealthy_count = 0;
  for(i =0; i < n; i++){
    if(balances[i] >= limit){
      wealthy[wealthy_count] = codes[i];
      wealthy_count++;
    }
  }
  return wealthy_count;
}

/**
 * Function to print all codes
 *
 * Input: Customer codes are passed by reference meanwhile the number of customers
 * is passed by value
 *
 * Output: None.
 */
void DisplayIntegerData(int codes[], int n){
  int i;
  for(i = 0; i < n; i++){
    printf("\n%d", codes[i]);
  }
}

/**
 * Function to print all balances
 *
 * Input: Customer balances are passed by reference meanwhile the number of customers
 * is passed by value
 *
 * Output: None.
 */
void DisplayRealData(float balances[], int n){
  int i;
  for(i = 0; i < n; i++){
    printf("\n%.2f", balances[i]);
  }
}

/* MY CUSTOM FUNCTIONS, VERY USEFUL BUT NOT MANDATORY */

/**
 * Find a customer code index
 *
 * Input: Customer codes is passed by reference. The code to search and the amount of 
 * customers is passed by value.
 *
 * Output: Returns -1 if it's not found, otherwise, returns the index
 */
int FindCode(int codes[], int code, int n){
  int code_found = -1;
  int i; //Loop counter

  //This "for" loop check that our counter "i" is less than the ammount of customers
  //and also if the code is found to avoid useless 
  for(i = 0; i < n && code_found == -1; i++){
    if(code == codes[i]){
      code_found = i;
    }
  }
  return code_found;
}

/**
 * Draw a menu and get menu option
 *
 * Input: None
 * Output: Menu option (as lowercase char)
 */
char GetMenuOption(void){
  char option;
  printf("\n\nMenu:");
  printf("\na) Operation: To deposit or take out money.");
  printf("\nb) Search clients.");
  printf("\nc) Display information stored in codes and balances vectors.");
  printf("\nd) Exit.");
  printf("\nEnter option: ");
  scanf(" %c", &option);
  option = tolower(option);
  return option;
}

/*
 * Withdraw money from customer
 *
 * Input: Customer codes and balances are passed by reference, the number of customers
 * and the customer code index are passed by value
 *
 * Output: None. Customer codes and balances are change within the function because 
 * they're passed by reference
 */
void WithdrawMoney(int codes[], float balances[], int n, int code_index){
  float amount;
  float balance = balances[code_index];
  do{
    printf("\nHow much money you want to withdraw? ");
    scanf("%f", &amount);
    if(amount > balance){
      printf("\nError: You can't withdraw so much money. Limit is %.2f.", balance);
    }else if(amount < 0){
      printf("\nError: You can't withdraw a negative figure.");
    }else{
      balances[code_index] -= amount;
    }
  }while(amount > balance || amount < 0);
}

/*
 * Deposit money for customer
 *
 * Input: Customer codes and balances are passed by reference, the number of customers
 * and the customer code index are passed by value
 *
 * Output: None. Customer codes and balances are change within the function because 
 * they're passed by reference
 */
void DepositMoney(int codes[], float balances[], int n, int code_index){
  float amount;
  do{
    printf("\nHow much money you want to deposit? ");
    scanf("%f", &amount);
    if(amount < 0){
      printf("\nError: You can't deposit a negative figure.");
    }else{
      balances[code_index] += amount;
    }
  }while (amount < 0);
}
