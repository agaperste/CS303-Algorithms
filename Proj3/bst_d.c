//Nate Marshall and Diego Lanao pair programmed this project
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bst.h"


extern bool red_black_tree;


LNODE *lalloc (const VALUE v) {
    LNODE *newnode = (LNODE *) malloc(sizeof(LNODE));
    if (NULL == newnode) { return NULL;}
    newnode->val = malloc((strlen(v)+1)*sizeof(char));
    strcpy(newnode->val, v);
    newnode->next = NULL;
    return newnode;
}

TNODE *talloc(const KEY k) {
    TNODE *newnode = (TNODE *) malloc(sizeof(TNODE));
    if (NULL == newnode) {return NULL;}
    newnode->key = malloc((strlen(k)+1)*sizeof(char));
    strcpy(newnode->key, k);
    newnode->head = NULL;
    newnode->tail = NULL;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->is_red = true;
    return newnode;
}

//create space for linked list node
TNODE *tree_add(TNODE *p, const KEY k, const VALUE v) {
    int cond;
    
    //the first if else if pair could be a conflict?
    if (p == NULL) {    /* a new word has arrived */
    //the node doesn't exist
        TNODE *newnode = talloc(k);
        newnode->left = newnode->right = NULL;
        LNODE *tmp = lalloc(v);
        newnode->head = tmp;
        newnode->tail = tmp;

        return newnode;
    }

    if ((cond = strcmp(k, p->key)) == 0) {
        //we are at it
        //Is this the right place to put this code????????????????????????????????//
        

        LNODE *tmp = lalloc(v);
        p->tail->next = tmp;
        p->tail = tmp;
        return p;
        
    } else if (cond < 0) {    
        p->left = tree_add(p->left, k, v);
    
    } else {
        p->right = tree_add(p->right, k, v);
    }
    
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
    if (p == NULL) {
        return p;
    }
    if (strcmp(k, p->key) == 0) {
        //you have arrived at the word
        return p;

    } else if (strcmp(k, p->key) > 0) {
        //go right
        tree_find(p->right, k);
    } else if (strcmp(k, p->key) < 0) {
        //go left young man, go left
        tree_find(p->left, k);
    }
}

void treeprint( TNODE *p) {
    if (p != NULL) {
        treeprint(p->left);
        printf("%s \n", p->key);
        treeprint(p->right);
    }
}

int height(const TNODE *p) {
    if (p == NULL) {
        return 0;
    } else {
        int left_depth = height(p->left);
        int right_depth = height(p->right);

        if (left_depth > right_depth){
            if (p->right == NULL && p->left == NULL){
                return(left_depth);
            }
            return(left_depth + 1);
            
        } else {
            if (p->right == NULL && p->left == NULL){
                return(right_depth);
            }
            return(right_depth + 1);
        }
    }
}

void nuke_tree(TNODE *p) {
    if (p != NULL) {
        TNODE *left_child = p->left;
        TNODE *right_child = p->right;
        LNODE *cur_node = p->head;
        while (cur_node != NULL) {
            LNODE *next_node = cur_node->next;
            free(cur_node->val);
            free(cur_node);
            cur_node = next_node;
        }
        free(p->key);
        free(p);
        nuke_tree(left_child);
        nuke_tree(right_child);
    }
}

TNODE *rotate_left(TNODE *h) {
    TNODE *x = h->right;
    h->right = x->left;
    x->left = h;
    x->is_red = h->is_red;
    h->is_red = true;
    return x;
}

TNODE *rotate_right(TNODE *h) {
    TNODE *x = h->left;
    h->left = x->right;
    x->right = h;
    x->is_red = h->is_red;
    h->is_red = true;
    return x;
}

void flip_colors(TNODE *p) {
    p->is_red = true;
    p->left->is_red = false;
    p->right->is_red = false;
}

bool is_red(const TNODE *p) {
    if (p == NULL){
        return false;
    }
    
    if(p->is_red == true) {
        return true;
    
    } else {
        return false;
    }
}