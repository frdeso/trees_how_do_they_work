all:
	gcc -g -o demo $(shell pkg-config --cflags glib-2.0) main.c $(shell pkg-config --libs glib-2.0)

	
