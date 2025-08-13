#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char *s = "hello world!\n";

	fwrite(s, 1, 13, stdout);
	return EXIT_SUCCESS;
}
