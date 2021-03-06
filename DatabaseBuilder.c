#ifndef RBT
#include "RBT.h"
#endif
#ifndef Node
#include "node.c"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
            int runningTime;
            int year;


            //Should be large enough to read in each line
            //256 size of each title and others are shorter than that

            fgets(buffer, sizeof buffer, fp);
            for(int i = 0; i < 8; i++){ //Only 9 tokens per line
                switch (i)
                {
                    case 2:
                        strncpy(title, strtok(buffer, "\t"), 256);
                        break;

                    case 5:
                        year = atoi(strtok(buffer, "\t"));
                        break;

                    case 7:
                        runningTime = atoi(strtok(buffer, "\t"));
                        break;

                    case 8:
                        strncpy(genre, strtok(buffer, "\t"),256);
                        break;
                
                    default:
                        strtok(buffer, "\t");
                        break;
                }
            }
            RBTInsert(title, genre, runningTime, year, database);

    }

    return database;
}

int CreateLogFile(char *name){
        strcat(name, ".log");

        FILE *fp = fopen(name, "w");

        if(fp == NULL){
            printf("File could not be opened\n");
            return 1;
        }

        return 0;

        fclose(fp);
}

void Alphabetize(char *name){
        FILE *fp = fopen(name, "w");

        if(fp == NULL){
            return;
        }

        //Write this if time permits

}

void AddToLogFile(char *name, node *movie){
        
        FILE *fp = fopen(name, "a");
        MediaType type;

        if(fp == NULL){
            printf("%s could not be opened\n", name);
            return;
        }

        fputs(GetTitle(movie), fp);
        fputs("\t", fp);

        fprintf(fp, "%d", GetYear(movie));
        fputs("\t", fp);

        fprintf(fp, "%d", GetRunningTime(movie));
        fputs("\t", fp);

        fputs(GetGenre(movie), fp);
        fputs("\t", fp);

        type = GetMediaType(movie);
        switch (type)
        {
            case dvd:
                fputs("DVD", fp);
                fputs("\t", fp);
                break;

            case bluray:
                fputs("Bluray", fp);
                fputs("\t", fp);
                break;

            case digital:
                fputs("Digital", fp);
                fputs("\t", fp);
                break;

            default:
                fputs("Not Specified", fp);
                fputs("\t", fp);
                break;
        }
        time_t time;
        time = ((GetDateAcquired(movie)));
        fputs(ctime(&time), fp);
        fputs("\n", fp);

        fclose(fp);
        return;
}

void UpdateMovie(char *name, node *movie){
    FILE *fp  = fopen(name, "w");

    char choice;
    char buffer[256]; //size of largest element to edit
    bool completed = false;

    if(fp == NULL){
        printf("%s could not be opened\n", name);
        return;
    }

    printf("Choose what you would like to edit for the %s:\n", GetTitle(movie));
    printf("Year: Enter \"y\"\n");
    printf("Running Time: Enter \"r\"\n");
    printf("Genre: Enter \"g\"\n");
    printf("Media Type: Enter \"m\"\n");
    printf("Date Acquired: Enter \"d\"\n");

    choice = getchar();
    
    if(choice < 64 || choice > 121 || (choice > 90 && choice < 97)){
        printf("Invalid character entered, try again\n");
        fclose(fp);
        UpdateMovie(name, movie);
        return;
    }
    else if (choice < 97){
        choice = choice + 32;
    }
    int temp;
    while(completed == false){
     switch(choice){
         case 'y':
             printf("Enter the desired year, ex(1956): ");
             fgets(buffer, sizeof buffer, stdin);
             temp = atoi(buffer);

             if(temp == 0 || temp < 0){ 
                printf("Invalid year entered, try again\n");
                break;
             }
             else
             {
                SetYear(movie, temp);
                completed = true;
             }
             break;

         case 'r':
            printf("Enter the desired Running Time in minutes, ex(74)");
            fgets(buffer, sizeof buffer, stdin);
            temp = atoi(buffer);

            if(temp == 0 || temp < 0){ 
                printf("Invalid year entered, try again\n");
                break;
             }
             else{
                    SetRunningTime(movie, temp);
                    completed = true;
             }
            break;

         case 'g':
                printf("Enter the desired Genres, ex(Action, Drama)");
                fgets(buffer, sizeof buffer, stdin);

                SetGenre(movie, buffer);
                break;

         case 'm':
                printf("Enter which Media Type:\n");
                printf("DVD: Enter \"v\"\n");
                printf("Bluray: Enter \"b\"\n");
                printf("Digital: Enter \"d\"\n");

                char tempc = getchar();

            if(tempc < 64 || tempc > 121 || (tempc > 90 && tempc < 97)){
                printf("Invalid character entered, try again\n");
             }
            else if (tempc < 97){
                tempc = tempc + 32;
            }
            else{
                if(tempc == 'v'){
                    SetMediaType(movie, dvd);
                    completed = true;
                }
                else if(tempc == 'b'){
                    SetMediaType(movie, bluray);
                    completed = true;   
                }
                 else if(tempc == 'd'){
                    SetMediaType(movie, digital);
                    completed = true;   
                }
                else
                {
                    printf("Incorrect choice, please try again\n");
                    break;
                }
            }
            break;

         case 'd':
           //D:
            break; 

         default:
            printf("Invalid character entered, try again\n");
            fclose(fp);
            UpdateMovie(name, movie);
            return;
        }
    }
}

int RemoveFromLogFile(char *name, char *movieTitle){
        
        FILE *fp = fopen(name, "w");
        FILE *new = fopen("new", "w");

        char buffer[2400]; //large enough for any line
        char check[256]; //large enough for any title
        bool found = false;

        if(fp == NULL){
            printf("%s could not be oepened\n", name);
            return 2;
        }

        while(!feof(fp)){
            fgets(buffer, sizeof buffer, fp);
            strncpy(check, strtok(buffer, "\t"), 256);
            if(strncmp(check, movieTitle, 256) == 0){
                found = true; 
                //do nothing with that string, deletes it
            }
            else
                fputs(buffer, new);

        }

        if(found == true){
            fclose(fp);
            remove(name);

            rename("new", name);
            fclose(new);
            //Add this print statement to the runner program
            printf("%s has been removed from the logfile\n", movieTitle);
            return 1;
        }
        else
        {
            fclose(new);
            remove("new");
            //Add this print statement to the runner program
            printf("%s could not be found within the logfile, please try again\n", movieTitle);
            return 2;
        }        
}

void RemoveLogFile(char *name){
        FILE *fp = fopen(name, "w");

        if(fp == NULL){
            printf("%s could not be opened\n", name);
            return;
        }

        fclose(fp);
        remove(name);

        printf("%s has been removed", name);
        return;
}

void DisplayLogFile(char *name){
    FILE *fp = fopen(name, "r");
    char buffer[2400];

    if(fp == NULL){
        printf("%s could not be opened\n", name);
        return;
    }

    printf("'\t''\t''\t'%s\n\n", name);

    while(!feof(fp)){
        fgets(buffer, 2400, fp);
        printf("%s", buffer);
        printf("\n");
    }
    return;
}