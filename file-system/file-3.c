#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *fp;
	char buffer[1024];
	size_t bytesRead;

	fp = fopen("test.txt", "r");
	if (fp == NULL) {
        perror("파일 열기 실패");
        return EXIT_FAILURE;
    }

	while((bytesRead = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
		fwrite(buffer, 1, bytesRead, stdout);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
