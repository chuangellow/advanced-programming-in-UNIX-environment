#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>

int main(void) {
	int fd1 = open("test.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd1 < 0) {
		perror("open error");
		return 1;
	}

	printf("The file descriptor of the open file is %d.\n", fd1);

	int fd2 = open("..", O_RDONLY);
	if (fd2 < 0) {
		perror("open error");
		return 1;
	}

	int fd3 = openat(fd2, "./test.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd3 < 0) {
		perror("openat error");
		return 1;
	}

	printf("The file descriptor of the open file is %d.\n", fd3);

	return 0;
}
