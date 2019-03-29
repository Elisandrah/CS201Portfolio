#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

enum Color {RED, BLACK};
enum MediaType {dvd, bluray, digital, none};

typedef struct node node;

typedef struct node{

    bool color;
    char *key[256];
    //Chosen as longest movie title was about 200 characters long
    //256 allows more leeway but still large enough
    char *genre[256];
    int runningTime;
    int year;
    bool MediaType;
    time_t dateAcquired;
    node *left;
    node *right;
    node *parent;
    bool found;


}node;

node *Node(char *title, char *genre, int runningTime, int year, bool type, node *left, node *right, node *parent){
    node *newNode = (node *)malloc(sizeof(node));

    strcpy(newNode->key, title);
    strcpy(newNode->genre, genre);
    newNode->runningTime = runningTime;
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

int GetRunningTime(node *movie){
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

void SetGenre(node *movie, char *genre){
    strncpy(movie->genre, genre, 256);
}

void SetRunningTime(node *movie, int time){
    movie->runningTime = time;
}

void SetYear(node *movie, int year){
    movie->year = year;
}

void SetMediaType(node *movie, bool type){
    movie->MediaType = type;
}

void SetDateAcquired(node *movie, time_t date){
    movie->dateAcquired = date;
}

