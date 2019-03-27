#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void demo(const char* lhs, const char* rhs)
{
    int rc = strcmp(lhs, rhs);
    if(rc == 0)
        printf("[%s] equals [%s]\n", lhs, rhs);
    else if(rc < 0)
        printf("[%s] precedes [%s]\n", lhs, rhs);
    else if(rc > 0)
        printf("[%s] follows [%s]\n", lhs, rhs);
 
}
int main(void)
{
    time_t dateAcquired;
    struct tm* tm_info;

    dateAcquired = time(NULL);
    char time[26];
    tm_info = localtime(&dateAcquired);

    strftime(time, 26, "%Y-%m-%d", tm_info);
    printf("%s", &time);
}