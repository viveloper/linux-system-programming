#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int fd;
	if(argc == 2) {
		const char *src = argv[1];
		fd = open(src, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	} 

	unsigned char buffer[1024];
	ssize_t read_bytes;
	while(read_bytes = read(STDIN_FILENO, buffer, sizeof buffer)) {
		write(STDOUT_FILENO, buffer, read_bytes);
	}

	close(fd);

	return 0;
}
