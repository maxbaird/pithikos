#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"
#include "ast.h"

static char* letTokenLiteral(LetStatement *ls){
  return ls->token.Literal;
}

static char* identTokenLiteral(Identifier *ident){
  return ident->token.Literal;
}

char* TokenLiteral(Program *p){
  if(p->stmt_cnt > 0){
    switch(p->statements[0].type){
      case let: return letTokenLiteral((LetStatement *)p->statements[0].stmt);
      case ident: return identTokenLiteral((Identifier*)p->statements[0].stmt);
      default: PITHIKOS_fatal("Invalid statment type");
    }
  }
  return NULL;
}
