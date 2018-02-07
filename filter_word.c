#include <stdio.h>

#include <filter_word.h>

/*Counts the words in the file. */
void count_words(FILE* inputStream, int* wordCount){
  char temp;
  while((temp = fgetc(inputStream)) != EOF){
    if(temp == ' ' || temp == '\n')
      (*wordCount)++;
  }
  rewind(inputStream);
}
