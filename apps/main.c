#include "../include/imagemutils.h"
#include "../include/excecoes.h"

int main(int argc, char *argv[]) {
    verificaArgumentos(argc, argv);
    Imagem img = abrirImagem(argv[2]);
    img = aplicarFiltroCinza(&img);
    Filtro gaus = pegarFiltro(GAUSSIANO);
    img = aplicarConvolucao(&img, &gaus);
    img = aplicarFiltroSobel(&img);
    gravarImagem(&img, "Saida.ppm");
    printf("Processamento concluído.\n");
    return 0;
}