#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	int n;
	assert(argc == 2);
	char buf[atoi(argv[1])];

	int fd = open("./random_file.bin",  O_RDONLY);

	while ((n = read(fd, buf, atoi(argv[1]))) > 0) {
		//ssize_t out_n = write(STDOUT_FILENO, buf, n);
		//assert(out_n == n);
		//assert(out_n >= 0);
	}
	return 0;
}
