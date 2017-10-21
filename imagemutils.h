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
    int altura, largura;
    FILE *stream;
    Tipo tipo;
    Pixel **pixels;
} Imagem;

void pegarPixels(Imagem *img);
Imagem abrirImagem(char *nome);

#endif //OFTASYS_IMAGEMUTILS_H
