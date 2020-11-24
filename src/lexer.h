#ifndef LEXER
#define LEXER

#include "token.h"
#include <string.h>
#include <ctype.h>

typedef struct Lexer {
  char* source_code;
  int index;
  char curr_char;
  int line;
} Lexer_;

Lexer_* init_lexer(char* code);
Tokens_* get_next_token(Lexer_* lexer);

#endif