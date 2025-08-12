#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct {
	char fname[32];
	size_t fsize;
} SRC_INFO;

size_t get_fsize(FILE*);

/** 
  argv[0] : extract
  argv[1] : target
 */
int main(int argc, char **argv) {
	if(argc < 2) {
		fprintf(stderr, "usage: %s target\n", argv[0]);
		return EXIT_FAILURE;
	}

	const char *target_path = argv[1];

	FILE *fp = fopen(target_path, "rb");
	if(!fp) {
		fprintf(stderr, "open target: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	unsigned char buffer;
	size_t acc;
	size_t read_count;
	FILE *fp_src; 
	SRC_INFO src_info;

	while(read_count = fread(&src_info, sizeof(SRC_INFO), 1, fp)) {
		acc = 0;
		fp_src = fopen(src_info.fname, "wb");
		while(read_count = fread(&buffer, 1, 1, fp)) {
			fwrite(&buffer, 1, read_count, fp_src);
			acc += read_count;
			if(acc == src_info.fsize) break;
		}
		fclose(fp_src);
	}

	
	fclose(fp);

	return EXIT_SUCCESS;
}
