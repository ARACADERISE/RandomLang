#ifndef syn_tree
#define syn_tree

#include <stdlib.h>

typedef struct SynTree {
  enum {
    Tree_Define,
    Tree_Print,
    Tree_IfStatement,
    Tree_eof
  } TreeType;

  /* All trees */
  struct SynTree** trees;
  size_t l_of_trees;

  /* If Statement */
  void** check_val_lval;
  void** check_val_rval;
  char** check_action;
  void** or_lvals;
  void** or_actions;
  void** or_rvals;
  void** and_lvals;
  void** and_actions;
  void** and_rvals;
  size_t amount_of_checks;
  size_t amount_of_or_checks;
  size_t amount_of_and_checks;

  /* For Tree_Define */
  char** variable_names;
  void** variable_values;
  size_t amount_of_variables;

  /* Tree_Print */
  char** values_to_print; // both Intval and Strval
  void** variables_to_print;
  size_t print_length;
  size_t print_values_length;
  int came_first; // easy fix ig
} SynTree_;

SynTree_* init_tree(int type);

#endif