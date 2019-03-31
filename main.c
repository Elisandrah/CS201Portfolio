//Will write at a later time
#include "DatabaseBuilder.c"
#ifndef Node
#include "node.c"
#endif

int main(int argc, char **argv){

    if(argc == 1){
        printf("No arguments given, Exiting program");
        return -1;
    }

    bool running = true;
    RBT *database = CreateDatabase();
    char input[256];
    char name[256];
    char choice;
    char s1[5] = ".log";


    while(running == true){
        printf("Welcome to your personal IMDB Catalog!\n");
        printf("What would you like to do: \n");
        printf("1: Create Log\n");
        printf("2: Delete Log\n");
        printf("3: Modify Log\n");
        printf("4: Exit Catalog\n");

        scanf("%c", &choice);
        printf("\n");

        switch(input[0]){
            case '1':
            printf("Enter your name: ");
            scanf("%s", &input);
            printf("\n");
            if(CreateLogFile(input) == 0){
                printf("Log File successfully created.\n");
            }
            break;

            case '2':
            printf("Enter the name of the logfile: ");
            scanf("%s", &input);
            printf("\n");
            strncat(input, s1, 261);
            RemoveLogFile(input);
            break;

            case '3':
            printf("Which logfile would you like to modify: ");
            scanf("%s", &input);
            strncpy(name, input, 256);
            printf("\n");
            strncat(input, s1, 261);
            DisplayLogFile(input);
            
            printf("What would you like to do to the log?\n");
            printf("1: Add to the catalog\n");
            printf("2: Remove from the catalog\n");
            printf("3: Update a listing in the catalog\n");

            scanf("%c", &choice);
            printf("\n");

            switch(choice){
                case '1':
                    printf("Enter the exact title of the movie you would like to add: ");
                    scanf("%s", &input);
                    AddToLogFile(name, search(input, &database));
                break; 

                case '2':

                break;

                case '3':

                break;
            }
            break;

            case '4':
                printf("Thank you for using the program, have a nice day!\n");
                running = false;
            break;
        }

        running = false;        
    }
    return 0;
}