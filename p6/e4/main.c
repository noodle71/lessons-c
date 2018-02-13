/*
 * AUTHOR: Angel Fernández Camba
 * DATE: 16/01/18
 * DESCRIPTION:
 * Write a program to read a string and encode it by means of a function Rot13(). 
 * This function adds 13 to any character received (if it is a letter). 
 * If the result is greater than ‘z’, it continues with the letter ‘a’
 * (thus, it is a rotate function). 
 * If this old procedure is applied to an encoded text, the original text is obtained. 
 * The prototype of the function is: 
 * void Rot13(char str[], char str_en[]);
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 100
#define A_CODE 97
#define Z_CODE 122

void Rot13(char str[], char str_en[]);

int main(void){
  char str[MAX_LEN];
  char str_en[MAX_LEN];

  printf("\nEncode text:\n");
  gets(str);

  Rot13(str, str_en);
  printf("\nText encoded:\n");
  puts(str_en);

  Rot13(str_en, str);
  printf("\nDecode encoded text:\n");
  puts(str);

  return 0;
}


void Rot13(char str[], char str_en[]){
  int i;
  int len;
  char letter;
  int letter_code;
  char letter_rot13;
  int num_letters = Z_CODE - A_CODE + 1;
  len = strlen(str);
  for(i = 0; i < len; i++){
    //Let's work with lowercase letters
    letter = tolower(str[i]);
    if(letter >= A_CODE && letter <= Z_CODE){
      //Get letter as integer    
      letter_code = str[i];
      //Normalize letter_code according to alphabet. 
      //If our letter is 'b' then, the code would be '1' 
      //Because 'a' = 97, 'b' = 98, ... 'z' = 122
      //So, 98 - 97 = 1; 
      //(Remember we start counting by 0, so 'b' would be the second letter)
      letter_code = letter_code - A_CODE;
      //Apply rot13 to letter
      letter_code = letter_code + 13;
      //Normalize again because if we sum 13 to the letter, 
      //letter code could be greater than 122 ('z' = 122) 
      //and that could turn the letter into a sign
      letter_code = letter_code % num_letters;
      //Denormalize the letter. We turn the alphabet code into ASCII code
      //https://www.cs.cmu.edu/~pattis/15-1XX/common/handouts/ascii.html
      letter_code += A_CODE;
      //Cast our letter code to char
      letter_rot13 = letter_code;

      str_en[i] = letter_rot13;
    }else{
      str_en[i] = str[i];
    }
  }
}
