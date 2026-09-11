#include <stdio.h>
#include <stdlib.h>
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

	// buf[strcspn(buf, '\n')] = 0;
	// printf("String: %s", buf);


	// Fork and exec
	pid_t pid = fork();

	if (pid > 0) {
		// Parent
		wait(NULL);
	}
	else {
		// Child
		execlp(buf, buf, NULL);
		// Something went wrong
		fprintf(stderr, "Could not exec %s\n", buf);
	}
}
