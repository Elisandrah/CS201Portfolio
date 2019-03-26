#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum Color {RED, BLACK};
enum MediaType {dvd, bluray, digital, none};

typedef struct node{

    bool color;
    char *key[256];
    char *genre[256];
    char runningTime[50];
    int year;
    bool MediaType;
    time_t dateAcquired;
    node *left;
    node *right;
    node *parent;
    bool found;


}node;

node *Node(char *title, char *genre, char *runningTime, int year, bool type, node *left, node *right, node *parent){
    node *newNode = (node *)malloc(sizeof(node));

    strcpy(newNode->key, title);
    strcpy(newNode->genre, genre);
    strcpy(newNode->runningTime, runningTime);
    newNode->year = year;
    newNode->left = left;
    newNode->right = right;
    newNode->parent = parent;
    newNode->color = RED;
    newNode->dateAcquired = time(NULL);
    newNode->found = false;
    
}