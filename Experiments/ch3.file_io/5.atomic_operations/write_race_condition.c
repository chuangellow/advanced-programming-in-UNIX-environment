#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void write_to_file(const char *message, const char *filename) {
    int fd = open(filename, O_WRONLY | O_APPEND);
    if (fd == -1) {
        perror("Error opening file");
        exit(1);
    }

    // Introducing a delay to increase the chance of race condition
    usleep(100000);

    ssize_t bytes_written = write(fd, message, strlen(message));
    if (bytes_written == -1) {
        perror("Error writing to file");
    }

    close(fd);
}

int main() {
    const char *filename = "output.txt";
    char *messageA = "Hello, I'm process A\n";
    char *messageB = "Hello, I'm process B\n";

    // Create or clear the file initially
    FILE *file = fopen(filename, "w");
    fclose(file);

    // Fork a new process
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error forking");
        exit(1);
    } else if (pid == 0) {
        write_to_file(messageB, filename);
		messageB = "I'm a child process\n";
		write_to_file(messageB, filename);
    } else {
        write_to_file(messageA, filename);
		messageA = "I'm a parent process\n";
		write_to_file(messageA, filename);
    }

    return 0;
}

