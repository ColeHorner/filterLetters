/*Program that runs statistics and probabilities on the frequencies of letters *
 *in a book that is in a text file.                                            */

#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "filter.h"
#include "filter_print.h"
#include "filter_calc.h"

int main(int argc, char** argv)
{
  char *line = NULL;                        //storing line from getline
  int total_letters = 0;                    //Storing total number of letters
  size_t lengthOfBuffer = 0;                //buffer for getline
  ssize_t numberOfCharactersRead;           //Number of characters read from getline
  int letters[ALPHABET] = {0};              //Array to store frequency of letters
  double frequency[ALPHABET] = {0};         //Array to store frequency percentage
  double running_frequency[ALPHABET] = {0}; //Array to store running frequency

  if(argc != 2){
    printf("Please enter file.\n");
    exit(1);
  }
  
  FILE *inputStream = fopen(argv[1], "r"); //opening file

  /*Reading first line of file*/
  numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);
  
  if(numberOfCharactersRead == -1)
  {
    perror("getline");
  }
  else
  {
    for(int i = 0; i < lengthOfBuffer; i++)
    {
      line[i] = tolower(line[i]);           //makes all letters lowercase
      if(line[i] >= 'a' && line[i] <= 'z')
      {
	letters[line[i] - 'a']++;           //counts letter freq and stores in array
	total_letters++;
      }
    }
  }
  /*Reading rest of file, this and previous code can probably be combined into a *
   *function to make better code.                                                */
  while( numberOfCharactersRead > 0 )
  {
    numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);
    if( numberOfCharactersRead == -1 )
    {
      perror( "getline" );
    }
    else
    {
      for(int i = 0; i < lengthOfBuffer; i++)
      {
	line[i] = tolower(line[i]);
	if(line[i] >= 'a' && line[i] <= 'z')
        {
	  letters[line[i] - 'a']++;
	  total_letters++;
	}
      }
    }
  }
  
  fclose(inputStream);  //Close file
  free(line);           //Free buffer for line

  calc_freq(total_letters, letters, frequency);
  calc_running(running_frequency, frequency);
  //printf("total number of letters : %d\n", total_letters);
  //print_letter_occurance(letters);
  //print_freq(running_frequency, frequency);
  //print_running(running_frequency);
  
  //FILE *fp = fopen("test.txt", "w"); //(file)setup file to write to
  
  srand(time(NULL));       //setup
  double rand_num = 0.0;   //setup

  /*Loop to print out random letters using running_frequency probability*/
  for(int j = 0; j < 20; j ++) //change to total_letters for file
  {
    rand_num = (double)rand()/RAND_MAX;
    printf("%lf\n", rand_num); //(stdin)test random number against r_f and correct let 
    
    for(int k = 0; k < ALPHABET; k++){
      if(rand_num >= running_frequency[k-1] && rand_num <= running_frequency[k])
      {
	printf("%c", 'a' + k);    //(stdin)print random characters to stdin
	//fputc(('a' + k), fp);   //(file)put random chracter into file
      }
    }
    printf("\n"); //(stdin)uncomment with printf in if loop
  }

  //fclose(fp); //(file)
  
  return 0;
}
