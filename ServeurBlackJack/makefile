EXEC=./
BINDIR=bin/
SRCDIR=src/

OBJET=$(BINDIR)carte.o $(BINDIR)tas.o $(BINDIR)jeu.o $(BINDIR)joueur.o $(BINDIR)plateau.o 
CC=gcc
CFLAGS=-Wall -g -lpthread

main : $(OBJET)
	@$(CC) -o $(EXEC)main $(BINDIR)*.o $(SRCDIR)main.c

$(BINDIR)carte.o: $(SRCDIR)carte.c
	@$(CC) $(CFLAGS) -c  -o $@ $(SRCDIR)carte.c

$(BINDIR)tas.o: $(SRCDIR)tas.c
	@$(CC) $(CFLAGS) -c  -o $@ $(SRCDIR)tas.c

$(BINDIR)jeu.o: $(SRCDIR)jeu.c
	@$(CC) $(CFLAGS) -c  -o $@ $(SRCDIR)jeu.c

$(BINDIR)joueur.o: $(SRCDIR)joueur.c
	@$(CC) $(CFLAGS) -c  -o $@ $(SRCDIR)joueur.c

$(BINDIR)plateau.o: $(SRCDIR)plateau.c
	@$(CC) $(CFLAGS) -c  -o $@ $(SRCDIR)plateau.c


clean:
	@rm -rf $(BINDIR)*.o
	@rm -rf ./main
	@echo "Cleaning done :)"
