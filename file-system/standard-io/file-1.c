#include <stdio.h>

int main() {
	FILE *fp;
	int ch;

	fp = fopen("test.txt", "r");

	while((ch = fgetc(fp)) != EOF) {
		fputc(ch, stdout);
	}

	fclose(fp);
	return 0;
}
