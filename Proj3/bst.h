
#if !defined(__BST_CSCI303)
#define __BST_CSCI303

#include <stdbool.h>

typedef char* KEY;
typedef char* VALUE;

// LNODE is the data structure for a singly linked list.
typedef struct lnode {
  VALUE val;          // A pointer to the value stored in the linked list.
  struct lnode *next; // Pointer to the next item in the list; it should be NULL if there is no successor.
} LNODE;

typedef struct tnode {
  KEY key;             // Search key for this binary search tree node.
  struct tnode *right; // Right child.
  struct tnode *left;  // Left child.

  LNODE *head; // Head of the linked list storing the values for the search key.
  LNODE *tail; // Tail of the linked list storing the values for the search key.

  bool is_red; // Flag use only in red-black trees to denote redness.
} TNODE;

// Public API.
TNODE *tree_add(TNODE*, const KEY, const VALUE);
TNODE *tree_find(TNODE*, const KEY);
int height (const TNODE* const);
void nuke_tree(TNODE*);

// Internal BST functions.
TNODE *talloc(const KEY k);
LNODE *lalloc(const VALUE v);

// Internal red-black tree functions.
TNODE *rotate_left (TNODE *h);
TNODE *rotate_right (TNODE *h);
void flip_colors(TNODE *p);
bool is_red(const TNODE *p);

#endif