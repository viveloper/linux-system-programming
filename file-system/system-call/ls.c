#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main(int argc, char ** argv) {
	const char *src_file = argv[1];
	struct stat statbuf;
	stat(src_file, &statbuf);

	switch (statbuf.st_mode & S_IFMT) {
		case S_IFBLK:  printf("block device");            break;
		case S_IFCHR:  printf("character device");        break;
		case S_IFDIR:  printf("directory");               break;
		case S_IFIFO:  printf("FIFO/pipe");               break;
		case S_IFLNK:  printf("symlink");                 break;
		case S_IFREG:  printf("regular file");            break;
		case S_IFSOCK: printf("socket");                  break;
		default:       printf("unknown?");                break;
	}
	printf("\t");

	unsigned int arr_mask[9] = {
		S_IRUSR, S_IWUSR, S_IXUSR, 
		S_IRGRP, S_IWGRP, S_IXGRP, 
		S_IROTH, S_IWOTH, S_IXOTH  
	};
	const long unsigned int num_of_mask = sizeof arr_mask / sizeof(unsigned int);
	
	for(int i=0; i<num_of_mask; i++) {
		if(statbuf.st_mode & arr_mask[i]) {
			if(i % 3 == 0) printf("r");
			else if(i % 3 == 1) printf("w");
			else if(i % 3 == 2) printf("x");
		} else {
			printf("-");
		}
	}
	printf("\t");

	printf("%u\t", statbuf.st_nlink);
	
	struct passwd *passwdbuf = getpwuid(statbuf.st_uid);	
	printf("%s\t", passwdbuf->pw_name);
	struct group *groupbuf = getgrgid(statbuf.st_gid);
	printf("%s\t", groupbuf->gr_name);
	printf("%lu\t", statbuf.st_size);
	struct tm *timebuf =  localtime(&statbuf.st_mtime);
	printf("%d월 %d %d:%d\t", timebuf->tm_mon + 1, timebuf->tm_mday, timebuf->tm_hour, timebuf->tm_min);

	printf("%s\n", src_file);
	return 0;
}
