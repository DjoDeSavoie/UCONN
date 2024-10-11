#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char ** argv)
{
    pid_t child, child2;
    int exitStatus;

    // at least, there should be 3 arguments
    // 2 for the first command, and the rest for the second command
    if (argc < 4) {
        fprintf(stderr, "Usage: %s cmd1 cmd1_arg cmd2 [cmd2_args ..]\n", argv[0]);
        return 1;
    }

    // TODO

    //first fork for the first process
    child = fork();
    if(child == -1){
        perror("fork()");
        exit(1);
    }
    //if we are on the child process
    else if(child == 0){
        //we execute the first command with execlp
        if(execlp(argv[1], argv[1], argv[2], NULL) -1){
            perror("execlp()");
            exit(1);
        }
    }

    // Parent process waiting for the child to complete
    if (waitpid(child, &exitStatus, 0) > 0) {
        if (WIFEXITED(exitStatus)) {
            printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
        } else {
            printf("Program did not terminate normally.\n");
        }
    } else {
        perror("waitpid()");
        exit(1);
    }

    //second fork for the second process
    child2 = fork();

    if(child2 == -1){
        perror("fork()");
        exit(1);
    }

    else if(child2 == 0){
        //we execute the sedonc command
        if(execvp(argv[3], &argv[3]) == -1){
            perror("execvp()");
            exit(1);
        }
    }

    if (waitpid(child2, &exitStatus, 0) > 0) {
        if (WIFEXITED(exitStatus)) {
            printf("exited=%d exitstatus=%d\n", WIFEXITED(exitStatus), WEXITSTATUS(exitStatus));
        } else {
            printf("Program did not terminate normally.\n");
        }
    } else {
        perror("waitpid()");
        exit(1);
    }


    return 0;
}
