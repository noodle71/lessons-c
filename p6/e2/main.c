/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a program to read a sentence with gets 
 * (the maximum size of this string should be 100, char sentence[100]) and calculate:
 * • Number of words in the sentence
 * • Number of letters (uppercase or lowercase)
 * • Number of vowels (uppercase or lowercase)
 *
 * Important note: We can expect that a blank space separates every two words.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int IsVowel(char letter);
int IsLetter(char letter);
int IsSpace(char letter);

int main(void){
  char sentence[100];
  char letter;
  int i;
  int is_space;
  int is_letter;
  int is_vowel;
  int vowel_counter = 0;
  int letter_counter = 0;
  int word_counter = 0;
  printf("Introduce a sentence:\n");
  gets(sentence);
  printf("Analizing he sentence: %s\n", sentence);
  //for(i = 0; sentence[i] != '\0'; i++){ //OTRA FORMA DE RECORRER EL BUCLE
  for(i = 0; i <= strlen(sentence); i++){
    letter = tolower(sentence[i]);
    
    is_space = IsSpace(letter);
    is_vowel = IsVowel(letter);
    is_letter = IsLetter(letter);
    vowel_counter += is_vowel;
    letter_counter += is_letter;
    word_counter += is_space;
  }
  printf("\nHas %d words, containing %d letters of which %d are vowels.\n", word_counter, letter_counter, vowel_counter);
  return 0;
}

int IsVowel(char letter){
  int is_vowel = 0;
  if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u'){
    is_vowel = 1;
  }
  return is_vowel;
}

int IsLetter(char letter){
  int is_letter = 0;
  if(letter >= 97 && letter <= 122){
    is_letter = 1;
  }
  return is_letter;
}

int IsSpace(char letter){
  int is_space = 0;
  if(letter == ' ' || letter == '\0'){
    is_space = 1;
  }
  return is_space;
}
