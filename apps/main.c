#include "../include/imagemutils.h"

int main(int argc, char *argv[]) {
    Imagem img = abrirImagem(argv[1]);
    aplicarFiltroCinza(&img);
    //aplicarSegmentacao(&img);
    printf("Procesamento concluido.\n");
    return 0;
}