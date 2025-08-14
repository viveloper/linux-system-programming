#include <stdio.h>

int main(int argc, char **argv) {
	const char *src = argv[1];
	FILE *fp = fopen(src, "rb");
	char buffer[1024];
	size_t ret;
	while(ret = fread(buffer, 1, sizeof buffer, fp)) {
		fwrite(buffer, 1, ret, stdout);
	}
	fclose(fp);
	return 0;
}
