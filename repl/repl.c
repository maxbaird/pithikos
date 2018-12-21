#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lexer/lexer.h"
#include "../token/token.h"
#include "../common/common.h"

#define SIZE 4096
#define PROMPT  ">> "

static void printToken(Token *tok){
  fprintf(stdout, "{Type:%s Literal:%s}\n", tok->Type, tok->Literal);
}

////////////////////////////////////////////////////
void StartRepl(){
  char line[SIZE];
  char *res = NULL;
  Lexer *l;
  Token tok = {NULL, ""};

  for(;;){
    fprintf(stdout, "%s", PROMPT);

    res = fgets(line, SIZE, stdin);

    if(res == NULL){ break; }

    l = InitLexer(line);

    for(tok = NextToken(l); strcmp(tok.Type, END) != 0 ; tok = NextToken(l)){
      printToken(&tok);
    }

    FinalizeLexer(l);
  }
}
