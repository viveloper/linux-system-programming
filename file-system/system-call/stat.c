#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char ** argv) {
	const char *src_file = argv[1];
	struct stat statbuf;
	stat(src_file, &statbuf);

	printf("File type: ");
	switch (statbuf.st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device\n");            break;
		case S_IFCHR:  printf("character device\n");        break;
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFIFO:  printf("FIFO/pipe\n");               break;
		case S_IFLNK:  printf("symlink\n");                 break;
		case S_IFREG:  printf("regular file\n");            break;
		case S_IFSOCK: printf("socket\n");                  break;
		default:       printf("unknown?\n");                break;
	}

	unsigned int arr_mask[9] = {
		S_IRUSR, S_IWUSR, S_IXUSR, 
		S_IRGRP, S_IWGRP, S_IXGRP, 
		S_IROTH, S_IWOTH, S_IXOTH  
	};
	const long unsigned int num_of_mask = sizeof arr_mask / sizeof(unsigned int);
	
	printf("Permission: ");
	for(int i=0; i<num_of_mask; i++) {
		if(statbuf.st_mode & arr_mask[i]) {
			if(i % 3 == 0) printf("r");
			else if(i % 3 == 1) printf("w");
			else if(i % 3 == 2) printf("x");
		} else {
			printf("-");
		}
	}
	printf("\n");

	return 0;
}
