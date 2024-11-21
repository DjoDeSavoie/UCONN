#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

// redirect standard input to the specified file
void redirectStdin(const char *filename)
{
        int fd = open(filename, O_RDONLY);
        if (fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
        // TODO
        // fill in the code below

        dup2(fd, STDIN_FILENO);
        close(fd);
}

// redirect standad output to the specified file
void redirectStdout(const char *filename)
{
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (fd < 0)
        {
                perror("Error opening the file\n");
                exit(-1);
        }
        // TODO
        // fill in the code below

        dup2(fd, STDOUT_FILENO);
        close(fd);
}

// TODO: imeplement the following function
//  if word is an arithmetic sequence word, return 1 else return 0
int arithmetic(char *word)
{
        int len = strlen(word);

        if(len < 3) return 0; //min len of 3

        // Store the first two numbers to determine the common difference
        int first = (int)word[0];  // Convert char to int for the ascii code
        int second = (int)word[1];
        int commonDifference = second - first;

        // Check the rest of the characters
        for (int i = 2; i < len; i++)
        {
                int current = (int)word[i];
                if (current - second != commonDifference)
                {
                        return 0;
                }

                second = current;
        }

        return 1; // It is an arithmetic sequence
}