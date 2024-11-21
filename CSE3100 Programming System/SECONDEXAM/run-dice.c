#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>

// write an integer to a pipe
void write_int(int pd, int value)
{
        write(pd, &value, sizeof(int));
}
// read an integer from a pipe
// the function returns the number of bytes read
int read_int(int pd, int *value)
{
        return read(pd, value, sizeof(int));
}

void dice_dist(int n)
{
        int pd1[2];
        // pipe creation
        if (pipe(pd1) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd2[2];
        // pipe creation
        if (pipe(pd2) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        pid_t pid = fork();
        
        if (pid == 0)
        {
                // TODO
                // fill in code below
                // note this is process A

                //we close the modes we don't use
                close(pd1[0]);
                close(pd2[1]);

                srand(3100);

                int v;

                // TODO
                // complete the following line of code
                while (read_int(pd2[0], &v) != 0)
                {
                        // TODO
                        // fill in code below
                        int throw1 = rand() % 6 + 1; // Throw the die to have a result between 1 and 6
                        write_int(pd1[1], throw1);
                }
                // TODO
                // fill in code below

                //Once we are done, we close the modes we were using
                close(pd1[1]);
                close(pd2[0]);
                
                exit(0);
        }
        // TODO
        // fill in code below

        close(pd1[1]);
        close(pd2[0]);

        int pd3[2];
        // pipe creation
        if (pipe(pd3) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd4[2];
        // pipe creation
        if (pipe(pd4) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t pid1 = fork();

        if (pid1 == 0)
        {
                // fill in code below
                // note this is process B

                //We close the mode we don't use
                close(pd3[0]);
                close(pd4[1]);

                srand(3504);

                int v;
                // TODO
                // complete the following line of code
                while (read_int(pd4[0], &v) != 0)
                {
                        // TODO
                        // fill in code below
                        int throw2 = rand() % 6 + 1; // Throw the die to have a result between 1 and 6
                        write_int(pd3[1], throw2);
                }

                // fill in code below
                close(pd3[1]);
                close(pd4[0]);
                exit(0);
        }

        // TODO
        // fill in code below

        close(pd3[1]);
        close(pd4[0]);

        int dist[11] = {0};
        int v1, v2;
        for (int i = 0; i < n; i++)
        {
                write_int(pd2[1], 1);
                write_int(pd4[1], 1);
                read_int(pd1[0], &v1);
                read_int(pd3[0], &v2);
                // TODO
                // fill in code below

                dist[v1 + v2 - 2]++;
        }

        // TODO
        // fill in code below

        close(pd1[0]);
        close(pd2[1]);
        close(pd3[0]);
        close(pd4[1]);

        wait(NULL); // the parent process wait for the child processes to finish
        wait(NULL);

        for (int i = 2; i <= 12; i++)
                printf("%02d %d\n", i, dist[i - 2]);
}
