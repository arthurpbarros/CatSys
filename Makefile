APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

FLAGS = -O3 -Wall -ansi
LIBS = -lm

OBJETOS = $(OBJ)/imagemutils.o $(OBJ)/excecoes.o $(OBJ)/filtroutils.o $(OBJ)/main.o

all: libed app

libed: $(OBJETOS)

app: $(BIN)/main

$(OBJ)/main.o: $(APPS)/main.c
	gcc $(FLAGS) -c $< -I $(INCLUDE) $(LIBS) -o $@

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) $(LIBS) -o $@

$(BIN)/%: $(OBJETOS)
	gcc $(FLAGS) $(OBJ)/*.o -I $(INCLUDE) $(LIBS) -o $@
	cp $@ catarata

clean:
	rm $(BIN)/main
	rm $(OBJ)/*.o