#include <dirent.h>
#include <stdio.h>

char ** listDir(const char* dirname) {
	DIR * dir = NULL;
	struct dirent *entry;

	if ((dir = opendir(dirname)) == NULL) {
		printf("Failed to Open Dir");
		return NULL;
	}
	int i = 0;
	while(entry = readdir(dir)) {
		i++;
		printf("filename%d = %s\t", i, entry->d_name);
		printf("filetype%d = %s\n", i, entry->d_type);
	}
	seekdir(dir, 0);
	char * filenames[i] = NULL;
	i = 0;
	while (entry = readdir(dir))
		filenames[i] = entry->d_name;
	return filenames;
}

int main() {
	char ** fns;
	fns = listDir("/home/pi/study/c++/src");
	printf("%s\n", fns[0]);
	return 0;
}
