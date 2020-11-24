#include "token.h"

Tokens_* init_token(int token_id, char* value)
{
  Tokens_* tokens = calloc(1,sizeof(*tokens));

  tokens->Type = token_id;
  tokens->val = value;

  return tokens;
}