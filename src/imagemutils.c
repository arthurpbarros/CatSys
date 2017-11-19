#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/imagemutils.h"
#include "../include/excecoes.h"

#define PI 3.141592

/*
 * Efetua a leitura da imagem recebendo como parâmetro o caminho onde está localizada
 * e retorna um struct do tipo Imagem.
 */
Imagem abrirImagem(char *nome) {
    Imagem img;
    char aux[100];
    img.stream = fopen(nome, "r");
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

/*
 * Auxilia a função de abrirImagem(), ficando responsável apenas pela leitura dos pixels.
 */
void pegarPixels(Imagem *img) {
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

/*
 * Grava uma imagem em um diretório, ambos recebidos por parâmetros.
 */
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

/*
 * Realiza a copia de uma imagem para ser utilizada na operação de convolução.
 */
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

Circulo encontrarCirculo(Imagem *img, Area *area) {
    int x, y, a, b;
    int r = 0, t;
    int ***acumulador = calloc(img->altura, sizeof(int **));
    for (x = 0; x < img->altura; x++) {
        acumulador[x] = calloc(img->largura, sizeof(int *));
        for (y = 0; y < img->largura; y++) {
            acumulador[x][y] = calloc(area->rmax - area->rmin + 1, sizeof(int));
        }
    }
    for (x = area->xInicial + area->rmin; x < area->xFinal - area->rmin; x++) {
        for (y = area->yInicial + area->rmin; y < area->yFinal - area->rmin; y++) {
            if (img->pixels[x][y].r != 255) continue;
            for (r = area->rmin; r < area->rmax; r++) {
                for (t = 0; t < 360; t++) {
                    a = x - r * cos(t * PI / 180);
                    b = y - r * sin(t * PI / 180);
                    if (a < 0 || b < 0
                        || a >= img->altura || b >= img->largura
                        || a - r < 0 || b - r < 0
                        || a + r >= img->altura || b + r >= img->largura)
                        continue;
                    acumulador[a][b][r - area->rmin]++;
                }
            }
        }
    }
    Circulo c = {0, 0, 0, acumulador[0][0][0]};
    for (x = area->xInicial + area->rmin; x < area->xFinal - area->rmin; x++) {
        for (y = area->yInicial + area->rmin; y < area->yFinal - area->rmin; y++) {
            for (r = area->rmin; r < area->rmax; r++) {
                if (acumulador[x][y][r - area->rmin] > c.valor) {
                    c.valor = acumulador[x][y][r - area->rmin];
                    c.x = x;
                    c.y = y;
                    c.r = r;
                }
            }
        }
    }
    free(acumulador);
    return c;
}