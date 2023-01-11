#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "avl.h"
#include "type_t.h"
#include "common.h"


int left_child_height(avl_node_t* node){
	avl_node_t* child;
	
	if(node->left== NULL){
		return(0);
	}
	
	child= node->left;
	
	return(child->height);
}

int right_child_height(avl_node_t* node){
	avl_node_t* child;
	
	if(node->right== NULL){
		return(0);
	}
	
	child= node->right;
	
	return(child->height);
}

void update_height(avl_node_t* node){

	int left, right;
	
	left= left_child_height(node);
	right= right_child_height(node);
	
	if(left!=0 && left>= right){
		node->height= left+ 1;
		return;
	}
	else if(right!=0 && right>= left){
		node->height= right+ 1;
		return;
	}
	else{
		node->height= 1;
		return;
	}
}

bool is_balanced(avl_tree_t *tree, avl_node_t* node){
	
	int left, right;
	
	left= left_child_height(node);
	right= right_child_height(node);
	
	if((left- right >= 2) || (right- left >= 2)){
		return(false);
	}
	return(true);
}

avl_node_t* rebalancing_child(avl_node_t* node){

	int left, right;
	avl_node_t* right_child, *left_child;
	
	left= left_child_height(node);
	right= right_child_height(node);
	
	if(right== 0 && left!= 0){
		return(node->left);
	}
	if(left== 0 && right!= 0){
		return(node->right);
	}
	
	right_child= node->right;
	left_child= node->left;
	
	if(left> right){
		return(left_child);
	}
	else if(right> left){
		return(right_child);
	}
	else{
		return(NULL);
	}
}

avl_node_t* reconstruct(avl_tree_t* tree, avl_node_t* v, avl_node_t* w, avl_node_t* u){
	avl_node_t* p;
	
	if(v->right!= NULL && w->right!= NULL){
		if(w== v->right && u== w->right){
			if(v->parent!= NULL){
				p= v->parent;
				if(p->right!= NULL){
					if(p->right== v){
						p->right= w;
					}
					else{
						p->left= w;
					}
				}
			    else{
					p->left= w;
				}
				if(w->left!= NULL){
					w->left->parent= v;
					v->right= w->left;
				}
				else{
					v->right= NULL;
				}
				w->left= v;
				w->right= u;
				
				w->parent= p;
				v->parent= w;
				u->parent= w;
			}
			else{
				if(w->left!= NULL){
					w->left->parent= v;
					v->right= w->left;
				}
				else{
					v->right= NULL;
				}
				w->left= v;
				w->right= u;
				
				tree->root= w;
				w->parent= NULL;
				v->parent= w;
				u->parent= w;
			}
			return(w);
		}
	}
	
	if(v->right!= NULL && w->left!= NULL){
		if(w== v->right && u== w->left){
			if(v->parent!= NULL){
				p= v->parent;
				if(p->right!= NULL){
					if(p->right== v){
						p->right= u;
					}
					else{
						p->left= u;
					}
				}
				else{
					p->left= u;
				}
				if(u->left!= NULL){
					u->left->parent= v;
					v->right= u->left;
				}
				else{
					v->right= NULL;
				}
				
				if(u->right!= NULL){
					u->right->parent= w;
					w->left= u->right;
				}
				else{
					w->left= NULL;
				}
				
				u->left= v;
				u->right= w;
				
				u->parent= p;
				v->parent= u;
				w->parent= u;
			}
			else{
				if(u->left!= NULL){
					u->left->parent= v;
					v->right= u->left;
				}
				else{
					v->right= NULL;
				}
				
				if(u->right!= NULL){
					u->right->parent= w;
					w->left= u->right;
				}
				else{
					w->left= NULL;
				}
				
				u->left= v;
				u->right= w;
				
				tree->root= u;
				u->parent= NULL;
				v->parent= u;
				w->parent= u;
			}
			return(u);
		}
	}
	if(v->left!= NULL && w->right){
		if(w== v->left && u== w->right){
			if(v->parent!= NULL){
				p= v->parent;
				if(p->right!= NULL){
					if(p->right== v){
						p->right= u;
					}
					else{
						p->left= u;
					}
				}
				else{
					p->left= u;
				}
				
				if(u->left!= NULL){
					u->left->parent= w;
					w->right= u->left;
				}
				else{
					w->right= NULL;
				}
				
				if(u->right!= NULL){
					u->right->parent= v;
					v->left= u->right;
				}
				else{
					v->left= NULL;
				}
				
				u->left= w;
				u->right= v;
				
				u->parent= p;
				v->parent= u;
				w->parent= u;
			}
			else{
				if(u->left!= NULL){
					u->left->parent= w;
					w->right= u->left;
				}
				else{
					w->right= NULL;
				}
				
				if(u->right!= NULL){
					u->right->parent= v;
					v->left= u->right;
				}
				else{
					v->left= NULL;
				}
				
				u->left= w;
				u->right= v;
				
				tree->root= u;
				u->parent= NULL;
				v->parent= u;
				w->parent= u;
			}
			return(u);
		}
	}
	if(v->left!= NULL && w->left!= NULL){
		if(w== v->left && u== w->left){
			if(v->parent!= NULL){
				p= v->parent;
				if(p->right!= NULL){
					if(p->right== v){
						p->right= w;
					}
					else{
						p->left= w;
					}
				}
				else{
					p->left= w;
				}
				if(w->right!= NULL){
					w->right->parent= v;
					v->left= w->right;
				}
				else{
					v->left= NULL;
				}
				w->left= u;
				w->right= v;
					
				w->parent= p;
				v->parent= w;
				u->parent= w;
			}
			else{
				if(w->right!= NULL){
					w->right->parent= v;
					v->left= w->right;
				}
				else{
					v->left= NULL;
				}
				w->left= u;
				w->right= v;
				
				tree->root= w;
				w->parent= NULL;
				v->parent= w;
				u->parent= w;
			}
			return(w);
		}
	}
	return(v);
}

