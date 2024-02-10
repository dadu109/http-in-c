CC=gcc

build: main.c
	$(CC) main.c -o main

start: main.c
	$(CC) main.c -o main && ./main
