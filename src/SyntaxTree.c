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

  // print statement
  tree->print_length = 0;
  tree->came_first = -1;
  tree->print_values_length = 0;
  tree->values_to_print = calloc(1,sizeof(*tree->values_to_print));
  tree->variables_to_print = calloc(1,sizeof(*tree->variables_to_print));

  return tree;
}