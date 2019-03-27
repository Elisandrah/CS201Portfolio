#include "RBT.h"
#include <stdio.h>
#include <stdlib.h>

//Will write at a later time. This will be the file that loads
//in all of the movies and puts them in the RBT

RBT *CreateDatabase(){
    RBT *database = newRBT();
    FILE *fp = fopen("movie_records", "r");
    

    if(fp == NULL){
        printf("File \"movie_records\" not found\n");
        return NULL;
    }

    while(!feof(fp)){
            char *buffer = (char *)malloc(2400*sizeof(char));
            char *title = (char *)malloc(256*sizeof(char));;
            char *genre = (char *)malloc(256*sizeof(char));
            char *runningTime = (char *)malloc(50*sizeof(char));
            int year;


            //Should be large enough to read in each line
            //256 size of each title and others are shorter than that

            fgets(buffer, sizeof buffer, fp);
            for(int i = 0; i < 8; i++){ //Only 9 tokens per line
                switch (i)
                {
                    case 2:
                        strncpy(title, strtok(buffer, '\t'), 256);
                        break;

                    case 5:
                        year = atoi(strtok(buffer, '\t'));
                        break;

                    case 7:
                        strncpy(runningTime, strtok(buffer, '\t'), 50);
                        break;

                    case 8:
                        strncpy(genre, strtok(buffer, '\t'),256);
                        break;
                
                    default:
                        strtok(buffer, '\t');
                        break;
                }
            }
            RBTInsert(title, genre, runningTime, year, database);

    }
}

void CreateLogFile(char *name){
        strcat(name, ".log");

        FILE *fp = fopen(name, "w");

        if(fp == NULL){
            printf("File could not be opened\n");
            return;
        }

        fclose(fp);
}

void AddToLogFile(char *name, node *movie){
        
        FILE *fp = fopen(name, "a");

        


}
