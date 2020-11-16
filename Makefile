main: main.o highlow.o gui.o
	gcc -o main main.o highlow.o gui.o `pkg-config --cflags --libs gtk+-3.0`

main.o: main.c 
	gcc `pkg-config --cflags gtk+-3.0` -c main.c

highlow.o: highlow.c
	gcc `pkg-config --cflags gtk+-3.0` -c highlow.c

gui.o: gui.c 
	gcc `pkg-config --cflags gtk+-3.0` -c gui.c
