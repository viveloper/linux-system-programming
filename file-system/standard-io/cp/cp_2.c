#include <stdio.h>
#include <stdlib.h>

// argv[0] : cp
// argv[1] : src
// argv[2] : dst
int main(int argc, char **argv) {
	FILE *fp_src;
	FILE *fp_dst;
	int buffer[1024];
	int read_bytes;

	if(argc < 3) {
		printf("usage: cp src dest\n");
		return EXIT_FAILURE;
	}

	fp_src =  fopen(argv[1], "r");
	fp_dst =  fopen(argv[2], "w");

	while (read_bytes = fread(buffer, 1, sizeof(buffer), fp_src)) {
		fwrite(buffer, 1, read_bytes, fp_dst);
	}

	fclose(fp_src);
	fclose(fp_dst);

	return EXIT_SUCCESS;
}
