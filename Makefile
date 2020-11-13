main: main.o
	gcc -o main main.o `pkg-config --cflags --libs gtk+-3.0`

main.o: main.c
	gcc -c main.c `pkg-config --cflags --libs gtk+-3.0`