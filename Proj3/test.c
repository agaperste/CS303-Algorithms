
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bst.h"

#define MAXWORD 128
#define MAXLINE 32768

bool red_black_tree;
TNODE *root;

int main()
{
  char line[MAXLINE];
  char copy[MAXLINE];
  char *sep = " ";

  red_black_tree = true;

  root = NULL;
  while (fgets(line, MAXLINE, stdin) != NULL) {
    // Copy the line and remove non-alphabetic characters other than hyphens.
    strcpy(copy, line);
    if (copy[0] != '\0') {
      for (int i = 0; i < strlen(copy); i++) {
	if (!isalnum(copy[i]) && (copy[i] != '-')) {
	  copy[i] = ' ';
	}
      }

      // Now read the words in the line.
      char *word = strtok(copy, sep);
      while (word != NULL) {
	if (isalpha(word[0])) {
	  root = tree_add(root, word, line);
	  root->is_red = false; /* The root is always black. */
	}
	word = strtok(NULL, sep);
      }
    }
  }

  fprintf(stderr, "height: %d\n", height(root));
  nuke_tree(root);
  return(0);
}
