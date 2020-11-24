#ifndef PARSER
#define PARSER

#include "token.h"
#include "lexer.h"
#include "SyntaxTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Parser {
  Tokens_* tokens;
  Tokens_* prev_tokens;
  Lexer_* lexer;
} Parser_;

Parser_* init_parser(Lexer_* lexer);
SynTree_* parse(Parser_* parser);

#endif