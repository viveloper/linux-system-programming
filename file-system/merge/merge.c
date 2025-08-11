#include <stdio.h>
#include <stdlib.h>

/** 
	argv[0] : merge
	argv[1] : src 1
	argv[n-1] : src n-1
	argv[n] : dst
 */
int main(int argc, char **argv) {
	if(argc < 4) {
		printf("usage: merge src1 src2 ... dst\n");
		return EXIT_FAILURE;
	}

	FILE *fp_dst = fopen(argv[argc-1], "w");

	for(int i=1; i<argc-1; i++) {
		FILE *fp_src = fopen(argv[i], "r"); 
		int buffer[1024];
		int read_count;
		while(read_count = fread(buffer, 1, sizeof(buffer), fp_src)) {
			fwrite(buffer, 1, read_count, fp_dst);
		}
		fclose(fp_src);
	}

	fclose(fp_dst);

	return EXIT_SUCCESS;
}
