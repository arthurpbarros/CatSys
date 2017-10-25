#include <stdio.h>
#include <stdlib.h>
#include "../include/imagemutils.h"

void fechar() {
    printf("Saindo do promgrama...\n");
    exit(1);
}

void verificaStream(FILE *stream) {
    if(stream == NULL) {
        fprintf(stderr, "Aconteceu algum problema ao ler o caminho da imagem.\n");
        fechar();
    }
}

void verificaAlocacaoPixels(Imagem *img) {
    if(img->pixels == NULL || img->pixels[0] == NULL) {
        fprintf(stderr, "O programa não conseguiu alocar memória suficiente para imagem.\n");
        fechar();
    }
}

void verificaFgets(char *fgets) {
    if(!fgets) {
        fprintf(stderr, "Não foi possível ler a imagem.\n");
        fechar();
    }
}