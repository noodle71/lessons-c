/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION: 
 * Write a program to read a string and copy the second word into another one. 
 * This will be executed by means of a function Transform() that will 
 * work with two strings, copying characters from string1 to string2.
 *
 * The first string string1 is declared in main as a static array of characters. 
 * On the other hand, string2 will be allocated dynamic memory and has to be declared 
 * in main as a pointer to char. 
 * The program will follow these steps:
 *
 * Read string1 by means of fgets function (safe version of gets ).
 *
 * Call a function CountWord() to the number of characters of the second word in the string1.
 * The objective is to determine the length of the second string2 (and pass this length 
 * back by reference).
 *
 * Allocate dynamic memory for string2 by means of calloc
 *
 * Call the function void Transform(char *string1, char *string2) to fill string2 as
 * specified. (Remember that this protopype is equivelent to the following ones: )
 * void Transform(char string1[], char *string2);
 * void Transform(char string1[], char string2[]);
 *
 * Display both string1 and string2
 * 
 * Release memory previously allocated for string2 .
 * 
 * Watch out: The following special cases should be considered in CountWord() and Transform():
 *
 * The original string could be empty or have just one word. In that case, the resulting 
 * string will be also empty.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100
#define A 97
#define Z 122

//MANTADORY FUNCTIONS
void CountWord(char string[], int *word_length);
void Transform(char string1[], char *string2);

//OPTIONAL FUNCTIONS
int CharIsLetter(char letter);
void IndexOfSecondWord(char string[], int *index, int *length);

int main(void){
  char string1[N];
  char *string2;
  int count = 0;

  printf("\nWrite a sentence:\n");
  fgets(string1, N, stdin);
  CountWord(string1, &count);
  string2 = (char *)calloc(count, sizeof(char));
  if(string2 != NULL){
    if(count == 0){
      printf("\nERROR: These sentence doesn't have two words.\n");
    }else{
      Transform(string1, string2); 
      printf("\nSecond word content:\n%s\n", string2);
    }
  }else{
    printf("\nERROR: Not enought memory.\n");
  }
  return 0;
}

/*
 * Count the length of the second word within a sentence.
 * INPUT: The string to look for the second word and the variable to store the length of
 * the second word (using pointers).
 * OUTPUT: None.
 */
void CountWord(char string[], int *word_length){
  int index;
  IndexOfSecondWord(string, &index, word_length);
  return;
}

/*
 * Search for a second word within a sentence. Store the length of the second word
 * using a pointer and get the index where the second word is, using another pointer.
 * INPUT: The string to look for the second word, the index and length that will be stored
 * there (using pointers).
 * OUTPUT: None.
 */
void IndexOfSecondWord(char string[], int *index, int *length){
  int previous_is_letter = 0;
  int current_is_letter;
  int word_count = 0;
  int i = 0;
  char c;
  for(i = 0; i < strlen(string); i++){
  //for(i = 0; string[i] != '\0'; i++){ //Another way to do the same
    c = string[i];
    current_is_letter = CharIsLetter(c);
    if(current_is_letter == 1 && previous_is_letter == 0){
      word_count++;
      if(word_count == 2){
        *index = i;
      }
    }
    if(word_count == 2 && current_is_letter == 1){
      //*length = *length + 1;
      (*length)++; //The same as above
    }
    previous_is_letter = current_is_letter;
  }
  return;
}

/*
 * Checks if char is a letter. If it's a letter, returns 1, otherwise, returns 0.
 * INPUT: The char.
 * OUTPUT: An integer (1 if is a letter or 0 if it's not a letter).
 */
int CharIsLetter(char letter){
  int result = 0;
  letter = tolower(letter);
  if(letter >= A && letter <= Z){
    result = 1;
  }
  return result;
}

/*
 * Store the second word within a sentence in a string.
 * INPUT: A string to get the second word from and the string to store the value.
 * OUTPUT: None.
 */
void Transform(char string1[], char *string2){
  int index = 0;
  int length = 0;
  int i;
  int j = 0;
  IndexOfSecondWord(string1, &index, &length);
  if(index > 0){
    for(i = index; j < length; i++){
      string2[j] = string1[i];
      j++;
    }
  }
  return;
}
