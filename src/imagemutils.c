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

void aplicarConvolucao(Imagem *img, Filtro *filtro) {
    Imagem temp = copiarImagem(img);
    int a, b, i, j;
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            float soma = 0;
            for (a = -(filtro->tamanho / 2); a <= filtro->tamanho / 2; a++) {
                for (b = -(filtro->tamanho / 2); b <= filtro->tamanho / 2; b++) {
                    if (i - a >= 0 && j - b >= 0 && i - a < img->altura && j - b < img->largura) {
                        soma += (filtro->kernel[a + filtro->tamanho / 2][b + filtro->tamanho / 2] *
                                 img->pixels[i - a][j - b].r) / filtro->somaKernel;
                    }
                }
            }
            temp.pixels[i][j].r = (int) soma;
            temp.pixels[i][j].g = (int) soma;
            temp.pixels[i][j].b = (int) soma;
        }
    }
    gravarImagem(&temp, "saida.ppm");
}

Filtro pegarFiltro(char *nome) {
    Filtro filtro;
    if (strcmp(nome, "gaussiano") == 0) {
        filtro.tamanho = 5;
        filtro.kernel = malloc(filtro.tamanho * sizeof(int *));
        int i;
        for (i = 0; i < filtro.tamanho; i++) {
            filtro.kernel[i] = malloc(filtro.tamanho * sizeof(int));
        }
        filtro.kernel[0][0] = 2;
        filtro.kernel[0][1] = 4;
        filtro.kernel[0][2] = 5;
        filtro.kernel[0][3] = 4;
        filtro.kernel[0][4] = 2;
        filtro.kernel[1][0] = 4;
        filtro.kernel[1][1] = 9;
        filtro.kernel[1][2] = 12;
        filtro.kernel[1][3] = 9;
        filtro.kernel[1][4] = 4;
        filtro.kernel[2][0] = 5;
        filtro.kernel[2][1] = 12;
        filtro.kernel[2][2] = 15;
        filtro.kernel[2][3] = 12;
        filtro.kernel[2][4] = 5;
        filtro.kernel[3][0] = 4;
        filtro.kernel[3][1] = 9;
        filtro.kernel[3][2] = 12;
        filtro.kernel[3][3] = 9;
        filtro.kernel[3][4] = 4;
        filtro.kernel[4][0] = 2;
        filtro.kernel[4][1] = 4;
        filtro.kernel[4][2] = 5;
        filtro.kernel[4][3] = 4;
        filtro.kernel[4][4] = 2;
        filtro.somaKernel = 159;
        /*int k[5][5] = {
                {2, 4,  5,  4,  2},
                {4, 9,  12, 9,  4},
                {5, 12, 15, 12, 5},
                {4, 9,  12, 9,  4},
                {2, 4,  5,  4,  2}
        };*/
        return filtro;
    }
    return filtro;
}