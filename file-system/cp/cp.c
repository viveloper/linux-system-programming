#include <stdio.h>
#include <stdlib.h>

// argv[0] : cp
// argv[1] : src
// argv[2] : dst
int main(int argc, char **argv) {
	FILE *fp_src;
	FILE *fp_dst;
	int ch;

	if(argc < 3) {
		printf("wrong args.\n");
		return EXIT_FAILURE;
	}

	fp_src =  fopen(argv[1], "r");
	fp_dst =  fopen(argv[2], "w");
	
	while((ch = fgetc(fp_src)) != EOF) {
		fputc(ch, fp_dst);
	}

	fclose(fp_src);
	fclose(fp_dst);

	return EXIT_SUCCESS;
}
