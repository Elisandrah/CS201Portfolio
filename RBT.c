#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RBT.h"

//Code adapted from https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/
//Used as template and ajusted to work within design choices

typedef struct RBT{
    node *root;

}RBT;

RBT *newRBT(){
    RBT *newRBT = (RBT *)malloc(sizeof(RBT));

    newRBT->root = NULL;
}

void *RBTInsert(char *title, char *genre, int runningTime, int year, RBT *tree){
    node *newNode = Node(title, genre, runningTime, year, none, NULL, NULL, NULL);

    tree->root = InsertHelper(tree->root, newNode);

    Fixup(tree->root, newNode);
}

node *InsertHelper(node *root, node *p){
    if(root == NULL)
        return p;

    if(strcmp(root->key, p->key) <= 0){
        root->left = InsertHelper(root->left, p);
        root->left->parent = root;
    }
    else if(strcmp(root->key, p->key) > 0){
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

node *search(char *title, RBT *tree){
    node *current = tree->root;
    //Replace strcmp with strncmp and other instances
    while(current != NULL){
        if(strcmp(title, current->key) == 0 && current->found == false){
            break;
        }
        else if(strcmp(title, current->key) < 0){
            if(current->left == NULL)
                break;
            else
                current = current->left;
        }
        else
            if(current->right == NULL)
                break;
            else
                current = current->right;
        }

    current->found = true;
    return current;

    //Current will ensure all options are found and listed when searched for
    //After choice is selected built list of nodes will have found reset
}