void rebalance(avl_tree_t* tree, avl_node_t* node){
	
	avl_node_t* curr, *v, *w, *u;
	bool balance;
	int i=0;
	
	curr= node;
	while(i==0){
		update_height(curr);
		balance= is_balanced(tree, curr);
		if(balance== false){
			v= curr;
			w= rebalancing_child(curr);
			if(w== NULL){
				w= v->right;
			}
			
			u= rebalancing_child(w);
			if(u== NULL){
				if(w== v->right){
					u= w->right;
				}
				else{
					u= w->left;
				}
			}
			curr= reconstruct(tree, v, w, u);
			update_height(curr->right);
			update_height(curr->left);
			update_height(curr);
			if(curr->parent== NULL){
				i++;
			}
		}
		else{
			if(curr->parent== NULL){
				i++;
		    }
			if(curr->parent!= NULL){
				curr= curr->parent;
			}
		}
	}
}

avl_tree_t* create_tree(comparator_t cmp, printer_t printer, int height_diff) {
	avl_tree_t* tree;
	
	tree = (avl_tree_t*)malloc(sizeof(avl_tree_t));
	if(!tree){
		exit(-1);
	}
	tree->root = NULL;
	tree->size = 0;
	tree->cmp = cmp;
	tree->printer = printer;
	tree->height_diff= height_diff;
	return tree;
}

void clear_node(avl_tree_t* tree, avl_node_t* node) {
  if(!node){
    return;
  }
  clear_node(tree, node->left);
  clear_node(tree, node->right);
  rmv(tree, node->data);
}


void clear_tree(avl_tree_t* tree) {
	clear_node(tree, tree->root);	
}

void destroy_tree(avl_tree_t* tree) {
	clear_tree(tree);
	free(tree);
}

int size(avl_tree_t* tree) {
	return tree->size;
  
}

avl_node_t* get_sibling(avl_node_t* node) {
	
	if(node->parent == NULL){
		return NULL;
	}
	
	if(node->parent->left == node){
		return node->parent->right;
	}
	
	return node->parent->left;
}

bool is_left_child(avl_node_t* node) {
	
	if(node->parent == NULL){
		return false;
	}
	if(node->parent->left == node){
		return true;
	}
	return false;
}

 bool is_right_child(avl_node_t* node) {
	
	if(node->parent == NULL){
		return false;
	}
	
	if(node->parent->right == node){
		return true;
	}
	
	return false;
}

void swap(avl_node_t* n1, avl_node_t* n2) {
	type_t tmp;
	 
	tmp = n1->data;
	n1->data = n2->data;
	n2->data = tmp;
}

type_t find(avl_tree_t* tree, type_t data) {
	avl_node_t* curr=tree->root;
	type_t zerovalue = {0};
	
	if(tree->root == NULL){
		return zerovalue;
	}
	
	while(curr != NULL) {
		if(tree->cmp(data, curr->data)<0)
			curr = curr->left;
		else if(tree->cmp(data, curr->data)>0)
			curr = curr->right;
		else
			return curr->data;
	}
	if(!curr){
		return zerovalue;
	}
	return curr->data;
}

bool contains(avl_tree_t* tree, type_t data) {
	type_t found;
	
	found = find(tree,data);
	if(tree->cmp(found, data)==0){
		return true;
	}
	return false;
}

