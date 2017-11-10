#ifndef OFTASYS_FILTROUTILS_H
#define OFTASYS_FILTROUTILS_H

#include "imagemutils.h"

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

Imagem aplicarConvolucao(Imagem *img, Filtro *filtro);
Filtro pegarFiltro(TipoFiltro tipo);
Imagem aplicarFiltroCinza(Imagem *img);
Imagem aplicarFiltroSobel(Imagem *img);
Imagem aplicarBinarizacao(Imagem *img);
int pixelValido(Imagem *img);
void AplicarHough(Imagem *img);

#endif /*OFTASYS_FILTROUTILS_H*/
