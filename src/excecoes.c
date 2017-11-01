#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/imagemutils.h"

void fechar() {
    printf("Saindo do programa...\n");
    exit(1);
}

void verificaStream(FILE *stream) {
    if (stream == NULL) {
        fprintf(stderr, "Aconteceu algum problema ao ler o caminho da imagem.\n");
        fechar();
    }
}

void verificaAlocacaoPixels(Imagem *img) {
    if (img->pixels == NULL || img->pixels[0] == NULL) {
        fprintf(stderr, "O programa não conseguiu alocar memória suficiente para imagem.\n");
        fechar();
    }
}

void verificaFgets(char *fgets) {
    if (!fgets) {
        fprintf(stderr, "Não foi possível ler a imagem.\n");
        fechar();
    }
}

void verificaArgumentos(int argc, char *argv[]) {
    if (argc == 7) {
        if (strcmp(argv[1], "-i") == 0 && strcmp(argv[3], "-f") == 0 && strcmp(argv[5], "-o") == 0) {
            return;
        }
    }
    fprintf(stderr, "Argumentos passados incorretamente.\nCorreto: ./catarata -i imagem.ppm -f ppm -o diagnostico.txt\n"
            "-i <input-image> a imagem de entrada a ser processada.\n"
            "-f <input-image-format> indica o formato da imagem de entrada.\n"
            "-o <diagnose-file> indica o nome do arquivo texto contendo o diagnóstico.\n");
    fechar();
}