#ifndef __AST_H__
#define __AST_H__

#include "../token/token.h"

typedef enum nodeType{
  let,
  ident,
  ret,
}NodeType;

typedef struct node{
  NodeType type;
}Node;

typedef struct statement{
  NodeType type;
  void *stmt;
}Statement;

typedef struct program{
  Statement *statements;
  size_t stmt_cnt;
}Program;

typedef struct identifier{
  Token token;
  string value;
}Identifier;

typedef struct letStatement{
  Token token;
  Identifier *name;
}LetStatement;

char* TokenLiteral(Program *p);

#endif /* __AST_H__ */
