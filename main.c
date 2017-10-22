#include "imagemutils.h"

int main(int argc, char **argv) {
    Imagem img = abrirImagem(argv[1]);
 	aplicarFiltroCinza(&img);
    printf("Altura: %d\tLargura: %d\n", img.altura, img.largura);
    return 0;
}