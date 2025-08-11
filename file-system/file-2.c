#include <stdio.h>

int main() {
	// FILE *fp;
	// fp = fopen("test.txt", "r");
	char buff[1024];

	while(fgets(buff, sizeof(buff), stdin)) {
		fputs(buff, stdout);
	}

	// fclose(fp);

	return 0;
}
