#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lexer.h"
#include "../common/common.h"

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

static bool isLetter(char ch){
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

//Read a character and advance the lexer's position
//until a non-letter-character is found.
static void readIdentifier(Lexer* l, char* literal){
  size_t position = l->position;
  char str[PITHIKOS_BUFFER];
  size_t n = 0;

  while(n < (PITHIKOS_BUFFER+1)){
    if(n == PITHIKOS_BUFFER){
      snprintf(str, PITHIKOS_BUFFER, "Identifiers cannot be longer than %d characters", PITHIKOS_BUFFER);
      PITHIKOS_print(str,PITHIKOS_EROR);
      exit(EXIT_FAILURE);
    }

    if(isLetter(l->ch)){
     readChar(l);
    }else{
      break;
    }
    n++;
  }
  strncpy(literal, l->input+position, n);
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
  safeFree((void **)&l);
}

Token NextToken(Lexer *l){
  char str[PITHIKOS_BUFFER];
  Token tok = {NULL, ""};

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
      break;
    default:
      if (isLetter(l->ch)){
        readIdentifier(l, tok.Literal);
        tok.Type = LookupIdent(tok.Literal);
        return tok;
      }
      tok = newToken(ILLEGAL, l->ch);
  }
  readChar(l);

  /* If type could not be determined */
  if(tok.Type == NULL){
    snprintf(str, PITHIKOS_BUFFER, "Unexpected token type: \"%c\"", l->ch);
    PITHIKOS_print(str, PITHIKOS_EROR);
    exit(EXIT_FAILURE);
  }

  return tok;
}
