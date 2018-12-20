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

static bool isDigit(char ch){
  return '0' <= ch && ch <= '9';
}

//Read a character and advance the lexer's position
//until a non-letter-character is found.
static void readIdentifier(Lexer* l, char* literal){
  size_t position = l->position;
  char str[PITHIKOS_BUFFER];
  size_t n = 0;

  while(n < (PITHIKOS_BUFFER + 1)){
    if(n == PITHIKOS_BUFFER){
      snprintf(str, PITHIKOS_BUFFER, "Identifiers cannot be longer than %d characters", PITHIKOS_BUFFER);
      PITHIKOS_fatal(str);
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

static void readNumber(Lexer *l, char *literal){
  size_t position = l->position;
  char str[PITHIKOS_BUFFER];
  size_t n = 0;

  while(n < (PITHIKOS_MAX_INT_LEN + 1)){
    if(n == PITHIKOS_MAX_INT_LEN){
      snprintf(str, PITHIKOS_BUFFER, "Integers cannot be greater than %d digits.", PITHIKOS_MAX_INT_LEN);
      PITHIKOS_fatal(str);
    }

    if(isDigit(l->ch)){
      readChar(l);
    }else{
      break;
    }
    n++;
  }
  strncpy(literal, l->input+position, n);
}

static void skipWhitespace(Lexer *l){
  for(;;){
    if(l->ch == ' ' ||  l->ch == '\t' || l->ch == '\n' || l->ch == '\r'){
      readChar(l);
    }else{
      break;
    }
  }
}

//Function to look ahead and get the next character without moving to it
static char peekChar(Lexer *l){
  if(l->readPosition >= strlen(l->input)){
    return (char) 0;
  }
  return l->input[l->readPosition];
}
//////////////////////////////////////////////////////////////

Lexer* InitLexer(const char *input){
  Lexer *l = malloc(sizeof(Lexer));

  if(l == NULL){
    PITHIKOS_fatal("Failed to init lexer!");
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

  skipWhitespace(l);

  switch (l->ch) {
    case '=':
      if(peekChar(l) == '='){
        char ch = l->ch;
        readChar(l);
        tok.Type = EQ;
        snprintf(tok.Literal, PITHIKOS_BUFFER, "%c%c", ch, l->ch);
      }else{
        tok = newToken(ASSIGN, l->ch);
      }
      break;
    case '+':
      tok = newToken(PLUS, l->ch);
      break;
    case '-':
      tok = newToken(MINUS, l->ch);
      break;
    case '!':
      if(peekChar(l) == '='){
        char ch = l->ch;
        readChar(l);
        tok.Type = NOT_EQ;
        snprintf(tok.Literal, PITHIKOS_BUFFER, "%c%c", ch, l->ch);
      }else{
        tok = newToken(BANG, l->ch);
      }
      break;
    case '/':
      tok = newToken(SLASH, l->ch);
      break;
    case '*':
      tok = newToken(ASTERISK, l->ch);
      break;
    case '<':
      tok = newToken(LT, l->ch);
      break;
    case '>':
      tok = newToken(GT, l->ch);
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
      }else if(isDigit(l->ch)){
        tok.Type = INT;
        readNumber(l, tok.Literal);
        return tok;
      }
      tok = newToken(ILLEGAL, l->ch);
  }
  readChar(l);

  /* If type could not be determined */
  if(tok.Type == NULL){
    snprintf(str, PITHIKOS_BUFFER, "Unexpected token type: \"%c\"", l->ch);
    PITHIKOS_fatal(str);
  }

  return tok;
}
