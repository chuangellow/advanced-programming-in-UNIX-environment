#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	const char* filename = "output.txt";

    // Create or clear the file initially
    FILE *file = fopen(filename, "w");
    fclose(file);

	int fd = open(filename, O_RDWR);
	if (fd == -1) {
		perror("Error opening file");
		exit(1);
	}
	const char* message = "Hello, World\n";
	ssize_t bytes_written = write(fd, message, strlen(message));

	if (bytes_written == -1) {
		perror("Error writing to file");
		exit(1);
	}

	int new_fd = dup2(fd, 6);
	if (new_fd == -1) {
		perror("Error duplicating file");
		exit(1);
	}

	char buf[strlen(message) + 1];
	lseek(new_fd, 0, SEEK_SET);
	ssize_t bytes_read = read(new_fd, buf, strlen(message));
	if (bytes_read == -1) {
		perror("Error reading from file");
		exit(1);
	}
	buf[bytes_read] = '\0';
	printf("file descriptor: %d\n", new_fd);
	printf("%s", buf);
	return 0;
}
