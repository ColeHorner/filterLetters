#include "filter.h"
#include "filter_calc.h"

/*Calculates the frequency of letter over the total number of letters in the file. */
void calc_freq(int total_letters, int letters[ALPHABET], double frequency[ALPHABET])
{
  for(int i = 0; i < ALPHABET; i++)
    {
      frequency[i] = (((double)letters[i])/total_letters);
    }
}

/*Loop to calculate the running frequency of the leters. */
void calc_running(double running_frequency[ALPHABET], double frequency[ALPHABET])
{
  for(int i = 0; i < ALPHABET; i++)
    {
      if(i > 0)
	running_frequency[i] = frequency[i] + running_frequency[i-1];
      else
	running_frequency[i] = frequency[i];
    }
}

/*Does all calculations necessary for probability. */
void calc_all(int total_letters, int letters[ALPHABET],
	      double running_frequency[ALPHABET], double frequency[ALPHABET])
{
  calc_freq(total_letters, letters, frequency);
  calc_running(running_frequency, frequency);
}
