/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a program that defines a constant integer number called SECRET 
 * by using #define .
 * Then write a loop that allows the user to play against the computer 
 * to guess that secret number. The loop must:
 * Request a number
 * Compare the number introduced by the uset with the constant SECRET
 * Indicate if the user has guessed the secret number of if the 
 * SECRET number is smaller/larger.
 * 
 * The loop will be repeated until the user guesses the number.
 */

#include <stdio.h>

#define SECRET 456

int main(void){
	//Define variables
	int user_secret; //Number to check if it's the secret
	int i = 0; //Loop counter
	
	//Ask user for input till is the secret
	do{
		printf("\nIntroduce the password:");
		scanf("%d", &user_secret);

		if(user_secret < SECRET){
			printf("Wrong: Password is greater than %d", user_secret);
		}else if(user_secret > SECRET){
			printf("Wrong: Password is less than %d", user_secret);
		}
		//Increase number of tries
		i++;
	}while(user_secret != SECRET);
	printf("Correct: Password found after %d tries\n", i);
	return 0;
}
