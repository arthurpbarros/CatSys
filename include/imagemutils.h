#ifndef OFTASYS_IMAGEMUTILS_H
#define OFTASYS_IMAGEMUTILS_H

#include <stdio.h>

typedef enum _Tipo {
    P3
} Tipo;

typedef struct _Pixel {
    int r, g, b;
} Pixel;

typedef struct _Circulo {
    int x, y, r, valor;
} Circulo;

typedef struct _Area {
    int xInicial, xFinal;
    int yInicial, yFinal;
    int rmin, rmax;
} Area;

typedef struct _Imagem {
    char *nome;
    int altura, largura, intervalo, limiar;
    FILE *stream;
    Tipo tipo;
    Pixel **pixels;
} Imagem;

Imagem abrirImagem(char *nome);
void pegarPixels(Imagem *img);
void gravarImagem(Imagem *img, char *nome, Area *area);
Imagem copiarImagem(Imagem *img);
Circulo encontrarCirculo(Imagem *img, Area *area);
int distancia(int i,int j,Circulo *circulo);
void diagnosticar(Imagem *img,Circulo *pupila,char *saida);

#endif /*OFTASYS_IMAGEMUTILS_H*/