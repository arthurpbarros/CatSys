FILES = apps/main.c src/imagemutils.c src/excecoes.c

all:
	gcc $(FILES) -o bin/main
	cp bin/main catarata