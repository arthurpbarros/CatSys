#include <stdlib.h>
#include <math.h>
#include "../include/filtroutils.h"
#include "../include/excecoes.h"

/*
 * Transforma uma imagem colorida em tons de cinza.
 */
Imagem aplicarFiltroCinza(Imagem *img) {
    int i, j;
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            img->pixels[i][j].r *= 0.3; 
            img->pixels[i][j].g *= 0.59;
            img->pixels[i][j].b *= 0.11;
            int cinza = img->pixels[i][j].r + img->pixels[i][j].g + img->pixels[i][j].b;
            img->pixels[i][j].r = cinza;
            img->pixels[i][j].g = cinza;
            img->pixels[i][j].b = cinza;
        }
    }
    return *img;
}

/*
 * Realiza a operação de convolução de acordo com a imagem, e filtro passados como parâmetros.
 * E ao termínio da função será retornado uma Imagem com o filtro aplicado.
 */
Imagem aplicarConvolucao(Imagem *img, Filtro *filtro) {
    Imagem copia = copiarImagem(img);
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
            soma = abs(soma);
            copia.pixels[i][j].r = (int) soma;
            copia.pixels[i][j].g = (int) soma;
            copia.pixels[i][j].b = (int) soma;
        }
    }
    return copia;
}

/*
 * Detecta os contornos da imagem, e calcula o limiar aceitável para cada Imagem.
 */
Imagem aplicarFiltroSobel(Imagem *img) {
    Filtro sobelx = pegarFiltro(SOBELX);
    Filtro sobely = pegarFiltro(SOBELY);
    Imagem gx = aplicarConvolucao(img, &sobelx);
    Imagem gy = aplicarConvolucao(img, &sobely);
    Imagem saida = copiarImagem(img);
    int i, j;
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            int x = gx.pixels[i][j].r;
            int y = gy.pixels[i][j].r;
            int pixel = (int) sqrt((x * x) + (y * y));
            saida.pixels[i][j].r = pixel;
            saida.pixels[i][j].g = pixel;
            saida.pixels[i][j].b = pixel;
        }
    }
    saida.limiar = 18;
    return saida;
}

/*
 * De acordo com o limiar da imagem o processo de Binarização é aplicado.
 */
Imagem aplicarBinarizacao(Imagem *img) {
    int i, j;
    for (i = 0; i < img->altura; i++) {
        for (j = 0; j < img->largura; j++) {
            if (img->pixels[i][j].r > img->limiar) {
                img->pixels[i][j].r = 255;
                img->pixels[i][j].b = 255;
                img->pixels[i][j].g = 255;
            } else {
                img->pixels[i][j].r = 0;
                img->pixels[i][j].g = 0;
                img->pixels[i][j].b = 0;
            }
        }
    }
    return *img;
}

/*
 * Retorna um Filtro de acordo com o TipoFiltro informado. Caso o TipoFiltro seja inválido, o programa lança uma exceção.
 */
Filtro pegarFiltro(TipoFiltro tipo) {
    Filtro filtro;
    if (tipo == GAUSSIANO) {
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
        return filtro;
    } else if (tipo == SOBELX) {
        filtro.tamanho = 3;
        filtro.kernel = malloc(filtro.tamanho * sizeof(int *));
        int i;
        for (i = 0; i < filtro.tamanho; i++) {
            filtro.kernel[i] = malloc(filtro.tamanho * sizeof(int));
        }
        filtro.kernel[0][0] = -1;
        filtro.kernel[0][1] = 0;
        filtro.kernel[0][2] = 1;
        filtro.kernel[1][0] = -2;
        filtro.kernel[1][1] = 0;
        filtro.kernel[1][2] = 2;
        filtro.kernel[2][0] = -1;
        filtro.kernel[2][1] = 0;
        filtro.kernel[2][2] = 1;
        filtro.somaKernel = 1;
        return filtro;
    } else if (tipo == SOBELY) {
        filtro.tamanho = 3;
        filtro.kernel = malloc(filtro.tamanho * sizeof(int *));
        int i;
        for (i = 0; i < filtro.tamanho; i++) {
            filtro.kernel[i] = malloc(filtro.tamanho * sizeof(int));
        }
        filtro.kernel[0][0] = 1;
        filtro.kernel[0][1] = 2;
        filtro.kernel[0][2] = 1;
        filtro.kernel[1][0] = 0;
        filtro.kernel[1][1] = 0;
        filtro.kernel[1][2] = 0;
        filtro.kernel[2][0] = -1;
        filtro.kernel[2][1] = -2;
        filtro.kernel[2][2] = -1;
        filtro.somaKernel = 1;
        return filtro;
    }
    filtroExcecao();
    return filtro;
}