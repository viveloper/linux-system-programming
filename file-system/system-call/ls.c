#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void print_file_info(const char *filepath, const char *filename);
void print_all_files(const char *dirpath); 

int main(int argc, char ** argv) {
	if(argc < 2) {
		print_all_files("."); // all files in directory
	} else {
		for(int i=1; i<argc; i++) {
			const char *filepath = argv[i];
			struct stat statbuf;
			lstat(filepath, &statbuf);
			if(S_ISDIR(statbuf.st_mode)) {
				printf("%s:\n", filepath);
				print_all_files(filepath); // all files in directory
			} else {
				print_file_info(filepath, filepath);
			}
		}
	}
	
	return 0;
}

void print_all_files(const char *dirpath) {
	DIR *dir = opendir(dirpath);
	struct dirent *ent;
	while((ent = readdir(dir)) != NULL) {
		if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) continue;
		char path[1024];
		snprintf(path, sizeof path, "%s/%s", dirpath, ent->d_name);
		print_file_info(path, ent->d_name);
	}
	closedir(dir);
}

void print_file_info(const char *filepath, const char *filename) {
	const char *src_file = filepath;
	struct stat statbuf;
	lstat(src_file, &statbuf);

	char perm[] = "----------";
	switch (statbuf.st_mode & S_IFMT) {
		case S_IFBLK:	perm[0] = 'b';	break;
		case S_IFCHR:   perm[0] = 'c';	break;
		case S_IFDIR:   perm[0] = 'd';	break;
		case S_IFIFO:   perm[0] = 'p';	break;
		case S_IFLNK:   perm[0] = 'l';	break;
		case S_IFREG:   perm[0] = '-';	break;
		case S_IFSOCK:  perm[0] = 's';	break;
		default:						break;
	}

	unsigned int arr_mask[9] = {
		S_IRUSR, S_IWUSR, S_IXUSR, 
		S_IRGRP, S_IWGRP, S_IXGRP, 
		S_IROTH, S_IWOTH, S_IXOTH  
	};
	const long unsigned int num_of_mask = sizeof arr_mask / sizeof(unsigned int);

	for(int i=0; i<num_of_mask; i++) {
		if(statbuf.st_mode & arr_mask[i]) {
			if(i % 3 == 0) perm[i+1] = 'r';
			else if(i % 3 == 1) perm[i+1] = 'w';
			else if(i % 3 == 2) perm[i+1] = 'x';
		} else {
			perm[i+1] = '-';
		}
	}
	printf("%s ", perm);

	printf("%u ", statbuf.st_nlink);

	struct passwd *passwdbuf = getpwuid(statbuf.st_uid);	
	printf("%s ", passwdbuf->pw_name);
	struct group *groupbuf = getgrgid(statbuf.st_gid);
	printf("%s ", groupbuf->gr_name);
	if((statbuf.st_mode & S_IFMT) == S_IFBLK || (statbuf.st_mode & S_IFMT) == S_IFCHR) {
		printf("%d, %d ", major(statbuf.st_rdev), minor(statbuf.st_rdev));
	} else {
		printf("%lu ", statbuf.st_size);
	} 
	struct tm *timebuf =  localtime(&statbuf.st_mtime);
	printf("%2d월 %2d %02d:%02d ", timebuf->tm_mon + 1, timebuf->tm_mday, timebuf->tm_hour, timebuf->tm_min);

	if(perm[0] == 'l') {
		char buf[256];
		ssize_t len = readlink(src_file, buf, sizeof buf);
		buf[len] = '\0';
		printf("%s -> %s\n", src_file, buf);
	} else {
		printf("%s\n", filename);
	}

}

