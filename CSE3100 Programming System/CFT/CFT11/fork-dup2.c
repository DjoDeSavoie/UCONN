// In this assignment, we practice dup2() and fork().
// The main() function takes a command line argument.
// In the main() function we use fork() to create a
// child process. The child process redirects the
// standard output to a file named "output.txt" using dup2().
// Moreover, it prints out the command line argument in capital letters.
// The parent process simply prints out the command line argument.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#define MAX_LINE 1024

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("Usage: %s message\n", argv[0]);
		return -1;
	}

	pid_t pid;
	pid = fork();

	if (pid == 0)
	{

		// Make sure when the file is created, the user has the read and write access
		int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
		if (fd < 0)
		{
			printf("Cannot open the file\n");
			return -1;
		}

		// Redirect stdout to the file descriptor
		dup2(fd, STDOUT_FILENO);
		close(fd); // Close the file descriptor after dup2

		char buffer[MAX_LINE];
		strcpy(buffer, argv[1]);
		// TODO
		// fill in the code below

		for (int i = 0; i < strlen(buffer); i++)
		{
			buffer[i] = toupper(buffer[i]);
		}

		// Print the uppercase message (which will be written to output.txt)
		printf("%s\n", buffer);

		exit(0); // End the child process
	}

	// Parent process simply prints the original argument
	printf("%s\n", argv[1]);

	return 0;
}
