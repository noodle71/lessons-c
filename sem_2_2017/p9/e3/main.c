/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION:
 * Write a program to copy prime numbers from a vector v1 to another vector v2. 
 * The program should follow the steps:
 * 
 * 1. The main program will ask to the user the number of elements in v1, 
 * and will allocate dynamic memory to the vector of integers v1. 
 * Then v1 is initialised reading the numbers from the keyboard, by means of 
 * the function ReadVec()
 *
 * 2. Then, the program will call the function CountPrime(), to count 
 * the number of prime numbers in the initial vector. This number is given 
 * back by reference
 *
 * 3. The program will allocate dynamic memory to the vector of integers 
 * v2 (that later will store the prime numbers)
 *
 * 4. The main program will call the function CopyPrime(). This function copies 
 * prime numbers from v1 to v2
 *
 * 5. Call the function Display() to display the resulting vector
 *
 * 6. Release memory. (Watch out: usually this step is not indicated to the student. 
 * The student should remember it is always necessary to release memory at the end)
 *
 */
#include <stdio.h>
#include <stdlib.h>

//MANDATORY FUNCTIONS
void ReadVec(int *pvector, int num_elem);
void CountPrime(int *pvector, int num_elem, int *pnum_primes);
void CopyPrimes(int *pvector, int num_elem, int *pprimes, int num_primes);
void Display(int *pvector, int num_elem);

//OPTIONAL FUNCTION
int IsPrime(int num);

int main(void){
  int *pnums;
  int *pprim;
  int size = 0;
  int primes_size = 0;
  do{
    printf("\nHow many numbers do you want to check if they are prime? ");
    scanf("%d", &size);
    if(size <= 0){
      printf("\nERROR. The number of elements must be greater than 0.");
    }
  }while(size <= 0);

  pnums = (int *) calloc(size, sizeof(int));
  if(pnums != NULL){
    ReadVec(pnums, size);
    CountPrime(pnums, size, &primes_size);
    pprim = (int *) calloc(primes_size, sizeof(int));
    if(pprim != NULL){
      CopyPrimes(pnums, size, pprim, primes_size);
      printf("\nGet primes from vector:\n");
      Display(pnums, size);
      printf("\nPrimes:\n");
      Display(pprim, primes_size);
      free(pnums);
      free(pprim);
      printf("\n");
    } else {
      printf("\nERROR: Not enought memory.\n");
    }
  } else {
    printf("\nERROR: Not enought memory.\n");
  }
  return 0;
}

/*
 * Fill a vector with numbers.
 * INPUT: Vector (passed by reference, it's the same as a pointer) and the number 
 * of elements to be stored.
 * OUTPUT: None.
 */
void ReadVec(int *pvector, int num_elem){
  int i;
  for(i = 0; i < num_elem; i++){
    do{
      printf("\nEnter the number #%d: ", i + 1);
      scanf("%d", &pvector[i]);
      if(pvector[i] <= 0){
	printf("\nERROR: Number must be greater than 0.");
      }
    }while(pvector[i] <= 0);
  }
  return;
}

/*
 * Count the number of primes within a vector of integers.
 * INPUT: Vector of integers (passed by reference, it's the same as a pointer), the number
 * of elements and the variable (pointer) to store the number of primes.
 * OUTPUT: None.
 */ 
void CountPrime(int *pvector, int num_elem, int *pnum_primes){
  int i;
  int num;
  for(i = 0; i < num_elem; i++){
    num = *(pvector + i);
    if(IsPrime(num) != 0){
      (*pnum_primes)++;
    }
  }
  return;
}

/*
 * Copy all primes from one vector to another.
 * INPUT: Both vectors are passed by reference (using pointers) and the size of 
 * both vectors.
 * OUTPUT: None.
 */ 
void CopyPrimes(int *pvector, int num_elem, int *pprimes, int num_primes){
  int i;
  int j = 0;
  int num;
  for(i = 0; i < num_elem; i++){
    num = *(pvector+i);
    if(IsPrime(num) != 0){
      *(pprimes + j) = *(pvector + i);
      j++;
    }
  }
  return;
}

/*
 * Print the content of a vector of integers.
 * INPUT: Vector of integers (passed by reference, ussing pointers) and the size of the vector.
 * OUTPUT: None.
 */ 
void Display(int *pvector, int num_elem){
  int i;
  for(i = 0; i < num_elem; i++){
    printf("%d\t", *(pvector + i));
  }
  return;
}


/*
 * Check if a number is prime.
 * INPUT: The number to check if it's prime.
 * OUTPUT: A integer which value is 0 if it's not prime, otherwise, 1.
 */ 
int IsPrime(int num){
  int i;
  int res = 1;

  if(num <= 1){
    res = 0;
  }else{
    for(i = 2; i < num && res != 0; i++){
      res = num % i;
    }
  }

  if(res > 1){
    res = 1;
  }

  return res;
}
