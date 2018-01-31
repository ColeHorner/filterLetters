/**
 * This is a program to count how many times
 * each letter of the alphabet occurs in a sample
 * of text
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define ALPHABET 26

int main(int argc, char** argv)
{
  char *line = NULL;                        //storing line from getline
  int total_letters = 0;                    //Storing total number of letters
  size_t lengthOfBuffer = 0;                //buffer for getline
  ssize_t numberOfCharactersRead;           //Number of characters read from getline
  int letters[ALPHABET] = {0};              //Array to store frequency of letters
  double frequency[ALPHABET] = {0};         //Array to store frequency percentage
  double running_frequency[ALPHABET] = {0}; //Array to store running frequency
 
  FILE * inputStream = fopen( "Dracula.txt", "r" ); //opening file

  /*Reading first line of file*/
  numberOfCharactersRead = getline(&line, &lengthOfBuffer, inputStream);
  
  if( numberOfCharactersRead == -1 )
  {
    perror( "getline" );
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
  
  fclose( inputStream );  //Close file
  free( line );           //Free buffer for line
  
  /*Loop to print each letter and number of times it appears. Also divides the         * 
   *frequency of each letter by the total number of letters and stores it in an array. */
  for(int k = 0; k < ALPHABET; k++)
  {
    printf("%c = %d\n", ('a' + k), letters[k]);
    frequency[k] = (((double)letters[k])/total_letters);
  }
  
  printf("total number of letters : %d\n", total_letters); //Total number of letters.
  
  /*Loop to print frequency of each letter over total letters, also adds the  *
   *frequencies together to get a running frequency.                          */
  for(int j = 0; j < ALPHABET; j++)
  {
    printf("frequency of %c over total letters = %.2lf%%\n",
	   ('a' + j), (frequency[j] * 100));
    
    if(j > 0)
      running_frequency[j] = frequency[j] + running_frequency[j-1];
    else
      running_frequency[j] = frequency[j];
  }
  /*Loop to print running frequency percentages*/
  for(int m = 0; m < ALPHABET; m++){
    printf("running frequency[%d] %c =  %.4lf\n",m ,'a' + m ,running_frequency[m]);
  }

  //FILE *fp = fopen("test.txt", "w"); //(file)setup file to write to
  srand(time(NULL));     //setup
  double rand_num = 0.0; //setup

  /*Loop to print out random letters using running_frequency probability*/
  for(int j = 0; j < 20; j ++) //change to total_letters for file
  {
    rand_num = (double)rand()/RAND_MAX;
    printf("%lf\n", rand_num); //(stdin)test random number against r_f and correct let 
    
    for(int k = 0; k < ALPHABET; k++){
      if(rand_num >= running_frequency[k-1] && rand_num <= running_frequency[k])
      {
	printf("%c", 'a' + k);    //(stdin)print random characters to stdin
	//fputc(('a' + k), fp);       //(file)put random chracter into file
      }
    }
    printf("\n"); //(stdin)uncomment with printf in if loop
  }

  //fclose(fp); //(file)
  
  return 0;
}


