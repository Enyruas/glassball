all: glassball

glassball: glassball_main client server agent screen
	gcc -o glassball client.o server.o glassball.o agent.o screen.o -lpthread
glassball_main: src/glassball.c src/glassball.h
	gcc -c -o glassball.o src/glassball.c
client: src/client.c src/client.h
	gcc -c -o client.o src/client.c
server: src/server.c src/server.h
	gcc -c -o server.o src/server.c
agent: src/agent.c src/agent.h
	gcc -c -o agent.o src/agent.c
screen: src/screen.c src/screen.h
	gcc -c -o screen.o src/screen.c

clean:
	rm -rf *.o

