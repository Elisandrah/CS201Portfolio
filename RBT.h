#ifndef Node
#include "Node.c"
#endif
#include <stdio.h>
#include <stdlib.h>

typedef struct RBT{
    node *root;

}RBT;

extern RBT *newRBT();
void RBTInsert(char *title, char *genre, int runningTime, int year, RBT *tree);
void Fixup(node *root, node *p);
void RotateLeft(node *root, node *p);
void RotateRight(node *root, node *p);
void RBTDelete();
node *search(char *title, RBT *tree);
