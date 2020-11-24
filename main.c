#include <stdio.h>
#include "src/readfile.h"
#include "src/lexer.h"
#include "src/parser.h"
#include "src/SyntaxTree.h"
#include "src/runtime.h"

int main(int argc, char* argv[])
{

  if(argc < 2)
  {
    fprintf(stderr,"\nExpecting input file.");
    exit(EXIT_FAILURE);
  }
  Lexer_* lex = init_lexer(readFile(argv[1]));
  Parser_* parser = init_parser(lex);
  SynTree_* tree = parse(parser);
  start_runtime(tree);
  return 0;
}