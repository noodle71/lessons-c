/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 19/02/18
 * DESCRIPTION: 
 * Write a program to declare two strings ( string1 and string2 ), 
 * read the first string from the keyboard, and create the second string 
 * by extracting from string1 the first letter of each word.
 * Example: if string1 is “ United Nations ” then string2 should be “ UN ”.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 100
#define A 97
#define Z 122

void CreateAcronym(char str[N], char acronym[N]);
int CharIsLetter(char letter);

int main(void){
  char string1[N];
  char string2[N];

  printf("\nEnter string:\n");
  //gets(string1);
  scanf(" %[^\n]", string1); //This is like gets
  CreateAcronym(string1, string2);
  printf("\nAcronym:\n%s\n", string2);
  return 0;
}

/*
 * Create an acronym given a string.
 * INPUT: Two string variables (passed by reference) one contains the text
 * and the other should countain the acronym.
 * OUTPUT: None.
 */
void CreateAcronym(char str[N], char acronym[N]){
  int len = strlen(str);
  int i;
  int counter = 0;
  char c;
  int current_char_is_letter = 0;
  int previous_char_is_letter = 0;
  //for(i = 0; i < N && str[i] != '\0'; i++){ //Another way to iterate the String
  for(i = 0; i < N && i < len; i++){
    c = str[i];
    current_char_is_letter = CharIsLetter(c);
    if(current_char_is_letter == 1 && previous_char_is_letter == 0){
      acronym[counter] = toupper(c);
      counter ++;
    }
    previous_char_is_letter = current_char_is_letter;
  }
  //Set the end of the string
  acronym[counter] = '\0';
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
