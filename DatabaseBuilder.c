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
            int runningTime;
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
                        runningTime = atoi(strtok(buffer, '\t'));
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

        if(fp == NULL){
            printf("%s could not be opened\n", name);
            return;
        }

        fputs(GetTitle(movie), fp);
        fputs("\t", fp);

        fputs(GetYear(movie), fp);
        fputs("\t", fp);

        fputs(GetRunningTime(movie), fp);
        fputs("\t", fp);

        fputs(GetGenre(movie), fp);
        fputs("\t", fp);

        fputs(GetMediaType(movie), fp);
        fputs("\t", fp);

        fputs(GetDateAcquired(movie), fp);
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
        flcose(fp);
        UpdateMovie(name, movie);
        return;
    }
    else if (choice < 97){
        choice = choice + 32;
    }
    while(completed == false){
     switch(choice){
         case 'y':
             printf("Enter the desired year, ex(1956): ");
             fgets(buffer, sizeof buffer, stdin);
             int temp = atoi(buffer);

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
            int temp = atoi(buffer);

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
                printf("DVD: Enter \"d\"\n");
                printf("Bluray: Enter \"b\"\n");
                printf("Digital: Enter \"d\"\n");

                char temp = getchar();

                if(temp < 64 || temp > 121 || (temp > 90 && temp < 97)){
                    printf("Invalid character entered, try again\n");
    }
    else if (choice < 97){
        choice = choice + 32;
    }



         case 'd':

         default:
             printf("Invalid character entered, try again\n");
             flcose(fp);
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
            return;
        }

        while(!feof(fp)){
            fgets(buffer, sizeof buffer, fp);
            strncpy(check, strtok(buffer, "\t"), 256);
            if(strncmp(check, movieTitle, 256) == 0){
                found = true; 
                //do nothing with that string, deletes it
            }
            else
                fputs(buffer, fp);

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
            fclose("new");
            remove("new");
            //Add this print statement to the runner program
            printf("%s could not be found within the logfile, please try again\n", movieTitle);
            return 2;
        }        
}

void RemoveLogFile(char *name){
        FILE *fp = fopen(name, "w");

        if(fp == NULL){
            printf("%s could no be opened\n", name);
            return;
        }

        fclose(fp);
        remove(name);

        printf("%s has been removed", name);
        return;
}