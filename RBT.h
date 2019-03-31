#ifndef Node
#include "Node.c"
#endif
#ifndef RBT
#define RBT_H
#include <stdio.h>
#include <stdlib.h>

typedef struct RBT{
    node *root;

}RBT;

RBT *newRBT();
void RBTInsert(char *title, char *genre, int runningTime, int year, RBT *tree);
void Fixup(node *root, node *p);
void RotateLeft(node *root, node *p);
void RotateRight(node *root, node *p);
node *search(char *title, RBT *tree);

#endif