APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

FLAGS = -O3 -Wall -std=c99
LIBS = -lm

all: libed app

libed: $(OBJ)/imagemutils.o

app: $(BIN)/main

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc $(FLAGS) -c $< -I $(INCLUDE) $(FLAGS) -o $@

$(BIN)/%: $(APPS)/%.c
	gcc $(FLAGS) $< $(OBJ)/*.o -I $(INCLUDE) $(LIBS) -o $@

run:
	$(BIN)/main $(ARGS)

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*