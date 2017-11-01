APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

FLAGS = -O3 -Wall -std=c99
LIBS = -lm

all: libed app copy

libed: $(OBJ)/imagemutils.o $(OBJ)/excecoes.o

app: $(BIN)/main

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) $(FLAGS) -o $@

$(BIN)/%: $(APPS)/%.c
	gcc $(FLAGS) $< $(OBJ)/*.o -I $(INCLUDE) $(LIBS) -o $@

copy:
	cp $(BIN)/main catarata

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*