#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include "file_io.h"

void list_files(const char *path) {
    struct dirent *entry;
    struct stat file_stat;
    char full_path[512];

    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (stat(full_path, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        if (S_ISREG(file_stat.st_mode)) {
            printf("File: %s, Size: %ld bytes\n", entry->d_name, file_stat.st_size);
        }
    }

    closedir(dir);
}
