#nom fichier exécutable
EXE = roblesexo1
BINS = saveliste

#compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

#regle de compilation par défaut
all: $(EXE)

#liaison
$(EXE): robleslisteint.c roblesexo1.c
	$(CC) $(CFLAGS) -o $@ $^

#nettoyer savelist
clean:
	del/q *.o $(EXE) $(BINS) 
