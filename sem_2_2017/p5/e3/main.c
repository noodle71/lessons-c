/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write an iterative function Prime() to determine if the received 
 * integer number is prime or not. The function will return a 1 if the number 
 * is prime, and a 0 if the number is not prime.
 * Write a program to display all the prime numbers between 
 * an initial integer number and a final integer number,
 * given by the user. The program will call the function Prime().
 */

#include <stdio.h>

//Function prototypes
int Prime(int num);

int main(void){
  int init; //First value of range to calculate primes
  int end; //Last value of range to calculate primes
  int i;
  int is_prime;
  do{
    printf("\nEnter the first number of range to calculate primes: ");
    scanf("%d", &init);
    printf("\nEnter the last number of range to calculate primes: ");
    scanf("%d", &end);

  }while(init > end);
  printf("\nPrime numbers between %d and %d:\n", init, end);
  for(i = init; i <= end; i++){
    is_prime = Prime(i);
    if(is_prime == 1){
      printf("%d\n", i);
    }
  }
  return 0;
}

/**
 * Checks if a number is prime.
 * Input: Number to check if it's prime
 * Output: Returns 0 if number is not prime. Return 1 if it's prime.
 */
int Prime(int num){
  int res = 0;
  int remainder = 1;
  int i;
  for(i = 2; i < num && remainder != 0; i++){
    remainder = num % i;
  }
  if(num == 0 || num == 1 || remainder != 0){
    res = 1;
  }

  return res;
}
