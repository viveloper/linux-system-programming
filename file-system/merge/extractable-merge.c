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
  argv[0] : merge
  argv[1] : src 1
  argv[n-1] : src n-1
  argv[n] : dst
 */
int main(int argc, char **argv) {
	if(argc < 4) {
		fprintf(stderr, "usage: %s src1 src2 ... dst\n", argv[0]);
		return EXIT_FAILURE;
	}

	const char *dst_path = argv[argc-1];
	const int src_count = argc - 2;

	FILE *dst = fopen(dst_path, "wb");
	if(!dst) {
		fprintf(stderr, "open dst: %s\n", strerror(errno));
		return EXIT_FAILURE;
	}

	for(int i=1; i<argc-1; i++) {
		const char *src_path = argv[i];
		FILE *src = fopen(src_path, "rb");
		if(!dst) {
			fprintf(stderr, "open src: %s\n", strerror(errno));
			fclose(dst);
			return EXIT_FAILURE;
		}

		SRC_INFO src_info;
		src_info.fsize = get_fsize(src);
		strcpy(src_info.fname, src_path);
		fprintf(stdout, "%s, %zu\n", src_info.fname, src_info.fsize);
		fwrite(&src_info, sizeof(SRC_INFO), 1, dst);

		unsigned char buffer[64 * 1024];
		size_t read_count;
		while(read_count = fread(buffer, 1, sizeof(buffer), src)) {
			fwrite(buffer, 1, read_count, dst);
		}

		fclose(src);
	}

	fclose(dst);

	return EXIT_SUCCESS;
}

size_t get_fsize(FILE *fp) {
	size_t fpos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	size_t fsize = ftell(fp);
	fseek(fp, fpos, SEEK_SET);
	return fsize;
}
