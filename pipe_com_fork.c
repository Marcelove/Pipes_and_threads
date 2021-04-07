#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define BUFFER_SIZE 25
#define READ_END          0
#define WRITE_END         1

int main(void)
{
	char write_msg[BUFFER_SIZE] = "Greetings";
	char read_msg[BUFFER_SIZE];

	pid_t pid;
	int fd[2];

	/*
	int pipe(int fds[2]);

	Parameters :
		fd[0] will be the fd(file descriptor) for the read end of pipe.
		fd[1] will be the fd for the write end of pipe.
	*/

	//create the pipe
	if (pipe(fd) == -1) {
		fprintf(stderr, "Pipe failed");
		return 1;
	}

	//now fork a child process
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	/*The child process's pid is never zero. fork returns zero to the child to tell it that it is the child. 
	The child process's pid, however, is the value that fork returns to the parent. (Remember that fork, assuming it succeeds, 
	returns twice -- once in the child, once in the parent.) You can confirm this by writing a program that compares the result
	of getpid in the child to the value fork returns to the parent (with a little IPC).
	https://stackoverflow.com/questions/23433915/child-process-always-zero-and-always-unique-after-fork
	*/

	if (pid > 0) { //parent process
		//close the unused end of the pipe
		close(fd[READ_END]);

		//write to the pipe
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1);

		//close the write end of the pipe
		close(fd[WRITE_END]);

	}

	else { //child process
		//lose the unused end o of the pipe
		close(fd[WRITE_END]);

		//read from the pipe
		read(fd[READ_END], read_msg, BUFFER_SIZE);
		printf("child read %s\n", read_msg);
	}

	/*
	pipe() is used for passing information from one process to another. pipe() is unidirectional therefore, for two-way 
	communication between processes, two pipes can be set up, one for each direction.
https://www.geeksforgeeks.org/c-program-demonstrate-fork-and-pipe/#:~:text=pipe()%20is%20used%20for,up%2C%20one%20for%20each%20direction.
	*/

	return 0;
}