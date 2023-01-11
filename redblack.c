#include <stdio.h>
#include <stdlib.h>

#include "type_t.h"
#include "redblack.h"
#include "common.h"


//rb_tree_t* create_tree(comparator_t cmp, printer_t printer, int height_diff);



bool add(rb_tree_t* tree, type_t data);




bool rmv(rb_tree_t* tree, type_t data);


void __print_node(FILE* fp, rb_tree_t* tree, rb_node_t* node) {
  if(!node)
    return;
  tree->printer(fp, node->data, true);
  fprintf(fp, "%s", node->color == RED ? "(R)" : "");
  __print_node(fp, tree, node->left);
  __print_node(fp, tree, node->right);
}

void print(FILE* fp, rb_tree_t* tree) {
  __print_node(fp, tree, tree->root);
}

void __dot_print_node(FILE* fp, rb_tree_t* tree, rb_node_t* node) {
  if(!node)
    return;
  fprintf(fp, "  "); 
  tree->printer(fp, node->data, true);
  if(node->color == BLACK)
    fprintf(fp, " [style=\"filled\",color=\"black\",fontcolor=\"white\"]");
  else
    fprintf(fp, " [style=\"filled\",color=\"red\",fontcolor=\"black\"]");
  fprintf(fp, "\n");
  
  if(node->left != NULL) {
    fprintf(fp, "  ");
    tree->printer(fp, node->data, true);
    fprintf(fp, " -- ");
    tree->printer(fp, node->left->data, true);
    fprintf(fp, "\n");
  }
  
  if(node->right != NULL) {
    fprintf(fp, "  ");
    tree->printer(fp, node->data, true);
    fprintf(fp, " -- ");
    tree->printer(fp, node->right->data, true);
    fprintf(fp, "\n");
  }
  
  __dot_print_node(fp, tree, node->left);
  __dot_print_node(fp, tree, node->right);
}

void dot_print(FILE* fp, rb_tree_t* tree) {
  fprintf(fp, "graph G {\n");
  __dot_print_node(fp, tree, tree->root);
  fprintf(fp, "}\n");
}
