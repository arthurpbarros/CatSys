FILES = apps/main.c src/imagemutils.c src/excecoes.c

all:
	gcc $(FILES) -o bin/main -lm -ansi
	cp bin/main catarata