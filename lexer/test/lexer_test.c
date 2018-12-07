#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../../token/token.h"

void load_file(const char *filename, char **result){
  char c = '\0';
  unsigned long char_cnt = 0;
  unsigned long bufsize = 128;

  FILE *fp = fopen(filename, "r");

  if(fp == NULL){
    perror("Failed to open file:");
    exit(EXIT_FAILURE);
  }

  *result = malloc(bufsize * sizeof(char));

  if(*result == NULL){
    fprintf(stderr, "Out of memory\n");
    exit(EXIT_FAILURE);
  }

  while((c = fgetc(fp)) != EOF){
    if(char_cnt >= bufsize-1){
      /* Increase buffer since there are more characters to be read */
      bufsize += bufsize;
      *result = realloc(*result, bufsize);

      if(*result == NULL){
        fprintf(stderr, "Out of memory\n");
        exit(EXIT_FAILURE);
      }
    }
    (*result)[char_cnt++] = c;
  }

  (*result)[char_cnt++] = '\0';

  fclose(fp);
}

//Removes all spaces, tabs and newlines
void strip_spaces(char *str){
  char *i = str;
  char *j = str;

  while(*j != '\0'){
    *i = *j++;
    if(*i != ' ' && *i != '\t' && *i != '\n'){
      i++;
    }
  }
  *i = '\0';
}

void TestNextToken(){
  char *filename = "input.pit";
	char *input = NULL;
  load_file(filename, &input);
  strip_spaces(input);

  Token tokens[] = {
    {ASSIGN, "="},
    {PLUS,   "+"},
    {LPAREN, "("},
    {RPAREN, "("},
    {LBRACE, "{"},
    {RBRACE, "}"},
    {COMMA,  ","},
    {SEMICOLON, ";"},
    {END, ""},
  }; 



  free(input);
}

int main(){
  TestNextToken();
	return EXIT_SUCCESS;
}
