#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "file_io.h"
#include "system_info.h"

void get_system_info() {
    char cpu_info[256];
    char mem_info[256];
    int pipefd[2];
    pid_t cpid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {  // 자식 프로세스
        close(pipefd[0]); // 파이프의 읽기 끝을 닫음
        get_cpu_info(cpu_info);
        write(pipefd[1], cpu_info, strlen(cpu_info)); // 부모 프로세스에 데이터 전송
        close(pipefd[1]); // 파이프의 쓰기 끝을 닫음
        exit(EXIT_SUCCESS);
    } else { // 부모 프로세스
        wait(NULL); // 자식 프로세스가 종료될 때까지 대기
        close(pipefd[1]); // 파이프의 쓰기 끝을 닫음
        read(pipefd[0], cpu_info, sizeof(cpu_info)); // 자식 프로세스의 데이터 읽기
        close(pipefd[0]); // 파이프의 읽기 끝을 닫음

        printf("CPU Info: %s\n", cpu_info);

        // 메모리 정보를 자식 프로세스로부터 얻음
        if (pipe(pipefd) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        cpid = fork();
        if (cpid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (cpid == 0) {  // 자식 프로세스
            close(pipefd[0]); // 파이프의 읽기 끝을 닫음
            get_mem_info(mem_info);
            write(pipefd[1], mem_info, strlen(mem_info)); // 부모 프로세스에 데이터 전송
            close(pipefd[1]); // 파이프의 쓰기 끝을 닫음
            exit(EXIT_SUCCESS);
        } else { // 부모 프로세스
            wait(NULL); // 자식 프로세스가 종료될 때까지 대기
            close(pipefd[1]); // 파이프의 쓰기 끝을 닫음
            read(pipefd[0], mem_info, sizeof(mem_info)); // 자식 프로세스의 데이터 읽기
            close(pipefd[0]); // 파이프의 읽기 끝을 닫음

            printf("Memory Info: %s\n", mem_info);
        }
    }
}

int main() {
    char directory_path[256];

    printf("Enter the directory path: ");
    scanf("%255s", directory_path);

    list_files(directory_path);
    get_system_info();

    return 0;
}
