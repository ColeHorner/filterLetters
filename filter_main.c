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
  char *line = NULL;                       //storing line from getline
  int total_letters = 0;                   //Storing total number of letters
  size_t lengthOfBuffer = 0;               //buffer for getline
  ssize_t end_of_file;                     //Number of characters read from getline
  int letters[ALPHABET] = {0};             //Array to store frequency of letters
  double frequency[ALPHABET] = {0};        //Array to store frequency percentage
  double running_frequency[ALPHABET] = {0};//Array to store running frequency

  if(argc != 2)
  {
    printf("Please enter file.\n");
    exit(EXIT_FAILURE);
  }
  
  printf("press 0 for info or press 1 for file\n");
  int info_or_file = getchar(); // bugged ghetto fixed
  FILE *inputStream = fopen(argv[1], "r"); //opening file
  
  if(!inputStream){
    perror("inputStream");
    exit(EXIT_FAILURE);
  }

  /*Reads the file from text and stores it in the array line*/
  do{
    end_of_file = getline(&line, &lengthOfBuffer, inputStream);
    for(int i = 0; i < lengthOfBuffer; i++)
    {
      line[i] = tolower(line[i]);
      if(line[i] >= 'a' && line[i] <= 'z')
      {
	letters[line[i] - 'a']++;
	total_letters++;
      }
    }
  }while(end_of_file != END_OF_FILE);
  
  fclose(inputStream);  //Close file
  free(line);           //Free buffer for line

  calc_all(total_letters, letters, running_frequency, frequency); //Calculations
  
  srand(time(NULL));       //Setup random numbers
  double rand_num = 0.0;   //Setup random numbers
  
  if(info_or_file == 48)
  {
    print_info(running_frequency, frequency, letters, total_letters);
    
    /*Loop to print out random letters using running_frequency probability*/
    for(int j = 0; j < TESTNUMBER; j ++)
    {
      rand_num = (double)rand()/RAND_MAX;
      printf("%lf ", rand_num); //test random number against r_f and correct letter
    
      for(int k = 0; k < ALPHABET; k++){
	if(rand_num >= running_frequency[k-1] && rand_num <= running_frequency[k])
	  {
	    printf("%c", 'a' + k);    //print random characters to console
	  }
      }
      printf("\n");
    }
  }
  else
  {
    FILE *fp = fopen("random_letters.txt", "w"); //setup file to write to
    if(!fp)
    {
      perror("fp");
      exit(EXIT_FAILURE);
    }
    /*Loop to print out random letters using running_frequency probability*/
    for(int j = 0; j < total_letters; j ++)
    {
      rand_num = (double)rand()/RAND_MAX; 
      for(int k = 0; k < ALPHABET; k++)
      {
	if(rand_num >= running_frequency[k-1] && rand_num <= running_frequency[k])
	fputc(('a' + k), fp);   //put random chracter into file
      }
    }
    printf("Written successfully!\n");
    fclose(fp);
  }
  return 0;
}
