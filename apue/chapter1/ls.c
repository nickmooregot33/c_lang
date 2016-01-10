#include "apue.h"
#include <dirent.h>

int log_to_stderr = 0;

int main(int argc, char *argv[]){
	DIR *dp;
	struct dirent *dirp;

	if(argc!=2)
		err_quit("usage: ls directory_name");

	if((dp = opendir(argv[1]))==NULL)
		err_sys("can't open %s", argv[1]);

	while((dirp=readdir(dp))!=NULL)
		printf("%10s:%10d\n",dirp->d_name,dirp->d_ino);

	closedir(dp);
	exit(0);
}


