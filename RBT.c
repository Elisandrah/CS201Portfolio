#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RBT.h"
//Declare a standard NIL node that all NULLS will point to

//Code adapted from https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
//Used as template and ajusted to work within design choices

typedef struct RBT{
    node *root;

}RBT;

RBT *newRBT(){
    RBT *newRBT = (RBT *)malloc(sizeof(RBT));

    newRBT->root = NULL;
}

node *RBTInsert(char *title, RBT *tree){
    node *newNode = Node(title, NULL, NULL, NULL);

    tree->root = RBTInsert(tree->root, newNode);

    Fixup(tree->root, newNode);
}

node *InsertHelper(node *root, node *p){
    if(root == NULL)
        return p;

    if(p->key < root->key){
        root->left = InsertHelper(root->left, p);
        root->left->parent = root;
    }
    else if(p->key > root->key){
        root->right = InsertHelper(root->right, p);
        root->right->parent = root;
    }

    return root;
}

void RotateRight(node *root, node *p){
    node *pleft = p->left;

    p->left = pleft->right;

    if(p->left != NULL)
        p->left->parent = p;

    pleft->parent = p->parent;

    if(p->parent == NULL)
        root = pleft;
    else if(p == p->parent->left)
        p->parent->left = pleft;
    else
        p->parent->right = pleft;

    pleft->right = p;
    p->parent = pleft;
}

void RotateLeft(node *root, node *p){
    node *pright = p->right;

    p->right = pright->left;

    if(p->right != NULL)
        p->right->parent = p;

    pright->parent = p->parent;

    if(p->parent == NULL)
        root = pright;
    else if(p == p->parent->left)
        p->parent->left = pright;
    else
        p->parent->right = pright;

    pright->left = p;
    p->parent = pright;
}

void Swap(node *one, node *two){
    bool oneColor = one->color;
    bool twoColor = two->color;

    one->color = twoColor;
    two->color = oneColor;
}

void Fixup(node *root, node *p){
    node *pparent = NULL;
    node *pgrandparent = NULL;

    while ((p != root) && (p->color != BLACK) && (p->parent->color == RED)){
        pparent = p->parent;
        pgrandparent = p->parent->parent;

        if(pparent == pgrandparent->left){
            node *puncle = pgrandparent->right;

            if(puncle != NULL && puncle->color == RED){
                pgrandparent->color = RED;
                pparent->color = BLACK;
                puncle->color = BLACK;
                p = pgrandparent;
            }
            else{
                if(p == pparent->right){
                    RotateLeft(root, pparent);
                    p = pparent;
                    pparent = p->parent;
                }

                RotateRight(root, pgrandparent);
                Swap(pparent, pgrandparent);
                p = pparent;
            }
        }
        else{
            node *puncle = pgrandparent->left;

            if((puncle != NULL) && (puncle->color == RED)){
                pgrandparent->color = RED;
                pparent->color = BLACK;
                puncle->color = BLACK;
                p = pgrandparent;
            }
            else
            {
                if(p == pparent->left){
                    RotateRight(root, pparent);
                    p = pparent;
                    pparent = p->parent;
                }

                RotateLeft(root, pgrandparent);
                Swap(pparent, pgrandparent);
                p = pparent;
            }
        }
    }
    root->color = BLACK;    
}

