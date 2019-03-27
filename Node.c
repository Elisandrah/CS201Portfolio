#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum Color {RED, BLACK};
enum MediaType {dvd, bluray, digital, none};

typedef struct node{

    bool color;
    char *key[256];
    //Chosen as longest movie title was about 200 characters long
    //256 allows more leeway but still large enough
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

char GetTitle(node *movie){
    return movie->key;
}

char GetGenre(node *movie){
    return movie->genre;
}

char GetRunningTime(node *movie){
    return movie->runningTime;
}

int GetYear(node *movie){
    return movie->year;
}

bool GetMediaType(node *movie){
    return movie->MediaType;
}

time_t GetDateAcquired(node *movie){
    return movie->dateAcquired;
}
