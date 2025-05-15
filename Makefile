all:
	gcc -std=c23 -IC:/Users/akiva/SDL3/include main.c lot.c -o main.exe -LC:/Users/akiva/SDL3/lib/x64 -lSDL3 -mwindows -static

