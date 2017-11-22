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
    /* Define a área que será processada para encontrar o círculo com o raio mínimo = 190 e máximo = 210 */
    Area areaIris = {0, img->altura, 0, img->largura, 190, 210};
    /* Se resolução da imagem for baixa, o raio mínimo e máximo precisam ser ajustados para economizar poder de processamento computacional */
    if(img->altura < 700 || img->largura < 700) {
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
    for(i = area->xInicial; i < area->xFinal; i++) {
        for(j = area->yInicial; j < area->yFinal; j++) {
            if(distancia(i, j, pupila) > pupila->r) {
                img->pixels[i][j].r = 0;
                img->pixels[i][j].g = 0;
                img->pixels[i][j].b = 0;
            }
        }
    }
}

/*
 * Executa o programa
 */
int main(int argc, char *argv[]) {
    verificaArgumentos(argc, argv);
    Imagem img = abrirImagem(argv[2]);
    Imagem copia = copiarImagem(&img);

    img = aplicarFiltros(&img);
    copia = aplicarFiltroCinza(&copia);

    Circulo pupila = pegarPupila(&img);

    Area regiao = {pupila.x - pupila.r - 50, pupila.x + pupila.r + 50, pupila.y - pupila.r - 50, pupila.y + pupila.r + 50, pupila.r};
    destacarPupila(&copia, &regiao, &pupila);
    gravarImagem(&copia, "Contornada.ppm", &regiao);
    printf("Processamento concluído.\n");
    return 0;
}