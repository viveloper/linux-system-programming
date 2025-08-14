#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
	const char *src = argv[1];
	int fd = open(src, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	dup2(fd, STDOUT_FILENO);

	const char buffer[13] = {"hello world!\n" };
	write(STDOUT_FILENO, buffer, sizeof buffer);
	
	close(fd);

	return 0;
}
