#include "parser.h"

Parser_* init_parser(Lexer_* lexer)
{
  Parser_* parser = calloc(1,sizeof(*parser));

  parser->lexer = lexer;
  parser->tokens = get_next_token(parser->lexer);
  parser->prev_tokens = parser->tokens;

  return parser;
}

Parser_* parser_get_next_token(Parser_* parser, int id)
{
  if(id == parser->tokens->Type)
  {
    parser->prev_tokens = parser->tokens;
    parser->tokens = get_next_token(parser->lexer);

    return parser;
  }
  fprintf(stderr,"\nInvalid token type\n\t➥ on line %d:\n\t➥ `%s`\n",parser->lexer->line,parser->tokens->val);
  exit(EXIT_FAILURE);
}

SynTree_* parse_define_keyword(Parser_* parser)
{
  SynTree_* tree = init_tree(Tree_Define);
  
  begin:
  parser_get_next_token(parser,Define_Keyword);

  if(parser->tokens->Type == Colon)
  {
    parser_get_next_token(parser,Colon);

    if(parser->tokens->Type == Id)
    {
      tree->amount_of_variables++;
      tree->variable_names = realloc(
        tree->variable_names,
        (tree->amount_of_variables+1)*sizeof(*tree->variable_names)
      );
      tree->variable_names[tree->amount_of_variables-1] = parser->tokens->val;
      parser_get_next_token(parser, Id);

      if(parser->tokens->Type == Equals)
      {
        parser_get_next_token(parser,Equals);
        tree->variable_values = realloc(
          tree->variable_values,
          (tree->amount_of_variables+1)*sizeof(*tree->variable_values)
        );
        tree->variable_values[tree->amount_of_variables-1] = parser->tokens->val;
        parser_get_next_token(parser,Intval);
      }

      if(parser->tokens->Type == Define_Keyword) goto begin;
    }
  }

  return tree;
}

SynTree_* parse_print_keyword(Parser_* parser)
{
  SynTree_* tree = init_tree(Tree_Print);

  parser_get_next_token(parser, Print_Keyword);

  if(parser->tokens->Type == LP)
  { // one type of syntax
    parser_get_next_token(parser, LP);
  } else if(parser->tokens->Type == Colon)
  { // second type
    parser_get_next_token(parser, Colon);
  } else
  {
    fprintf(stderr,"\nSyntax Error:\n\t➥ Expected `:` or `()` on line %d\n",parser->lexer->line);
    exit(EXIT_FAILURE);
  }

  if(parser->tokens->Type == Id)
  {
    if(tree->came_first == -1) tree->came_first = 0;
    GetId:
    tree->print_length++;
    tree->variables_to_print = realloc(
      tree->variables_to_print,
      (tree->print_length+1)*sizeof(*tree->variables_to_print)
    );
    tree->variables_to_print[tree->print_length-1] = parser->tokens->val;
    parser_get_next_token(parser, Id);

    while(parser->tokens->Type == Comma)
    {
      parser_get_next_token(parser, Comma);

      if(parser->tokens->Type == Id)
      {
        tree->print_length++;
        tree->variables_to_print = realloc(
          tree->variables_to_print,
          (tree->print_length+1)*sizeof(*tree->variables_to_print)
        );
        tree->variables_to_print[tree->print_length-1] = parser->tokens->val;
        parser_get_next_token(parser, Id);
      } else if(parser->tokens->Type == Intval) goto GetInt;
    }
  } else if(parser->tokens->Type == Intval)
  {
    if(tree->came_first == -1) tree->came_first = 1;
    GetInt:
    tree->print_values_length++;
    tree->values_to_print = realloc(
      tree->values_to_print,
      (tree->print_values_length+1)*sizeof(*tree->values_to_print)
    );
    tree->values_to_print[tree->print_values_length-1] = parser->tokens->val;
    parser_get_next_token(parser, Intval);

    while(parser->tokens->Type == Comma)
    {
      parser_get_next_token(parser, Comma);

      if(parser->tokens->Type == Intval)
      {
        tree->print_values_length++;
        tree->values_to_print = realloc(
          tree->values_to_print,
          (tree->print_values_length+1)*sizeof(*tree->values_to_print)
        );
        tree->values_to_print[tree->print_values_length-1] = parser->tokens->val;
        parser_get_next_token(parser, Intval);
      } else if(parser->tokens->Type == Id) goto GetId;
    }
  } else if(parser->tokens->Type == Strval)
  {
  
  } else
  {
    fprintf(stderr,"\nPrint error\n\t➥ Empty print statement found on line %d\n",parser->lexer->line);
    exit(EXIT_FAILURE);
  }

  if(parser->tokens->Type == RP) parser_get_next_token(parser, RP);

  return tree;
}

