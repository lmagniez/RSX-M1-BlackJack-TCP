PLATEAUSRCDIR = ../ServeurBlackJack/src/
BINDIR = ./bin/
SRCDIR = ./src/
CC = gcc 
CFLAGS = -Wall -Wextra -g -O2

OBJET = $(BINDIR)ServeurUDP.o $(BINDIR)Network_Toolbox.o $(BINDIR)startServeur.o $(BINDIR)ServeurTCP.o $(BINDIR)parsingCmd.o $(BINDIR)carte.o $(BINDIR)tas.o $(BINDIR)jeu.o $(BINDIR)joueur.o $(BINDIR)plateau.o $(BINDIR)ServeurTCPClient.o

all: server

server : $(OBJET)
	$(CC) $(CFLAGS) -o $@ $^ -lpthread

$(BINDIR)carte.o: $(PLATEAUSRCDIR)carte.c
	@$(CC) $(CFLAGS) -c  -o $@ $(PLATEAUSRCDIR)carte.c

$(BINDIR)tas.o: $(PLATEAUSRCDIR)tas.c
	@$(CC) $(CFLAGS) -c  -o $@ $(PLATEAUSRCDIR)tas.c

$(BINDIR)jeu.o: $(PLATEAUSRCDIR)jeu.c
	@$(CC) $(CFLAGS) -c  -o $@ $(PLATEAUSRCDIR)jeu.c

$(BINDIR)joueur.o: $(PLATEAUSRCDIR)joueur.c
	@$(CC) $(CFLAGS) -c  -o $@ $(PLATEAUSRCDIR)joueur.c

$(BINDIR)plateau.o: $(PLATEAUSRCDIR)plateau.c
	@$(CC) $(CFLAGS) -c  -o $@ $(PLATEAUSRCDIR)plateau.c


$(BINDIR)parsingCmd.o : $(SRCDIR)parsingCmd.c
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)parsingCmd.c -lpthread  

$(BINDIR)ServeurTCP.o : $(SRCDIR)ServeurTCP.c
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)ServeurTCP.c -lpthread 

$(BINDIR)ServeurTCPClient.o : $(SRCDIR)ServeurTCPClient.c
	$(CC) $(CFLAGS) -c -o $@ $(SRCDIR)ServeurTCPClient.c -lpthread  

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
