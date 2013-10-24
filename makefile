IDIR=src
SERVER=server.c server.h
OBJ = server.o client.o glassball.o

glassball: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CLAGS)
glassball.o: $(IDIR)/glassball.c $(IDIR)/glassball.h
	$(CC) -c -o $@ $< 
client.o: $(IDIR)/client.c $(IDIR)/client.h
	$(CC) -c -o $@ $<
server.o: $(IDIR)/server.c $(IDIR)/server.h
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf *.o

