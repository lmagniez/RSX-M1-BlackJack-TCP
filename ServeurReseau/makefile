BINDIR = ./bin/
SRCDIR = ./src/
CC = gcc 
CFLAGS = -Wall -Wextra -g -O2

OBJET = $(BINDIR)ServeurUDP.o $(BINDIR)Network_Toolbox.o $(BINDIR)startServeur.o $(BINDIR)ServeurTCP.o

all: server

server : $(OBJET)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

$(BINDIR)ServeurTCP.o : $(SRCDIR)ServeurTCP.c
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)ServeurTCP.c -lpthread  

$(BINDIR)ServeurUDP.o : $(SRCDIR)ServeurUDP.c
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)ServeurUDP.c -lpthread  

$(BINDIR)startServeur.o : $(SRCDIR)startServeur.c
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)startServeur.c

$(BINDIR)Network_Toolbox.o : $(SRCDIR)Network_Toolbox.c
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)Network_Toolbox.c

clean:
	@rm -rf $(BINDIR)*.o 
	@rm -rf server
	@echo "Cleaning done :)"