bool add(avl_tree_t* tree, type_t data) {
	avl_node_t *curr,*parent,*node;
	
	if(contains(tree,data)){
		return(false);
	}
	curr = tree->root;
	parent = curr;
	while(curr!=NULL){
		parent = curr;
		if(tree->cmp(data, curr->data)<0){
			curr = curr->left;
		}
		else if(tree->cmp(data,curr->data) > 0){
			curr = curr->right;
		}
		else {
			break;
		}
	}
	
	if(!curr){
		curr = parent;
	}
	
	node = (avl_node_t*)malloc(sizeof(avl_node_t));
	if(!node){
		printf("\nMALLOC FAILURE\n");
	}
	node->left = node->right = NULL;
	node->parent = curr;
	node->data = data;
	
	if(curr) {
		if(tree->cmp(data, curr->data)<0)
			curr->left = node;
		else
			curr->right = node;
	}
	else{
		tree->root = node;
	}
	tree->size++;
	rebalance(tree, node);

	return(true);
}

avl_node_t* find_node(avl_tree_t* tree, type_t value) {
	avl_node_t* curr = tree->root;
	avl_node_t* parent = curr;
	
	while(curr != NULL) {
		parent = curr;
		if(tree->cmp(value, curr->data)<0)
			curr = curr->left;
		else if(tree->cmp(value, curr->data)>0)
			curr = curr->right;
		else
			return curr;
	}
	if(!curr)
		return parent;
	return curr;
}

bool update(avl_tree_t* tree, type_t data, type_t new_data) {
	avl_node_t* found=NULL;
	
	if(!contains(tree,data)){
		return(false);
	}
	
	found = find_node(tree,data);
	
	if(!found || tree->cmp(found->data, data)!=0){
		return false;
	}
	
	found->data = new_data;
	return(true);
}

avl_node_t* delete_node(avl_tree_t *tree, avl_node_t* node) {
	
	if(node->left!=NULL && node->right != NULL){
		return NULL;
	}
  
	if(node->left != NULL)
		node->left->parent = node->parent;
	else if(node->right != NULL)
		node->right->parent = node->parent;  
  
	if(tree->root == node)
		tree->root = (node->left != NULL ? node->left : node->right);
	else if(is_left_child(node))
		node->parent->left = (node->left != NULL ? node->left : node->right);
	else
		node->parent->right = (node->left != NULL ? node->left : node->right);
	tree->size--;
  
	if(node->left != NULL){
		return node->left;
	}
	if(node->right != NULL){
		return node->right;
	}
	else {
		return node->parent;
	}
}

avl_node_t* rmv_node(avl_tree_t* tree, avl_node_t* node) {
	avl_node_t* curr;
	avl_node_t* neighbour_node;
	
	if(node->left!=NULL && node->right != NULL) {
		curr = node->right;
		while(curr->left != NULL){
			curr = curr->left;
		}
		swap(node, curr);
		node = curr;
	}
	neighbour_node = delete_node(tree, node);
	free(node);
	return neighbour_node;
}

avl_node_t* rmv_value(avl_tree_t* tree, type_t value) {
	avl_node_t* found;
	avl_node_t* neighbour_node;
	
	found = find_node(tree,value);
	
	if(!found || tree->cmp(found->data, value)!=0){
		return NULL;
	}
	neighbour_node = rmv_node(tree, found);
	return neighbour_node;
}

bool rmv(avl_tree_t* tree, type_t data) {
	avl_node_t* found=NULL, *node;
	
	found = find_node(tree,data);
	if(found->right!= NULL){
		node= found->right;
	}
	else if(found->left!= NULL){
		node= found->left;
	}
	else{
		node= found->parent;
	}
	
	if(rmv_value(tree, data)!=NULL){
		rebalance(tree, node);
		return true;
	}
	return false;
}

void __print_node(FILE* fp, avl_tree_t* tree, avl_node_t* node) {
  if(!node)
    return;
  tree->printer(fp, node->data, true);
  __print_node(fp, tree, node->left);
  __print_node(fp, tree, node->right);
}

void print(FILE* fp, avl_tree_t* tree) {
  __print_node(fp, tree, tree->root);
}

void __dot_print_node(FILE* fp, avl_tree_t* tree, avl_node_t* node) {
  if(!node)
    return;
  fprintf(fp, "  "); 
  tree->printer(fp, node->data, true);
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

void dot_print(FILE* fp, avl_tree_t* tree) {
  fprintf(fp, "graph G {\n");
  __dot_print_node(fp, tree, tree->root);
  fprintf(fp, "}\n");
}
