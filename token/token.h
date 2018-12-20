#ifndef __TOKEN_H__
#define __TOKEN_H__

#include "../common/common.h"

/* Constants */
#define ILLEGAL          "ILLEGAL"
#define END              "EOF"

// Identifiers + literals
#define IDENT            "IDENT"
#define INT              "INT"

//Operators
#define ASSIGN           "="
#define PLUS             "+"
#define MINUS            "-"
#define BANG             "!"
#define ASTERISK         "*"
#define SLASH            "/"

#define LT               "<"
#define GT               ">"
#define EQ               "=="
#define NOT_EQ           "!="

// Delimiters
#define COMMA            ","
#define SEMICOLON        ""

#define LPAREN           "("
#define RPAREN           ")"
#define LBRACE           "{"
#define RBRACE           "}"

// Keywords
#define FUNCTION       "FUNCTION"
#define LET            "LET"
#define TRUE           "TRUE"
#define FALSE          "FALSE"
#define IF             "IF"
#define ELSE           "ELSE"
#define RETURN         "RETURN"

typedef const char* TokenType;
typedef char string[PITHIKOS_BUFFER];

typedef struct token{
  TokenType Type;
  string Literal;
}Token;

typedef struct keyword{
  char *kw;
  TokenType type;
}keyword_t;

TokenType LookupIdent(char *ident);


#endif /* __TOKEN_H__ */
