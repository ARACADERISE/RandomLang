#ifndef syn_tree
#define syn_tree

#include <stdlib.h>

typedef struct SynTree {
  enum {
    Tree_Define,
    Tree_Print,
    Tree_eof
  } TreeType;

  /* All trees */
  struct SynTree** trees;
  size_t l_of_trees;

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