#include <stdlib.h>
#include <string.h>
#include "imagemutils.h"

void pegarPixels(Imagem *img) {

    char aux[4] = "";
    int i, j;

    for(i = 0; i < img->altura; i++) {
        for(j = 0; j < img->largura; j++) {
            img->pixels[i][j].x = i;
            img->pixels[i][j].y = j;

            fgets(aux, 4, img->stream);
            aux[strlen(aux)] = '\0';
            img->pixels[i][j].r = atoi(aux);
            //printf("R: %s\n", aux);

            getc(img->stream);

            fgets(aux, 4, img->stream);
            img->pixels[i][j].g = atoi(aux);
            //printf("G: %s\n", aux);

            getc(img->stream);

            fgets(aux, 4, img->stream);
            img->pixels[i][j].b = atoi(aux);
            //printf("B: %s\n", aux);
            getc(img->stream);
        }
    }
}

Imagem abrirImagem(char *nome) {
    Imagem img;
    char aux[100];
    img.stream = fopen(nome, "r");

    if(img.stream == NULL) {
        printf("Aconteceu algum problema ao abrir a imagem\ncaminho ou nome do arquivo incorreto\n");
        exit(1);
    }

    fgets(aux, 100, img.stream);
    aux[strlen(aux) - 1] = '\0';

    if(strcmp(aux, "P3") == 0) {
        img.tipo = P3;
    }

    fgets(aux, 100, img.stream);
    fgets(aux, 100, img.stream);

    img.altura = atoi(strtok(aux, " "));
    img.largura = atoi(strtok(NULL, " "));
    img.pixels = malloc(img.altura * sizeof(Pixel *));
    int i;
    for(i = 0; i < img.altura; i++) {
        img.pixels[i] = malloc(img.largura * sizeof(Pixel));
    }

    pegarPixels(&img);

    fclose(img.stream);

    return img;
}