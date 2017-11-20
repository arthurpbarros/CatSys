#include "../include/excecoes.h"
#include "../include/filtroutils.h"

void desenharCirculo(Imagem *img, Circulo *c)
{
    int x = c->r-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (c->r << 1);



    while (x >= y)
    {
        img->pixels[c->x + x][c->y + y].r = 255;
        img->pixels[c->x + y][c->y + x].r = 255;
        img->pixels[c->x - y][c->y + x].r = 255;
        img->pixels[c->x - x][c->y + y].r = 255;
        img->pixels[c->x - x][c->y - y].r = 255;
        img->pixels[c->x - y][c->y - x].r = 255;
        img->pixels[c->x + y][c->y - x].r = 255;
        img->pixels[c->x + x][c->y - y].r = 255;

        img->pixels[c->x + x][c->y + y].g = 255;
        img->pixels[c->x + y][c->y + x].g = 255;
        img->pixels[c->x - y][c->y + x].g = 255;
        img->pixels[c->x - x][c->y + y].g = 255;
        img->pixels[c->x - x][c->y - y].g = 255;
        img->pixels[c->x - y][c->y - x].g = 255;
        img->pixels[c->x + y][c->y - x].g = 255;
        img->pixels[c->x + x][c->y - y].g = 255;

        img->pixels[c->x + x][c->y + y].b = 255;
        img->pixels[c->x + y][c->y + x].b = 255;
        img->pixels[c->x - y][c->y + x].b = 255;
        img->pixels[c->x - x][c->y + y].b = 255;
        img->pixels[c->x - x][c->y - y].b = 255;
        img->pixels[c->x - y][c->y - x].b = 255;
        img->pixels[c->x + y][c->y - x].b = 255;
        img->pixels[c->x + x][c->y - y].b = 255;

        if (err <= 0)
        {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0)
        {
            x--;
            dx += 2;
            err += (-c->r << 1) + dx;
        }
    }
}

Imagem aplicarFiltros(Imagem *img) {
    *img = aplicarFiltroCinza(img);
    Filtro gaus = pegarFiltro(GAUSSIANO);
    *img = aplicarConvolucao(img, &gaus);
    *img = aplicarFiltroSobel(img);
    *img = aplicarBinarizacao(img);
    return *img;
}

Imagem contornarPupila(Imagem *img, Imagem *copia,char *nome) {
    Area areaIris = {0, img->altura, 0, img->largura, 190, 210};
    Circulo iris = encontrarCirculo(img, &areaIris);
    Area areaPupila = {iris.x - iris.r, iris.x + iris.r, iris.y - iris.r, iris.y + iris.r, 50, iris.r};
    Circulo pupila = encontrarCirculo(img, &areaPupila);
    desenharCirculo(copia, &pupila);
    printf("%d",copia->pixels[pupila.y][pupila.x].r);
    diagnosticar(copia,&pupila,nome);
    return *copia;
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
    copia = contornarPupila(&img, &copia,argv[6]);   
    gravarImagem(&copia, "Contornada.ppm");
    printf("Processamento concluído.\n");
    return 0;
}