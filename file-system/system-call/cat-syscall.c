#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
	const char *src = argv[1];
	unsigned char buffer[1024];
	
	int fd = open(src, O_RDONLY);

	ssize_t read_bytes;

	while(read_bytes = read(fd, buffer, sizeof buffer)) {
		write(STDOUT_FILENO, buffer, read_bytes);
	}

	close(fd);

	return 0;
}
