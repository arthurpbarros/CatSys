#ifndef OFTASYS_IMAGEMUTILS_H
#define OFTASYS_IMAGEMUTILS_H

#include <stdio.h>

typedef enum _Tipo {
    P3
} Tipo;

typedef enum _TipoFiltro {
    GAUSSIANO,
    SOBELX,
    SOBELY
} TipoFiltro;

typedef struct _Filtro {
    int **kernel;
    int tamanho;
    float somaKernel;
} Filtro;

typedef struct _Pixel {
    int r, g, b;
} Pixel;

typedef struct _Imagem {
    char *nome;
    int altura, largura, intervalo, limiar;
    FILE *stream;
    Tipo tipo;
    Pixel **pixels;
} Imagem;

Imagem abrirImagem(char *nome);
Imagem aplicarFiltro();
void pegarPixels(Imagem *img);
Imagem aplicarFiltroCinza(Imagem *img);
Imagem aplicarFiltroSobel(Imagem *img);
void gravarImagem(Imagem *img, char *nome);
Imagem copiarImagem(Imagem *img);
Filtro pegarFiltro(TipoFiltro tipo);
Imagem aplicarConvolucao(Imagem *img, Filtro *filtro);
Imagem aplicarBinarizacao(Imagem *img);

#endif /*OFTASYS_IMAGEMUTILS_H*/