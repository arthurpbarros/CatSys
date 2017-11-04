SRC = ./src
INCLUDE = ./include
OBJ = ./obj
FLAGS = -ansi -Wall -O3
LIBS = -lm

all:
	gcc $(FLAGS) -c $(SRC)/excecoes.c -I $(INCLUDE) $(LIBS) -o $(OBJ)/excecoes.o
	gcc $(FLAGS) -c $(SRC)/imagemutils.c -I $(INCLUDE) $(LIBS) -o $(OBJ)/imagemutils.o
	gcc $(FLAGS) -c $(SRC)/filtroutils.c -I $(INCLUDE) $(LIBS) -o $(OBJ)/filtroutils.o
	gcc $(FLAGS) apps/main.c $(OBJ)/*.o -I $(INCLUDE) $(LIBS) -o bin/main
	cp bin/main catarata

clean:
	rm bin/*
	rm $(OBJ)/*.o