#include "../include/excecoes.h"
#include "../include/filtroutils.h"

int main(int argc, char *argv[]) {
    verificaArgumentos(argc, argv);
    Imagem img = abrirImagem(argv[2]);
    img = aplicarFiltroCinza(&img);
    Filtro gaus = pegarFiltro(GAUSSIANO);
    img = aplicarConvolucao(&img, &gaus);
    img = aplicarFiltroSobel(&img);
    img = aplicarBinarizacao(&img);
    gravarImagem(&img, "ImagemProcessada.ppm");
    /*AplicarHough(&img);*/
    printf("Processamento concluído.\n");
    return 0;
}