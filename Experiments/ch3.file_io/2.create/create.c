#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
	int fd = creat("./test.txt", S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd >= 0) {
		printf("creat OK!\n");
	}
	else {
		perror("creat error");
	}
	char buf[4096];
	ssize_t ret = read(fd, buf, sizeof(char));
	if (ret == -1) {
		perror("read error");
	}
	return 0;
}
