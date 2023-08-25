#include <unistd.h>
#include <assert.h>

#define BUFFERSIZE 4096

int main(int argc, char *argv[]) {
	int n;
	char buf[BUFFERSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFERSIZE)) > 0) {
		ssize_t out_n = write(STDOUT_FILENO, buf, n);
		assert(out_n == n);
		assert(out_n >= 0);
	}
	return 0;
}
