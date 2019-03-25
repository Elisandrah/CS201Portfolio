#include <stdio.h>
#include <stdlib.h>

enum Color {RED, BLACK};

typedef struct node{

    bool color;
    char *key[256];
    node *left;
    node *right;
    node *parent;


}node;

node *Node(char *title, node *left, node *right, node *parent){
    node *newNode = (node *)malloc(sizeof(node));

    newNode->key = title;
    newNode->left = left;
    newNode->right = right;
    newNode->parent = parent;
    newNode->color = RED;
}