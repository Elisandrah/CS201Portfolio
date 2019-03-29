//Will write at a later time
#ifndef Node
#include "node.c"
#endif
#ifndef RBT
#include "RBT.h"
#endif
#include "DatabaseBuilder.c"


int main(int argc, char **argv){

    bool running = true;
    RBT *database = CreateDatabase();


    while(running = true){
        printf("Welcome to your personal IMDB Catalog!\n");
        running = false;        
    }
    return 0;
}