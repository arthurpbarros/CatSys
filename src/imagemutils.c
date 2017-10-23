#include <stdlib.h>
#include <string.h>
#include "imagemutils.h"

void pegarPixels(Imagem *img) {
    char aux[5] = "", *ptr;
    int i, j;

    for(i = 0; i < img->altura; i++) {
        for(j = 0; j < img->largura; j++) {
            img->pixels[i][j].x = i;
            img->pixels[i][j].y = j;
            if(!fgets(aux, 5, img->stream)) return;
            img->pixels[i][j].r = strtol(aux, &ptr, 10);
            if(!fgets(aux, 5, img->stream)) return;
            img->pixels[i][j].g = strtol(aux, &ptr, 10);
            if(!fgets(aux, 5, img->stream)) return;

            img->pixels[i][j].b = strtol(aux, &ptr, 10);
        }
    }
}

Imagem abrirImagem(char *nome) {
    Imagem img;
    char aux[100];
    img.stream = fopen(nome, "r");
    if(img.stream == NULL) {
        fprintf(stderr, "Aconteceu algum problema ao abrir a imagem\ncaminho ou nome do arquivo incorreto\n");
        exit(1);
    }

    if(!fgets(aux, 100, img.stream)) exit(1);
    aux[strlen(aux) - 1] = '\0';
    if(strcmp(aux, "P3") == 0) {
        img.tipo = P3;
    }

    if(!fgets(aux, 100, img.stream)) exit(1);

    if(!fgets(aux, 100, img.stream)) exit(1);
    img.altura = atoi(strtok(aux, " "));
    img.largura = atoi(strtok(NULL, " "));
    img.pixels = malloc(img.altura * sizeof(Pixel *));
    int i;
    for(i = 0; i < img.altura; i++) {
        img.pixels[i] = malloc(img.largura * sizeof(Pixel));
    }
    if(img.pixels == NULL || img.pixels[0] == NULL) {
        fprintf(stderr, "O programa não conseguiu alocar memória suficiente para a imagem. Logo, teve que ser encerrado.");
        exit(1);
    }

    pegarPixels(&img);
    fclose(img.stream);
    return img;
}

void aplicarFiltroCinza(Imagem *img){
    int i,j;
    FILE *output = fopen("Catarata.ppm","w");

    fprintf(output,"%s\n","P3");
    fprintf(output, "%d %d\n",img->altura,img->largura);
    fprintf(output, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");

    for(i = 0; i < img->altura; i++) {
        for(j = 0; j < img->largura; j++) {
            img->pixels[i][j].r *= 1.3;
            img->pixels[i][j].g *= 1.59;
            img->pixels[i][j].b *= 1.11;
            fprintf(output, "%d\n", img->pixels[i][j].r);
            fprintf(output, "%d\n", img->pixels[i][j].g);
            fprintf(output, "%d\n", img->pixels[i][j].b);
        }
    }
    fclose(output);
}