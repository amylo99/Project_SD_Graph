# Définition du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall

# Nom de l'exécutable
EXEC = a.out

# Fichiers sources
SRC = main.c projet.c


OBJ = $(SRC:.c=.o)


all: $(EXEC)


$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ) $(EXEC)


run: $(EXEC)
	@echo "Usage: make run FILE=<filename>"
	./$(EXEC) < $(FILE)
