#include <dirent.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char* argv[]) {
	assert(argc == 2);
	DIR *dp;
	struct dirent *dirp;
	dp = opendir(argv[1]);
	assert(dp != NULL);
	while ((dirp = readdir(dp)) != NULL) {
		printf("%s\n", dirp->d_name);
	}
	closedir(dp);
	return 0;
}
