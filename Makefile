INCLUDE = ./include
OBJ = ./obj
FLAGS = -ansi -Wall -O3
LIBS = -lm

all:
	gcc $(FLAGS) -c src/imagemutils.c -I $(INCLUDE) $(LIBS) -o $(OBJ)/imagemutils.o
	gcc $(FLAGS) -c src/excecoes.c -I $(INCLUDE) $(LIBS) -o $(OBJ)/excecoes.o
	gcc $(FLAGS) apps/main.c $(OBJ)/*.o -I $(INCLUDE) $(LIBS) -o bin/main
	cp bin/main catarata

clean:
	rm bin/*
	rm $(OBJ)/*.o