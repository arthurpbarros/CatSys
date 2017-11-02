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
    img.altura = atoi(strtok(aux, " "));
    img.largura = atoi(strtok(NULL, " "));
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
            img->pixels[i][j].x = i;
            img->pixels[i][j].y = j;
            verificaFgets(fgets(aux, 5, img->stream));
            img->pixels[i][j].r = strtol(aux, &ptr, 10);
            verificaFgets(fgets(aux, 5, img->stream));
            img->pixels[i][j].g = strtol(aux, &ptr, 10);
            verificaFgets(fgets(aux, 5, img->stream));
            img->pixels[i][j].b = strtol(aux, &ptr, 10);
        }
    }
}

void aplicarFiltroCinza(Imagem *img) {
    /*Função para aplicar o filtro cinza nos pixeis.*/
    int i, j;
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            img->pixels[i][j].r *= 0.3; /*+30% no red*/
            img->pixels[i][j].g *= 0.59;/*+59% no green*/
            img->pixels[i][j].b *= 0.11;/*+11% no blue*/
            int cinza = img->pixels[i][j].r + img->pixels[i][j].g + img->pixels[i][j].b;
            img->pixels[i][j].r = cinza;
            img->pixels[i][j].g = cinza;
            img->pixels[i][j].b = cinza;
            /*Escrita temporária num arquivo, a título de teste.*/
        }
    }
    gravarImagem(img, "CatarataCinza.ppm");
}

int Ires(int i, int j, Imagem *img) {
    /*Filtragem em determinado pixel passado como argumento*/
    int f[5][5] = {
            {2, 4,  5,  4,  2},
            {4, 9,  12, 9,  4},
            {5, 12, 15, 12, 5},
            {4, 9,  12, 9,  4},
            {2, 4,  5,  4,  2}
    };
    const int constFiltro = 159;
    int a, b;
    int valor = 0;
    for (a = -2; a <= 2; a++) {
        for (b = -2; b <= 2; b++) {
            if (j + a >= 0 && i + b >= 0 && j + a < img->largura && i + b < img->altura) {
                valor += (f[a + 2][b + 2] * img->pixels[i + b][j + a].r) / constFiltro;
            }
        }
    }
    return valor;
}

void aplicarSegmentacao(Imagem *img) {
    /*Aplicação de segmentação na imagem em tons de cinza.*/
    int i, j;
    Imagem nova = copiarImagem(img);
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            int valor = Ires(i, j, img);
            nova.pixels[i][j].r = valor;
            nova.pixels[i][j].g = valor;
            nova.pixels[i][j].b = valor;
        }
    }
    gravarImagem(&nova, "CatarataFiltro.ppm");
}

void gravarImagem(Imagem *img, char *nome) {
    img->stream = fopen(nome, "w");
    fprintf(img->stream, "%s\n", "P3");
    fprintf(img->stream, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(img->stream, "%d %d\n", img->altura, img->largura);
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
            copia.pixels[i][j].x = img->pixels[i][j].x;
            copia.pixels[i][j].y = img->pixels[i][j].y;
            copia.pixels[i][j].r = img->pixels[i][j].r;
            copia.pixels[i][j].g = img->pixels[i][j].g;
            copia.pixels[i][j].b = img->pixels[i][j].b;
        }
    }
    return copia;
}