SynTree_* parse_if_statement(Parser_* parser)
{

  SynTree_* tree = init_tree(Tree_IfStatement);

  parser_get_next_token(parser, IfStatement);

  if(parser->tokens->Type == Colon)
  {
    parser_get_next_token(parser,Colon);
  } else if(parser->tokens->Type == LP)
  {
    parser_get_next_token(parser, LP);
  } else 
  {
    fprintf(stderr,"\nSyntax Error:\n\t➥ Expected `:` or `()` on line %d\n",parser->lexer->line);
    exit(EXIT_FAILURE);
  }

  begin:
  if(parser->tokens->Type == Id)
  {
    tree->check_val_lval = parser->tokens->val;
    parser_get_next_token(parser, Id);

    if(parser->tokens->Type == GT)
    {
      tree->check_action = parser->tokens->val;
      parser_get_next_token(parser, GT);

      if(parser->tokens->Type == Eof)
      {
        fprintf(stderr,"\nParsing Error:\n\t➥ Unexpected End Of File(EOF) on line %d\n",parser->lexer->line);
        exit(EXIT_FAILURE);
      }

      if(parser->tokens->Type == Id)
      {
        printf("Here");
        exit(EXIT_SUCCESS);
      } else if(parser->tokens->Type == Intval)
      {
        tree->check_val_rval = parser->tokens->val;
        parser_get_next_token(parser, Intval);
      }

      if(parser->tokens->Type == And)
      {
        parser_get_next_token(parser, And);

        if(parser->tokens->Type == Id)
        {
          tree->amount_of_and_checks++;
          tree->and_lvals = realloc(
            tree->and_lvals,
            (tree->amount_of_and_checks+1)*sizeof(*tree->and_lvals)
          );
          tree->and_lvals[tree->amount_of_and_checks-1] = parser->tokens->val;
          parser_get_next_token(parser, Id);
        } else if(parser->tokens->Type == Intval)
        {
          tree->amount_of_and_checks++;
          tree->and_lvals = realloc(
            tree->and_lvals,
            (tree->amount_of_and_checks+1)*sizeof(*tree->and_lvals)
          );
          tree->and_lvals[tree->amount_of_and_checks-1] = parser->tokens->val;
          parser_get_next_token(parser, Intval);
        }
      }
    }
  }

  if(parser->tokens->Type == RP) parser_get_next_token(parser, RP);

  redo:
  switch(parser->tokens->Type)
  {
    case Print_Keyword:
    {
      SynTree_* secondaryTree = parse_print_keyword(parser);
      tree->l_of_trees++;
      tree->trees = realloc(
        tree->trees,
        (tree->l_of_trees+1)*sizeof(*tree->trees)
      );
      tree->trees[tree->l_of_trees-1] = secondaryTree;

      if(parser->tokens->Type != Eof) goto redo;
      goto end;
    }
    default:
    {
      fprintf(stderr,"\nSyntax Error:\n\t➥ Unexpected `%s` on line %d\n",parser->tokens->val,parser->lexer->line);
      exit(EXIT_FAILURE);
    }
  }

  end:
  return tree;
}

SynTree_* parse_current_state(Parser_* parser)
{
  switch(parser->tokens->Type)
  {
    case Define_Keyword: return parse_define_keyword(parser);
    case Print_Keyword: return parse_print_keyword(parser);
    case IfStatement: return parse_if_statement(parser);
    default:break; // error here, will get to that later on
  }
  return init_tree(Tree_eof);
}

SynTree_* parse_rand(Parser_* parser)
{
  SynTree_* Tree = calloc(1,sizeof(*Tree));
  Tree = parse_current_state(parser);

  Tree->trees[0] = Tree;
  Tree->l_of_trees++;

  while(parser->tokens->Type != Eof)
  {
    SynTree_* tree = parse_current_state(parser);

    if(tree)
    {
      Tree->l_of_trees++;
      Tree->trees = realloc(
        Tree->trees,
        (Tree->l_of_trees+1)*sizeof(*Tree->trees)
      );
      Tree->trees[Tree->l_of_trees-1] = tree;
    }
  }

  return Tree;
}

SynTree_* parse(Parser_* parser)
{
  return parse_rand(parser);
}