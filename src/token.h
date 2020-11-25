#ifndef TOKENS
#define TOKENS

#include <stdlib.h>

typedef struct Tokens {
  enum {
    Id,
    Arrow,
    Equals,
    Define_Keyword,
    IfStatement,
    Colon,
    GT,
    LT,
    And,
    Or,
    Comma,
    Intval,
    Strval,
    Print_Keyword,
    LP,
    RP,
    Eof
  } Type;
  char* val;
} Tokens_;

Tokens_* init_token(int token_id, char* value);

#endif