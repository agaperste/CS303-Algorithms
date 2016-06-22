//author: Yingzhu (Jacqueline) Zhang 

//after thought of the author:
//tis a hard project, indeed.
//But, Happy Halloween!

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#include "bst.h"


extern bool red_black_tree;


/* Public API */

TNODE *tree_add(TNODE *p, const KEY k, const VALUE v) {
    int cond;
    
    //if the node doesn't exist
    if (p == NULL) { 
        TNODE *new_node = talloc(k);
        new_node->left = new_node->right = NULL;
        LNODE *tmp = lalloc(v);
        new_node->head = tmp;
        new_node->tail = tmp;

        return new_node;
    }

    //if we are at the node
    //reg BST
    if ((cond = strcmp(k, p->key)) == 0) {
        LNODE *tmp = lalloc(v);
        p->tail->next = tmp;
        p->tail = tmp;
        return p;
        
    } 
    else if (cond < 0) {    
        p->left = tree_add(p->left, k, v);
    } 
    else {
        p->right = tree_add(p->right, k, v);
    }
    //RBT
    if (red_black_tree == true) {
            if (is_red(p->right) && !is_red(p->left)) {
                p = rotate_left(p);
            }

            if (is_red(p->left) && is_red(p->left->left)) {
                p = rotate_right(p);
            }

            if (is_red(p->left) && is_red(p->right)) {
                flip_colors(p);
            }
        }

    return p;
}

TNODE *tree_find(TNODE *p, const KEY k) {
    //if the node doesn't exist
    if (p == NULL) {
        return p;
    }
    //go right
    if (strcmp(k, p->key) > 0) {
        tree_find(p->right, k);
    } 
    //go left
    else if (strcmp(k, p->key) < 0) {
        tree_find(p->left, k);
    }
    //if we are at it
    else if (strcmp(k, p->key) == 0) {
        return p;
    } 
}

int height(const TNODE *p) {
    //if the node doesn't exist
    if (p == NULL) {
        return 0;
    } else {
        int ldepth = height(p->left);
        int rdepth = height(p->right);

        if (ldepth > rdepth){
            if (p->right == NULL && p->left == NULL){
                return(ldepth);
            }
            return(ldepth + 1);
            
        } else {
            if (p->right == NULL && p->left == NULL){
                return(rdepth);
            }
            return(rdepth + 1);
        }
    }
}


void nuke_tree(TNODE *p) {
    //if the tree isn't null
    if (p != NULL) {
        TNODE *lchild = p->left;
        TNODE *rchild = p->right;
        LNODE *cur = p->head;

        while (cur != NULL) {
            LNODE *next = cur->next;
            free(cur->val);
            free(cur);
            cur = next;
        }

        free(p->key);
        free(p);
        nuke_tree(lchild);
        nuke_tree(rchild);
    }
}


/* Internal BST functions */

LNODE *lalloc (const VALUE v) {
    LNODE *new_node = (LNODE *) malloc(sizeof(LNODE));
    if (NULL == new_node) { 
        return NULL;
    }
    new_node->val = malloc((strlen(v)+1)*sizeof(char));
    strcpy(new_node->val, v);
    new_node->next = NULL;
    
    return new_node;
}

TNODE *talloc(const KEY k) {
    TNODE *new_node = (TNODE *) malloc(sizeof(TNODE));
    if (NULL == new_node) {
        return NULL;
    }
    new_node->key = malloc((strlen(k)+1)*sizeof(char));
    strcpy(new_node->key, k);
    new_node->head = NULL;
    new_node->tail = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->is_red = true;

    return new_node;
}


/* Internal red-black tree functions. */

//Performs a red-black left rotation at the 
//top of the subtree rooted at *h
TNODE *rotate_left(TNODE *h) {
    TNODE *r = h->right;
    h->right = r->left;
    r->left = h;
    r->is_red = h->is_red;
    h->is_red = true;
    return r;
}

//Performs a red-black right rotation at the 
//top of the subtree rooted at *h
TNODE *rotate_right(TNODE *h) {
    TNODE *r = h->left;
    h->left = r->right;
    r->right = h;
    r->is_red = h->is_red;
    h->is_red = true;
    return r;
}

//flips color of the speciified node
void flip_colors(TNODE *p) {
    p->is_red = true;
    p->left->is_red = false;
    p->right->is_red = false;
}

//check if is red
bool is_red(const TNODE *p) {
    if (p == NULL){
        return false;
    }
    if(p->is_red == true) {
        return true;
    } 
    else {
        return false;
    }
}


/* Helper function */ 

//print the tree
void print_tree(TNODE *p) {
    if(p == NULL){
        printf("You don't have a tree.\n");
        return;
    }
    else{
        print_tree(p->left); 
        printf("%s \n", p->key);
        print_tree(p->right);
    }
}
