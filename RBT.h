#include <stdio.h>
#include <stdlib.h>
#include "Node.c"

typedef struct rbt RBT;

extern RBT *newRBT();
node* RBTInsert(char *title, RBT *tree);
void Fixup(node *root, node *p);
void RotateLeft(node *root, node *p);
void RotateRight(node *root, node *p);