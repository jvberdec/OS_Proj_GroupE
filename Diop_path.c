#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

void readFile(int fd, int fd2) {
	size_t count = 1;
	while (count > 0) {
		char c;
		count = read(fd, &c, 1);
		if (count != 0) write(fd2, &c, 1);
	}
}

int path() {
	int t1, t2, t3;
	char cwd[PATH_MAX];

	//Print the current directory
	getcwd(cwd, PATH_MAX);
	printf("%s\n", cwd);

	errno = 0;
	t2 = open("t2.txt", O_WRONLY);
	if (t2 == -1) {
		printf("\n open() failed with error [%s]\n", strerror(errno));
		return 1;
	}
	else {
		write(t2, cwd, strlen(cwd));
	}
	close(t2);
	rename("t2.txt", "path.txt");

	//Concatenate the content of tree.txt and path.txt into t3.txt
	t1 = open("tree.txt", O_RDONLY);
	if (t1 == -1) {
		printf("\n open() failed with error [%s]\n", strerror(errno));
		return 1;
	}
	else {
		t3 = open("t3.txt", O_WRONLY);
		if (t3 == -1) {
			printf("\n open() failed with error [%s]\n", strerror(errno));
			return 1;
		}
		else {
			readFile(t1, t3);
			t2 = open("path.txt", O_RDONLY);
			readFile(t2, t3);
		}
	}

	close(t1);
	close(t2);
	close(t3);
	rename("t3.txt", "log.txt");

	//Delete tree.txt and path.txt
	remove("tree.txt");
	remove("path.txt");

	return 0;
}
