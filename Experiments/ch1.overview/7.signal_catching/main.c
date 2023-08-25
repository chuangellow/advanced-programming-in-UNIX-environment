#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 4096

static void sig_int(int);

int main(void) {
	char buf[MAXLINE];
	pid_t pid;
	int status;

	if (signal(SIGINT, sig_int) == SIG_ERR) {
		perror("signal error");
	}

	printf("%% ");
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = 0;
		if ((pid = fork()) < 0) perror("fork error");
		else if (pid == 0) {
			execlp(buf, buf, (char *) 0);
			exit(127);
		}
		if ((pid = waitpid(pid, &status, 0)) < 0) {
			perror("waitpid error");
		}
		printf("%% ");
	}
	exit(0);
}

void sig_int(int signo) {
	printf("interrupt\n%% ");
}
