#include <stdio.h>
#include <stdlib.h>

int get_max_width(int *nums, int size);
int get_width(int num);

enum COUNT_TYPE { LINE, WORD, CHAR };

int main(int argc, char **argv) {
	int ch;
	FILE *fp = stdin;
	char *filename;
	int counts[3] = { 0 }; // line, word, char
	int is_word_started = 0;
	int max_width;

	if(argc >= 2) {
		filename = argv[1];
		fp =  fopen(filename, "r");
	}

	while((ch = fgetc(fp)) != EOF) {
		counts[CHAR]++;
		if(ch == ' ' || ch == '\t' || ch == '\n') {
			is_word_started = 0;
		} else {
			if(!is_word_started) counts[WORD]++;
			is_word_started = 1;
		}
		if(ch == '\n') counts[LINE]++;
	}

	max_width = get_max_width(counts, 3);

	printf("%*d ", max_width, counts[LINE]);
	printf("%*d ", max_width, counts[WORD]);
	printf("%*d ", max_width, counts[CHAR]);
	printf("%s\n", filename);
	
	fclose(fp);

	return 0;
}

int get_max_width(int *nums, int size) {
	int max_width = 1;
	for(int i=0; i<size; i++) {
		int width = get_width(nums[i]);
		if(width  > max_width) max_width = width;
	}
	return max_width;
}

int get_width(int num) {
	if(num == 0) return 1;
	int width = 0;
	while(num > 0) {
		width++;
		num /= 10;
	}
	return width;
}
