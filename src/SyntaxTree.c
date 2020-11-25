#include "SyntaxTree.h"

SynTree_* init_tree(int type)
{
  SynTree_* tree = calloc(1,sizeof(*tree));

  tree->TreeType = type;
  tree->l_of_trees = 0;
  tree->trees = calloc(1,sizeof(*tree->trees));

  // variable definitions
  tree->amount_of_variables = 0;
  tree->variable_names = calloc(1,sizeof(*tree->variable_names));
  tree->variable_values = calloc(1,sizeof(*tree->variable_values));

  /* If statement */
  tree->check_val_lval = calloc(1,sizeof(*tree->check_val_lval));
  tree->check_val_rval = calloc(1,sizeof(*tree->check_val_rval));
  tree->check_action = calloc(1,sizeof(*tree->check_action));
  tree->or_lvals = calloc(1,sizeof(*tree->or_lvals));
  tree->or_rvals = calloc(1,sizeof(*tree->or_rvals));
  tree->and_lvals = calloc(1,sizeof(*tree->and_lvals));
  tree->and_rvals = calloc(1,sizeof(*tree->and_rvals));
  tree->and_actions = calloc(1,sizeof(*tree->and_actions));
  tree->or_actions = calloc(1,sizeof(*tree->or_actions));
  //tree->amount_of_checks = 0;
  tree->amount_of_or_checks = 0;
  tree->amount_of_and_checks = 0;

  // print statement
  tree->print_length = 0;
  tree->came_first = -1;
  tree->print_values_length = 0;
  tree->values_to_print = calloc(1,sizeof(*tree->values_to_print));
  tree->variables_to_print = calloc(1,sizeof(*tree->variables_to_print));

  return tree;
}