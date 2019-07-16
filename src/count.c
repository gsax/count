// SPDX-License-Identifier: Beerware
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void listdir(char *dir)
{
	size_t file_count = 0;
	size_t dir_count = 0;
	const struct dirent *dp;
	struct stat statbuf;
	DIR *fd;

	fd = opendir(dir);
	size_t arglen = strlen(dir);

	if (!fd) {
		fprintf(stderr, "%s: can't open %s, it's not a directory\n",
			__func__, dir);
		return;
	}

	while ((dp = readdir(fd)) != NULL) {
		char *fullpath = malloc(arglen + strlen(dp->d_name) + 2);

		sprintf(fullpath, "%s/%s", dir, dp->d_name);
		stat(fullpath, &statbuf);
		free(fullpath);

		if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, ".."))
			continue;
		else if (S_ISREG(statbuf.st_mode))
			file_count++;
		else if (S_ISDIR(statbuf.st_mode))
			dir_count++;
	}
	closedir(fd);
	printf("files: %zu\n", file_count);
	printf("dirs:  %zu\n", dir_count);
}

int main(int argc, char *argv[])
{
	if (argc > 2) {
		for (int i = 1; i < argc; i++) {
			printf("directory: %s\n", argv[i]);
			listdir(argv[i]);
		}
	} else if (argc == 2) {
		listdir(argv[1]);
	} else if (argc == 1) {
		listdir(".");
	}
	return EXIT_SUCCESS;
}
