#include <stdlib.h>
#include <string.h>
#include "../include/imagemutils.h"
#include "../include/excecoes.h"

Imagem abrirImagem(char *nome) {
    Imagem img;
    char aux[100];
    img.stream = fopen(nome, "r");
    /*Verificação de erro na leitura da imagem*/
    verificaStream(img.stream);

    verificaFgets(fgets(aux, 100, img.stream));
    aux[strlen(aux) - 1] = '\0';
    if (strcmp(aux, "P3") == 0) {
        img.tipo = P3;
    }

    verificaFgets(fgets(aux, 100, img.stream));

    verificaFgets(fgets(aux, 100, img.stream));
    img.largura = atoi(strtok(aux, " "));
    img.altura = atoi(strtok(NULL, " "));
    verificaFgets(fgets(aux, 100, img.stream));
    img.intervalo = atoi(aux);
    img.pixels = malloc(img.altura * sizeof(Pixel *));
    int i;
    for (i = 0; i < img.altura; i++) {
        img.pixels[i] = malloc(img.largura * sizeof(Pixel));
    }
    verificaAlocacaoPixels(&img);
    pegarPixels(&img);
    fclose(img.stream);
    return img;
}

void pegarPixels(Imagem *img) {
    /*Funcão para captar os pixeis da imagem, apartir do seu arquivo*/
    char aux[5] = "", *ptr;
    int i, j;

    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            verificaFgets(fgets(aux, 5, img->stream));
            img->pixels[i][j].r = (int) strtol(aux, &ptr, 10);
            verificaFgets(fgets(aux, 5, img->stream));
            img->pixels[i][j].g = (int) strtol(aux, &ptr, 10);
            verificaFgets(fgets(aux, 5, img->stream));
            img->pixels[i][j].b = (int) strtol(aux, &ptr, 10);
        }
    }
}

void gravarImagem(Imagem *img, char *nome) {
    img->stream = fopen(nome, "w");
    fprintf(img->stream, "%s\n", "P3");
    fprintf(img->stream, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(img->stream, "%d %d\n", img->largura, img->altura);
    fprintf(img->stream, "%d\n", img->intervalo);

    int i, j;
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            fprintf(img->stream, "%d\n", img->pixels[i][j].r);
            fprintf(img->stream, "%d\n", img->pixels[i][j].g);
            fprintf(img->stream, "%d\n", img->pixels[i][j].b);
        }
    }
    fclose(img->stream);
}

Imagem copiarImagem(Imagem *img) {
    Imagem copia;
    copia.tipo = img->tipo;
    copia.altura = img->altura;
    copia.largura = img->largura;
    copia.intervalo = img->intervalo;
    copia.pixels = malloc(copia.altura * sizeof(Pixel *));
    int i, j;
    for (i = 0; i < copia.altura; i++) {
        copia.pixels[i] = malloc(copia.largura * sizeof(Pixel));
        for (j = 0; j < copia.largura; j++) {
            copia.pixels[i][j].r = img->pixels[i][j].r;
            copia.pixels[i][j].g = img->pixels[i][j].g;
            copia.pixels[i][j].b = img->pixels[i][j].b;
        }
    }
    return copia;
}