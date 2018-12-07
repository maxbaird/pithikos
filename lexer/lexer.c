#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

//This function gets the next character and advances
//the position in the input string.
static void readChar(Lexer *l){
  //First check if we have reached the end of input
  if(l->readPosition >= strlen(l->input)){
    l->ch = 0; //Set to NULL
  }else{
    //Get next character
    l->ch = l->input[l->readPosition];
  }

  l->position = l->readPosition;
  l->readPosition++;
}

static Token newToken(TokenType tokenType, char ch){
  char str [3] = "\0";
  str[0] = ch;

  Token token;
  token.Type = tokenType;
  strcpy(token.Literal, str);
  return token;
}
//////////////////////////////////////////////////////////////

Lexer* InitLexer(const char *input){
  Lexer *l = malloc(sizeof(Lexer));

  if(l == NULL){
    fprintf(stderr, "Failed to init lexer!\n");
    exit(EXIT_FAILURE);
  }

  l->input = input;
  l->position = 0;
  l->readPosition = 0;
  l->ch = '\0';

  readChar(l);

  return l;
}

void FinalizeLexer(Lexer *l){
  free(l);
}

Token NextToken(Lexer *l){
  Token tok;

  switch (l->ch) {
    case '=':
      tok = newToken(ASSIGN, l->ch);
      break;
    case ';':
      tok = newToken(SEMICOLON, l->ch);
      break;
    case '(':
      tok = newToken(LPAREN, l->ch);
      break;
    case ')':
      tok = newToken(RPAREN, l->ch);
      break;
    case ',':
      tok = newToken(COMMA, l->ch);
      break;
    case '+':
      tok = newToken(PLUS, l->ch);
      break;
    case '{':
      tok = newToken(LBRACE, l->ch);
      break;
    case '}':
      tok = newToken(RBRACE, l->ch);
      break;
    case 0:
      strcpy(tok.Literal, "");
      tok.Type = END;
  }
  readChar(l);
  return tok;
}
