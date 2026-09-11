#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {

	char buf[1024];

	// Prompt
	printf("$ ");

	// Get input from keyboard
	fgets(buf, 1024, stdin);
	
	// Trim newline
	char *nl = strchr(buf, '\n');
	if (nl) *nl = '\0';
	
	// Split buf into args
	char *args[20];
	int nargs = 0;

	args[nargs] = strtok(buf, " ");
	while (args[nargs] != NULL)  {
		args[++nargs] = strtok(NULL, " ");
	}

	// Fork and exec
	pid_t pid = fork();

	if (pid > 0) {
		wait(NULL);
	}
	else {
		execvp(args[0], args);
		fprintf(stderr, "Could not exec %s\n", buf);
	}
}
