/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Modify previous program by including statements to validate the number introduced 
 * by the user. This number should be between 0 and 1000 (both are valid).
 * One example about a general loop structure to read variables while 
 * implementing error checking can be found at
 *
 * http://www.iit.upcomillas.es/libroc/ , section of "Códigos de uso frecuente".
 */

#include <stdio.h>

#define SECRET 456

int main(void){
	//Define variables
	int user_secret; //Number to check if it's the secret
	int i = 0; //Loop counter
	
	//Ask user for input till is the secret
	do{
		do{
			printf("\nIntroduce the password:");
			scanf("%d", &user_secret);
			if(user_secret < 0 || user_secret > 1000){
				printf("Invalid password");
			}
			//Increase tries counter
			i++;
		}while(user_secret < 0 || user_secret > 1000);

		if(user_secret < SECRET){
			printf("Wrong: Password is greater than %d", user_secret);
		}else if(user_secret > SECRET){
			printf("Wrong: Password is less than %d", user_secret);
		}

	}while(user_secret != SECRET);
	printf("Correct: Password found after %d tries\n", i);
	return 0;
}
