#ifndef OFTASYS_IMAGEMUTILS_H
#define OFTASYS_IMAGEMUTILS_H

#include <stdio.h>

typedef enum _Tipo {
    P3
} Tipo;

typedef struct _Pixel {
    int x, y;
    int r, g, b;
} Pixel;

typedef struct _Imagem {
    char *nome;
    int altura, largura, intervalo;
    FILE *stream;
    Tipo tipo;
    Pixel **pixels;
} Imagem;

Imagem abrirImagem(char *nome);
void pegarPixels(Imagem *img);
void aplicarFiltroCinza(Imagem *img);
int Ires(int i,int j,Imagem img);
void aplicarSegmentacao(Imagem img);
void gravarImagem(Imagem *img,char *nome);
#endif //OFTASYS_IMAGEMUTILS_H