#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "bst.h"


// Public API.

bool red_black_tree;

// create space for linked-list node
TNODE *tree_add(TNODE*p, const KEY k, const VALUE v) {
    int cond;
   
    if (p == NULL){
        LNODE *headlist = lalloc(v);
        p = talloc(k);
        p->left = NULL;
        p->right = NULL;
        p->head = headlist;
        p->tail = headlist;
	p->is_red = true;
        return (p);
    }
   
    else if((cond = strcmp(k, p->key)) == 0){
        LNODE *new_item = lalloc(v);
        p->tail->next = new_item;
        p->tail = new_item;
    }
    else if (cond < 0){
        p->left = tree_add(p->left, k ,v);
    }
    else{
        p->right = tree_add(p->right, k ,v);
    }
    if (red_black_tree == true){
        if (is_red(p->right) && !(is_red(p->left)))
            p = rotate_left(p);
        if (is_red(p->left) && is_red(p->left->left))
            p = rotate_right(p);
        if (is_red(p->left) && is_red(p->right))
            flip_colors(p);
    }
    return p;
}
  

TNODE *tree_find(TNODE *p, const KEY k) {
	if (p == NULL || p->key == k)
		return p;
	if (strcmp(k, p->key) < 0)
		tree_find(p->left, k);
	else
		tree_find(p->right, k);
}

int height (const TNODE* const p) {
  
	if (p == NULL) { return; }
	else {
	long int HL = height(p->left);
	long int HR = height(p->right);
	if (HL <= HR)
		return HL + 1;
	else
		return HR + 1;
	}
}

void nuke_tree(TNODE*p) {
  
  if (!p) { return; }
  nuke_tree(p->left);
  nuke_tree(p->right);
  free(p);
  
  
  //hail satan
  /*if (p == NULL) {
    return;
  }
  
  else {
    
    
    
    
    
    
    
    while (p->head != NULL) {
      LNODE *temp = p;
      p = p->tail;
      free(temp);
    }
    LNODE *temp2 = p;
    p = p->tail;
    free(temp2);
    free(p);
    if (p->left == NULL && p->right == NULL)
      free(p);    
    else {
      //TNODE temp = *p;
      nuke_tree(p->left);
      nuke_tree(p->right);
      free(p);
    } */
  }

int number (TNODE *p) {
  if (p == NULL) {
    return 0;
  }
  
  else {
    if (p->left == NULL && p->right == NULL) {
      return 1;
    }
    else {
      return (1 + (number(p->left)) + (number(p->right)));
    }
  }
}

// Internal BST functions.
TNODE *talloc(const KEY k) {
	TNODE *p = (TNODE*)malloc(sizeof(TNODE));
	int length = strlen(k) + 1;
	
	
	
	//if (NULL == t)
	//return NULL;
	//allocate memory for copy of k, thencopy k into, be sure to pass in pointer
	//len, cpy
	//length not included by 1, always add one byte
	char *new = (char *)malloc(sizeof(char) * length);
	new = strcpy(new, k);
	
	p->key = new;
	p->is_red = false;
	p->left = NULL;
	p->right = NULL;
	//t->head = NULL;
	//t->tail = NULL;
	return p;
}
	
LNODE *lalloc(const VALUE v) {
	LNODE *p = (LNODE*)malloc(sizeof(LNODE));
	
	int length = strlen(v) + 1;
	
	//if (NULL == t)
	//return NULL;
	char *new = (char *)malloc(sizeof(char) * length);
	new = strcpy(new, v);
	p->val = new;
	//t->is_red = false;
	p->next = NULL;
	//t->left = NULL;
	//t->right = NULL;
	//t->head = NULL;
	//t->tail = NULL;
	return p;
}

// Internal red-black tree functions.
TNODE *rotate_left (TNODE *h) {
	//performs a red-black left rotation at the top of the subtree rooted at *h
	TNODE *x = h->right;
	h->right = x->left;
	x->left = h;
	x->is_red = h->is_red;
	h->is_red = true;
	// x->N = h->N;
	// h->N = 1 + sizeof(h->left) + sizeof(h->right);
	return x;
}
	
TNODE *rotate_right (TNODE *h) {
	//performs a red-black right rotation at the top of the subtree rooted at *h
	TNODE *x = h->left;
	//666
	h->left = x->right;
	x->right = h;
	x->is_red = h->is_red;
	h->is_red = true;
	// x->N = h->N;
	// h->N = 1 + sizeof(h->left) + sizeof(h->right);
	return x;
}
	
void flip_colors(TNODE *p) {
	//flips color of speciified node
	//TNODE RED, BLACK;
	p->is_red = true;
	p->left->is_red = false;
	p->right->is_red = false;
}

bool is_red(const TNODE *p) {
	if (p == NULL) { return false; }
	//666
	else { return p->is_red;}
}

/*void print_tree(TNODE *p) {
    if(p == NULL)
    {
        printf("Print exit\n");
        return;
    }
    else
    {
        printf("%d\n",p);
        print_tree(&(p->left));
        print_tree(&(p->right));
    }
}*/

//int main() { return 0; }

