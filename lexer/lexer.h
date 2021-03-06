#ifndef __LEXER_H__
#define __LEXER_H__

#include "../token/token.h"

typedef struct lexer{
 const char*    input;
 size_t         position;     // Current position in input (points to current char)
 size_t         readPosition; // Current reading position in input (after current char)
 char           ch;           // Current char under examination
}Lexer;

Lexer* InitLexer(const char *input);
void FinalizeLexer(Lexer *l);
Token NextToken(Lexer *l);

#endif /* __LEXER_H__ */
