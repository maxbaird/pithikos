#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "../../token/token.h"
#include "../lexer.h"

typedef const char* string;

typedef struct test{
  TokenType expectedType;
  string expectedLiteral;
}test_t;

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
  size_t i = 0;
  bool no_err = true;

  load_file(filename, &input);
  strip_spaces(input);

  test_t tests[] = {
    {ASSIGN, "="},
    {PLUS,   "+"},
    {LPAREN, "("},
    {RPAREN, ")"},
    {LBRACE, "{"},
    {RBRACE, "}"},
    {COMMA,  ","},
    {SEMICOLON, ";"},
    {END, ""},
  }; 

  Lexer *l = InitLexer(input);

  size_t testSize = sizeof(tests) / sizeof(tests[0]);

  for(i = 0; i < testSize; i++){
    Token tok = NextToken(l);

    if(strcmp(tok.Type, tests[i].expectedType) != 0){
      fprintf(stderr, "tests[%zu] - tokentype wrong. expected=%s, got=%s\n",i, tests[i].expectedType, tok.Type);
      no_err = false;
    }

    if(strcmp(tok.Literal, tests[i].expectedLiteral) != 0){
      fprintf(stderr, "tests[%zu] - literal wrong. expected=%s, got=%s\n", i, tests[i].expectedLiteral, tok.Literal);
      no_err = false;
    }
  }

  if(no_err){
    fprintf(stdout, "Passed\n");
    fflush(stdout);
  }

  free(input);
}

int main(){
  TestNextToken();
	return EXIT_SUCCESS;
}
