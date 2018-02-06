/*File with the print methods for filtering the letters. */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "filter.h"
#include "filter_print.h"

/*Prints total number of letters read. */
void print_total_letters(int total_letters)
{
  printf("Total number of letters read: %d\n", total_letters);
}

/*Prints the number of times each letter is read from file. */
void print_letter_occurance(int letters[ALPHABET])
{
  for(int i = 0; i < ALPHABET; i++)
    {
      printf("%c = %d\n", ('a' + i), letters[i]);
    }
}


/*Loop to print frequency of each letter over total letters. */
void print_freq(double running_frequency[ALPHABET], double frequency[ALPHABET])
{
  for(int i = 0; i < ALPHABET; i++)
    {
      printf("frequency of %c over total letters = %.2lf%%\n",
	     ('a' + i), (frequency[i] * 100));
    }
}


/*Loop to print running frequency percentages. */
void print_running(double running_frequency[ALPHABET])
{
  for(int i = 0; i < ALPHABET; i++)
    {
      printf("running frequency[%d] up to %c =  %.4lf\n", i,
	     ('a' + i), running_frequency[i]);
    }
}

/*Prints all the info to the screen. */
void print_to_screen(double running_frequency[ALPHABET], double frequency[ALPHABET],
		int letters[ALPHABET], int total_letters)
{
  print_total_letters(total_letters);
  print_letter_occurance(letters);
  print_freq(running_frequency, frequency);
  print_running(running_frequency);

  double rand_num;
  srand(time(NULL));
  for(int j = 0; j < TESTNUMBER; j++)
  {
    rand_num = (double)rand()/RAND_MAX;
    printf("%lf ", rand_num);
    for(int k = 0; k < ALPHABET; k++){
      if(rand_num >= running_frequency[k-1] && rand_num <= running_frequency[k])
      {
	printf("%c", 'a' + k);    //print random characters to console
      }
    }
    printf("\n");
  }
}

/*Prints the letters to a file with the same frequency as the file read*/
void print_to_file(double running_frequency[ALPHABET], int total_letters)
{
  double rand_num;
  char* file_name = malloc(sizeof(char) * SIZE_OF_WRITE_FILE);
  
  srand(time(NULL));
  
  printf("What file would you like to write to?\n");
  scanf("%s", file_name);
  
  FILE *fp = fopen(file_name, "w"); //setup file to write to
  if(!fp){
    perror("fp");
    exit(EXIT_FAILURE);
  }
  
  /*Loop to print out random letters using running_frequency probability*/
  for(int j = 0; j < total_letters; j++)
  {
    rand_num = (double)rand()/RAND_MAX; 
    for(int k = 0; k < ALPHABET; k++)
    {
      if(rand_num >= running_frequency[k-1] && rand_num <= running_frequency[k])
	fputc(('a' + k), fp);   //put random character into file
    }
  }
  printf("Written successfully!\n");
  
  fclose(fp);
  free(file_name);
}
