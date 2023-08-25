#include <stdio.h>

int main(int argc, char *argv[]) {
	int c;
	while ((c = getc(stdin)) != EOF) {
		if (putc(c, stdout) == EOF) printf("error");
		if (ferror(stdin)) printf("error");
	}
	return 0;
}
