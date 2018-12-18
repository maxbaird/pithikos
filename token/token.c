#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

static keyword_t keywords[] = {
  {"fn", FUNCTION},
  {"let", LET}
};

TokenType LookupIdent(char *ident){
  size_t keyword_amt = sizeof(keywords) / sizeof(keywords[0]);
  size_t i = 0;

  for(i = 0; i < keyword_amt; i++){
    if(strcmp(keywords[i].kw, ident) == 0){
      return keywords[i].type;
    }
  }
  return IDENT;
}
