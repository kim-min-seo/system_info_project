CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: file_list

file_list: main.o file_io.o system_info.o
	$(CC) $(CFLAGS) -o file_list main.o file_io.o system_info.o
	

main.o: main.c file_io.h system_info.h
	$(CC) $(CFLAGS) -c main.c
	

file_io.o: file_io.c file_io.h
	$(CC) $(CFLAGS) -c file_io.c
	

system_info.o: system_info.c system_info.h
	$(CC) $(CFLAGS) -c system_info.c
	

clean:
	rm -f *.o file_list
