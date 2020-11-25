#include "runtime.h"
#include <stdio.h>

SynTree_* run_define(SynTree_* tree)
{
  return tree; // really nothing else to do..
}

SynTree_* run_print_Method(SynTree_* tree, SynTree_* node)
{ // extremely bugged. Prints backwards. Will fix later!
  int var_printed = -1,val_printed = -1;
  if(tree->print_values_length > 0 && tree->came_first == 1)
  {
    other:
    val_printed = 0;
    for(int i = 0; i < tree->print_values_length; i++)
    {
      printf("%s\n",tree->values_to_print[i]);
    }
    if(tree->print_length > 0 && var_printed == -1) goto print_variables;
  }
  if(tree->print_length > 0 && tree->came_first == 0 && var_printed == -1)
  {
    print_variables:
    var_printed = 0;
    for(int i = 0; i < node->l_of_trees; i++)
    {
      if(node->trees[i]->amount_of_variables > 0)
      {
        for(int x = 0; x < tree->print_length; x++)
        {
          for(int y = 0; y < node->trees[i]->amount_of_variables; y++)
          {
            if(strcmp(tree->variables_to_print[x],node->trees[i]->variable_names[y])==0) printf("%s\n",(char*)node->trees[i]->variable_values[y]);

                      }
        }
      }
    }
    if(tree->print_values_length > 0 && val_printed == -1) goto other;
  }
  return tree;
}

void check(SynTree_* tree, SynTree_* node)
{
  for(int y = 0; y < tree->l_of_trees; y++)
  {
    switch(tree->trees[y]->TreeType)
    {
      case Tree_Print: run_print_Method(tree->trees[y], node);break;
      default: {
        fprintf(stderr,"\nRuntime Error\n\t➥ Uncaught error at if statement\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

SynTree_* run_if_statement(SynTree_* tree, SynTree_* node)
{
  for(int i = 0; i < node->l_of_trees; i++)
  {
    if(node->trees[i]->amount_of_variables > 0)
    {
      for(int x = 0; x < node->trees[i]->amount_of_variables; x++)
      {
        if(strcmp(tree->check_val_lval,node->trees[i]->variable_names[x])==0) {
          char* val = node->trees[i]->variable_values[x];
          if(strcmp(tree->check_action,">")==0)
          {
            if(isdigit(val[0])&&atoi(node->trees[i]->variable_values[x]) > atoi(tree->check_val_rval))
            {
              check(tree,node);
            }
          }
          if(strcmp(tree->check_action,"<")==0)
          {
            if(isdigit(val[0])&&atoi(node->trees[i]->variable_values[x]) < atoi(tree->check_val_rval))
            {
              check(tree,node);
            }
          }
        }
      }
    }
  }
  return tree;
}

SynTree_* check_tree_type(SynTree_* tree, SynTree_* node)
{
  switch(tree->TreeType)
  {
    case Tree_Define: return run_define(tree);
    case Tree_Print: return run_print_Method(tree,node);
    case Tree_IfStatement: return run_if_statement(tree,node);
    default: break; // Tree_eof
  }
  return tree;
}

SynTree_* run_runtime(SynTree_* tree)
{
  for(int i = 0; i < tree->l_of_trees; i++) check_tree_type(tree->trees[i],tree);
  return tree;
}

SynTree_* start_runtime(SynTree_* tree)
{
  return run_runtime(tree);
}