#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_cat(char *s1, char *s2)
{
    // TODO 
    if(s1 == NULL || s2 == NULL) {
        my_error("NULL string\n");
    }

    int lenS1 = strlen(s1);
    int lenS2 = strlen(s2);    

    int catLength = lenS1 + lenS2;
    char * cat = malloc(catLength + 1);//+1 for the '\0'
    if(cat == NULL){
        my_error("error malloc ! \n");
    }

    strcpy(cat, s1);
    strcat(cat, s2);
    
    return cat;
}

int main(int argc, char *argv[])
{
    char *s = my_cat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        char *temp = my_cat(s, argv[i]);
        free(s);
        s = temp;
    }

    printf("%s\n", s);
    free(s);
    return 0;
}