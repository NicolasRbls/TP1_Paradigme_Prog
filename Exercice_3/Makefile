# Nom du fichier exécutable
EXE = RoblestrainApp

# Compilateur et options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

# Règle de compilation par défaut
all: $(EXE)

# Liaison
$(EXE): main.c trainHoraire.c
	$(CC) $(CFLAGS) -o $@ $^

# Nettoyer le projet
clean:
	del /q *.o $(EXE)
