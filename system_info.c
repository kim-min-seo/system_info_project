#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system_info.h"

// /proc/stat 파일에서 CPU 정보를 읽어오는 함수
void get_cpu_info(char *buffer) {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fgets(buffer, 256, fp);
    fclose(fp);
}

// /proc/meminfo 파일에서 메모리 정보를 읽어오는 함수
void get_mem_info(char *buffer) {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fgets(buffer, 256, fp);
    fclose(fp);
}
