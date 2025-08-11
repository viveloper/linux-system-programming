#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	FILE *fp;
	char buffer[256];

	fp = fopen("./test-makefile", "r");

	if(fp == NULL) {
		perror("fail file open");
		return EXIT_FAILURE;
	}

	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		printf("%s", buffer);
	}
	
	fclose(fp);

	return EXIT_SUCCESS;
}
