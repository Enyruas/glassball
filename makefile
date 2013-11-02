IDIR=src/cversion/
SERVER=server.c server.h
OBJ = server.o client.o glassball.o agent.o screen.o
LIB = -lpthread

glassball: $(OBJ)
	$(CC) -o $@ $^ $(CLAGS) $(LIB)
glassball.o: $(IDIR)glassball.c $(IDIR)glassball.h
	$(CC) -c -o $@ $< 
client.o: $(IDIR)client.c $(IDIR)client.h
	$(CC) -c -o $@ $<
server.o: $(IDIR)server.c $(IDIR)server.h
	$(CC) -c -o $@ $<
agent.o: $(IDIR)agent.c $(IDIR)agent.h
	$(CC) -c -o $@ $(IDIR)/agent.c
screen.o: $(IDIR)screen.c $(IDIR)screen.h
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf *.o

