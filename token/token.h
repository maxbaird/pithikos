#ifndef __TOKEN_H__
#define __TOKEN_H__

typedef const char* TokenType;
typedef char string[128];

typedef struct token{
  TokenType Type;
  string Literal;
}Token;

/*****************************************/
/* Constants */
static const char* ILLEGAL         = "ILLEGAL";
static const char* END             = "EOF";

// Identifiers + literals
static const char* IDENT           = "IDENT";
static const char* INT             = "INT";

//Operators
static const char* ASSIGN          = "=";
static const char* PLUS            = "+";

// Delimiters
static const char* COMMA           = ",";
static const char* SEMICOLON       = ";";

static const char* LPAREN          = "(";
static const char* RPAREN          = ")";
static const char* LBRACE          = "{";
static const char* RBRACE          = "}";

// Keywords
static const char* FUNCTION      = "FUNCTION";
static const char* LET           = "LET";

#endif /* __TOKEN_H__ */
