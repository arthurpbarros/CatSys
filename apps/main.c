#include "../include/excecoes.h"
#include "../include/filtroutils.h"

/*
 * Aplica filtros necessários para detecção de círculos na imagem.
 */
Imagem aplicarFiltros(Imagem *img) {
    *img = aplicarFiltroCinza(img);
    Filtro gaus = pegarFiltro(GAUSSIANO);
    *img = aplicarConvolucao(img, &gaus);
    *img = aplicarFiltroSobel(img);
    *img = aplicarBinarizacao(img);
    return *img;
}

/*
 * Capta a pupila a partir da Transformada de Hough
 */
Circulo pegarPupila(Imagem *img) {
    /* Define a área que será processada para encontrar o círculo com o raio mínimo  190 e máximo = 210 */
    Area areaIris = {0, img->altura, 0, img->largura, 190, 210};
    /* Se a resolução da imagem for baixa, o raio mínimo e máximo precisam ser ajustados para economizar poder de processamento computacional */
    if (img->altura < 700 || img->largura < 700) {
        areaIris.rmin = 110;
        areaIris.rmax = 140;
    }
    Circulo iris = encontrarCirculo(img, &areaIris);
    /* Define a área da íris que será processada para encontrar a pupila. Com raio mínimo = 50 e máximo igual ao da íris */
    Area areaPupila = {iris.x - iris.r, iris.x + iris.r, iris.y - iris.r, iris.y + iris.r, 50, iris.r};
    Circulo pupila = encontrarCirculo(img, &areaPupila);
    return pupila;
}

/*
 * Define os pixels ao redor da pupila com a cor preta
 */
void destacarPupila(Imagem *img, Area *area, Circulo *pupila) {
    int i, j;
    for (i = area->xInicial - 50; i < area->xFinal + 50; i++) {
        for (j = area->yInicial - 50; j < area->yFinal + 50; j++) {
            if (distancia(i, j, pupila) > pupila->r) {
                img->pixels[i][j].r = 0;
                img->pixels[i][j].g = 0;
                img->pixels[i][j].b = 0;
            }
        }
    }
}

/*
 * Contorna a pupila de forma recursiva
 */
void contornarPupila(Imagem *img, Area *area, Circulo *pupila) {
    if(area->xInicial == area->xFinal) {
        return;
    } else if(area->yInicial == area->yFinal) {
        area->yInicial = 0;
        area->xInicial++;
    } else {
        area->yInicial++;
    }
    if(distancia(area->xInicial, area->yInicial, pupila) == pupila->r) {
        img->pixels[area->xInicial][area->yInicial].r = 255;
    }
    contornarPupila(img, area, pupila);
}

/*
 * Analisa se o paciente possui algum grau de catarata e imprimi o relatório em um arquivo de saída.
 */
void diagnosticar(Imagem *img, Circulo *pupila, Area *area, char *saida) {
    int i, j;
    int brancos = 0, total = 0;
    for (i = area->xInicial; i < area->xFinal; i++) {
        for (j = area->yInicial; j < area->yFinal; j++) {
            if (distancia(i, j, pupila) < pupila->r) {
                /* Usando 30% de threshold para o pixel */
                if (img->pixels[i][j].r > 0.3 * 255) {
                    brancos++;
                }
                total++;
            }
        }
    }
    FILE *arq = fopen(saida, "w");
    float comprometimento = (float) brancos / total;
    fprintf(arq, "Diagnóstico Geral: ");
    /* Usando 30% de threshold para catarata */
    if(comprometimento < 0.3) {
        fprintf(arq, "Sem catarata\n");
    } else {
        fprintf(arq, "Com catarata\n");
        fprintf(arq, "Porcentagem de Comprometimento: %.2f%%\n", comprometimento * 100);
    }
    fclose(arq);
}

/*
 * Executa o programa
 */
int main(int argc, char *argv[]) {
    verificaArgumentos(argc, argv);
    printf("Iniciando o processamento...\n");
    Imagem img = abrirImagem(argv[2]);
    Imagem copia = copiarImagem(&img);

    img = aplicarFiltros(&img);
    copia = aplicarFiltroCinza(&copia);

    Circulo pupila = pegarPupila(&img);

    img = copiarImagem(&copia);

    Area regiaoPupila = {pupila.x - pupila.r, pupila.x + pupila.r, pupila.y - pupila.r, pupila.y + pupila.r, pupila.r};
    /* Variável contorno usada no algorítmo recursivo que contorna a pupila */
    Area contorno = regiaoPupila;
    contornarPupila(&img, &contorno, &pupila);
    gravarImagem(&img, "PupilaContornada.ppm", NULL);

    destacarPupila(&copia, &regiaoPupila, &pupila);
    diagnosticar(&copia, &pupila, &regiaoPupila, argv[6]);
    gravarImagem(&copia, "PupilaSegmentada.ppm", &regiaoPupila);
    printf("Processamento concluído.\n");
    return 0;
}