#include <stdio.h>
#include <fcntl.h>

int main(void) {
	int fd = open("./out.txt", O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd >= 0) {
		printf("FILE I/O OK!");
	}
	else {
		perror("open error");
	}
	return 0;
}
