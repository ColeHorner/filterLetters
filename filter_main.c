/*Program that runs statistics and probabilities on the frequencies of letters *
 *in a book that is in a text file.                                            */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "filter.h"
#include "filter_print.h"
#include "filter_calc.h"
#include "filter_word.h"

int main(int argc, char** argv)
{
  char *line = NULL;                       //storing line from getline
  size_t lengthOfBuffer = 0;
  int total_letters, end_of_file, info_or_file, letters_or_words;
  int letters[ALPHABET] = {0};             //Array to store frequency of letters
  double frequency[ALPHABET] = {0};        //Array to store frequency percentage
  double running_frequency[ALPHABET] = {0};//Array to store running frequency
  total_letters = 0;
  int* wordCount;
  wordCount = malloc(sizeof(long int));

  if(argc != 2){
    printf("Please enter file.\n");
    exit(EXIT_FAILURE);
  }
  
  FILE *inputStream = fopen(argv[1], "r"); //opening file
  if(!inputStream){
    perror("inputStream");
    exit(EXIT_FAILURE);
  }
  
  printf("Press 0 for letters or press 1 for words.\n");
  scanf("%d", &letters_or_words);
  
  printf("Press 0 for infomation or press 1 to write to a file.\n");
  scanf("%d", &info_or_file);

  count_words(inputStream, wordCount); //need to do this to create array
  // printf("Word count is: %d\n", *wordCount);
  char words[*wordCount][30];
  
  if(!letters_or_words)
  {
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
    free(line);           //Free buffer for line
    calc_all(total_letters, letters, running_frequency, frequency);
  }
  else{
    printf("Word count is: %d\n", *wordCount); 
    for(int i = 0; i < *wordCount; i++){
      fscanf(inputStream, "%s", words[i]);
    }
    printf("\n");
  }
  fclose(inputStream);  //Close file
  
  if(!info_or_file){
    if(!letters_or_words)
      print_to_screen(running_frequency, frequency, letters, total_letters);
    else{
      printf("print letter stuff to screen\n");//TODO
      for(int i = 0; i < *wordCount; i++){
	//printf("%s ", words[i]);
      }
      printf("\n");
    }
  }
  else{
    if(!letters_or_words)
      print_to_file(running_frequency, total_letters);
    else
      printf("print letter stuff to file\n"); //TODO
  }
  
  return 0;
}
