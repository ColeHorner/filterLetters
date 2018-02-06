/*Program that runs statistics and probabilities on the frequencies of letters *
 *in a book that is in a text file.                                            */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "filter.h"
#include "filter_print.h"
#include "filter_calc.h"

int main(int argc, char** argv)
{
  char *line = NULL;                       //storing line from getline
  size_t lengthOfBuffer = 0;
  int total_letters, end_of_file, info_or_file;
  int letters[ALPHABET] = {0};             //Array to store frequency of letters
  double frequency[ALPHABET] = {0};        //Array to store frequency percentage
  double running_frequency[ALPHABET] = {0};//Array to store running frequency

  total_letters = 0;

  if(argc != 2){
    printf("Please enter file.\n");
    exit(EXIT_FAILURE);
  }
  
  FILE *inputStream = fopen(argv[1], "r"); //opening file
  if(!inputStream){
    perror("inputStream");
    exit(EXIT_FAILURE);
  }
  
  printf("Press 0 for info or press 1 for file.\n");
  scanf("%d", &info_or_file);

  end_of_file = getline(&line, &lengthOfBuffer, inputStream);
  /*Reads the file from text and stores it in the array line*/
  do{
    for(int i = 0; i < lengthOfBuffer; i++)
    {
      line[i] = tolower(line[i]);
      if(line[i] >= 'a' && line[i] <= 'z')
      {
	letters[line[i] - 'a']++;
	total_letters++;
      }
    }
    end_of_file = getline(&line, &lengthOfBuffer, inputStream);
  }while(end_of_file != END_OF_FILE);
  
  fclose(inputStream);  //Close file
  free(line);           //Free buffer for line

  calc_all(total_letters, letters, running_frequency, frequency);
  
  if(!info_or_file)
    print_to_screen(running_frequency, frequency, letters, total_letters);
  else
    print_to_file(running_frequency, total_letters);
  
  return 0;
}
