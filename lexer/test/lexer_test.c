#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "../../token/token.h"
#include "../lexer.h"

typedef struct test{
  TokenType   expectedType;
  const char* expectedLiteral;
}test_t;

static void load_file(const char *filename, char **result){
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

void TestNextToken(){
  char *filename = "input.pit";
	char *input = NULL;
  size_t i = 0;

  load_file(filename, &input);

  test_t tests[] = {
    {LET, "let"},
    {IDENT, "five"},
    {ASSIGN, "="},
    {INT, "5"},
    {SEMICOLON, ";"},
    {LET, "let"},
    {IDENT, "ten"},
    {ASSIGN, "="},
    {INT, "10"},
    {SEMICOLON, ";"},
    {LET, "let"},
    {IDENT, "add"},
    {ASSIGN, "="},
    {FUNCTION, "fn"},
    {LPAREN, "("},
    {IDENT, "x"},
    {COMMA, ","},
    {IDENT, "y"},
    {RPAREN, ")"},
    {LBRACE, "{"},
    {IDENT, "x"},
    {PLUS, "+"},
    {IDENT, "y"},
    {SEMICOLON, ";"},
    {RBRACE, "}"},
    {SEMICOLON, ";"},
    {LET, "let"},
    {IDENT, "result"},
    {ASSIGN, "="},
    {IDENT, "add"},
    {LPAREN, "("},
    {IDENT, "five"},
    {COMMA, ","},
    {IDENT, "ten"},
    {RPAREN, ")"},
    {SEMICOLON, ";"},
    {BANG, "!"},
		{MINUS, "-"},
		{SLASH, "/"},
		{ASTERISK, "*"},
		{INT, "5"},
		{SEMICOLON, ";"},
		{INT, "5"},
		{LT, "<"},
		{INT, "10"},
		{GT, ">"},
		{INT, "5"},
		{SEMICOLON, ";"},
 		{IF, "if"},
		{LPAREN, "("},
		{INT, "5"},
		{LT, "<"},
		{INT, "10"},
		{RPAREN, ")"},
		{LBRACE, "{"},
		{RETURN, "return"},
		{TRUE, "true"},
		{SEMICOLON, ";"},
		{RBRACE, "}"},
		{ELSE, "else"},
		{LBRACE, "{"},
		{RETURN, "return"},
		{FALSE, "false"},
 		{SEMICOLON, ";"},
		{RBRACE, "}"},
    {INT, "10"},
		{EQ, "=="},
		{INT, "10"},
		{SEMICOLON, ";"},
		{INT, "10"},
		{NOT_EQ, "!="},
		{INT, "9"},
		{SEMICOLON, ";"},
    {END, ""}
  };

  Lexer *l = InitLexer(input);

  size_t testSize = sizeof(tests) / sizeof(tests[0]);

  for(i = 0; i < testSize; i++){
    Token tok = NextToken(l);

    if(strcmp(tok.Type, tests[i].expectedType) != 0){
      fprintf(stderr, "tests[%zu] - tokentype wrong. expected=\"%s\", got=\"%s\"\n",i, tests[i].expectedType, tok.Type);
      break;
    }

    if(strcmp(tok.Literal, tests[i].expectedLiteral) != 0){
      fprintf(stderr, "tests[%zu] - literal wrong. expected=\"%s\", got=\"%s\"\n", i, tests[i].expectedLiteral, tok.Literal);
      break;
    }
  }

  if(i == testSize){
    fprintf(stdout, "ok\n");
  }else{
    fprintf(stderr, "FAIL\n");
  }

  fflush(stdout);

  FinalizeLexer(l);
  free(input);
}

int main(){
  TestNextToken();
	return EXIT_SUCCESS;
}
