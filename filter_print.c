#include "filter.h"
#include "filter_print.h"

/*Prints total number of letters read*/
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


/*Loop to print frequency of each letter over total letters, also adds the  *
 *frequencies together to get a running frequency.                          */
void print_freq(double running_frequency[ALPHABET], double frequency[ALPHABET])
{
  for(int i = 0; i < ALPHABET; i++)
    {
      printf("frequency of %c over total letters = %.2lf%%\n",
	     ('a' + i), (frequency[i] * 100));
    }
}


/*Loop to print running frequency percentages*/
void print_running(double running_frequency[ALPHABET])
{
  for(int m = 0; m < ALPHABET; m++)
    {
      printf("running frequency[%d] up to %c =  %.4lf\n",m ,
	     ('a' + m) ,running_frequency[m]);
    }
}

/*Wrapping all the print functions into on print heap*/
void print_info(double running_frequency[ALPHABET], double frequency[ALPHABET],
		int letters[ALPHABET], int total_letters)
{
  print_total_letters(total_letters);
  print_letter_occurance(letters);
  print_freq(running_frequency, frequency);
  print_running(running_frequency);
}
