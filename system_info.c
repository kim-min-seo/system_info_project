#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system_info.h"

void get_cpu_info(char *buffer) {
    // CPU 사용량 정보를 수집하여 버퍼에 저장 (예시 파일 사용)
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fgets(buffer, 256, fp);
    fclose(fp);
}

void get_mem_info(char *buffer) {
    // 메모리 사용량 정보를 수집하여 버퍼에 저장 (예시 파일 사용)
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fgets(buffer, 256, fp);
    fclose(fp);
}
