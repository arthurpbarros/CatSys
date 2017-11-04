#ifndef OFTASYS_EXCECOES_H
#define OFTASYS_EXCECOES_H

#include <stdio.h>
#include "imagemutils.h"

void fechar();
void verificaStream(FILE *stream);
void verificaAlocacaoPixels(Imagem *img);
void verificaFgets(char *fgets);
void verificaArgumentos(int argc, char *argv[]);
void filtroExcecao();

#endif /*OFTASYS_EXCECOES_H*/