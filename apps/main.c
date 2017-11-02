#include "../include/imagemutils.h"
#include "../include/excecoes.h"

int main(int argc, char *argv[]) {
    verificaArgumentos(argc, argv);
    Imagem img = abrirImagem(argv[2]);
    aplicarFiltroCinza(&img);
    aplicarSegmentacao(&img);
    printf("Processamento concluído.\n");
    return 0;
}
