/*
 * AUTHOR: Angel Fernández Camba
 * DATE: Long time ago...
 * DESCRIPTION: Write a program that creates a file ( library.dat ) 
 * to store all the information about the books in a library. For each book, 
 * the information that must be stored is the following (use a structure called T_BOOK):
 *
 * Book title
 * Author
 * Date of purchase (structure type T_DATE containing three fields: day, month, year)
 * The program begins by requesting the number of books in the library, 
 * then it will ask the user the information related with all the books in the 
 * library, in order to write such information in the file. It is not necessary 
 * to store the information of the books in arrays. A function called ReadOneBook() must 
 * be used to read from the keyboard the information of each book (call this function 
 * inside a loop in main()). 
 *
 * Once a book has been read, it will be stored in the binary file. The prototype 
 * of the function ReadOneBook() is:
 * T_BOOK ReadOneBook(void);
 * Note: Write another version of the function ReadoneBook() using pointers to 
 * give back the structure.
 */
#include<stdio.h>
#define M 100

typedef struct{
  int day;
  int month;
  int year;
}T_DATE;

typedef struct{
  char name[M];
  char author[M];
  T_DATE date_purchase;
}T_BOOK;

T_BOOK ReadOneBook(void);
void ReadByReference(T_BOOK *book);

int main(void){
  int n;
  T_BOOK book;
  FILE *f_books;
  f_books = fopen("books.dat", "wb");
  if(f_books != NULL){
    do{
      printf("\nHow many books do you have? ");
      scanf("%d", &n);
      if(n <= 0){
        printf("\nERROR: Must be greater than 0.");
      }
    }while(n <= 0);

    while(n-- > 0){
      //book = ReadOneBook();
      ReadByReference(&book);
      fwrite(&book, sizeof(T_BOOK), 1, f_books);
    }
    fclose(f_books);
  }
  return 0;
}

/*
 * Read a book.
 * INPUT: None.
 * OUTPUT: Book.
 */ 
T_BOOK ReadOneBook(void){
  T_BOOK b;
  printf("\nPurchase day (dd/mm/yyyy): ");
  scanf("%d/%d/%d", &b.date_purchase.day, &b.date_purchase.month, &b.date_purchase.year);
  getchar();
  printf("Name: ");
  fgets(b.name, M, stdin);
  printf("Author: ");
  fgets(b.author, M, stdin);
  return b;
}

/*
 * Read a book by reference.
 * INPUT: Book pointer.
 * OUTPUT: None.
 */ 
void ReadByReference(T_BOOK *b){
  printf("\nPurchase day (dd/mm/yyyy): ");
  scanf("%d/%d/%d", &b->date_purchase.day, &b->date_purchase.month, &b->date_purchase.year);
  getchar();
  printf("Name: ");
  fgets(b->name, M, stdin);
  printf("Author: ");
  fgets(b->author, M, stdin);
  return;
}
