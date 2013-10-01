all: glassball

glassball: glassball_main client server 
	gcc -o glassball client.o server.o glassball.o
glassball_main: src/glassball.c src/glassball.h
	gcc -c -o glassball.o src/glassball.c
client: src/client.c src/client.h
	gcc -c -o client.o src/client.c
server: src/server.c src/server.h
	gcc -c -o server.o src/server.c

clean:
	rm -rf *.o

