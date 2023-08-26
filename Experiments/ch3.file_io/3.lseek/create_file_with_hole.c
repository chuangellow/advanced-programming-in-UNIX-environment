#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
	char buf1[4096], buf2[4096];
	int i;
	char c1, c2;
	for (i = 0, c1 = 'a', c2 = 'A'; c1 <= 'z'; c1++, c2++, i++) {
		buf1[i] = c1;
		buf2[i] = c2;
	}

	int fd;
	if ((fd = creat("file.hole", S_IRWXU | S_IRWXG | S_IRWXO)) < 0) {
		perror("creat error");
	}
	if (write(fd, buf1, sizeof(char) * 26) != 26) {
		perror("buf1 write error");
	}
	if (lseek(fd, 16384, SEEK_SET) == -1) {
		perror("lseek error");
	}
	if (write(fd, buf2, sizeof(char) * 26) != 26) {
		perror("buf2 write error");
	}
	return 0;
}
