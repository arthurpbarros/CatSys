#include <stdlib.h>
#include <string.h>
#include "../include/imagemutils.h"

#define A 1/159

Imagem abrirImagem(char *nome) {
    Imagem img;
    char aux[100];
    img.stream = fopen(nome, "r");
    if(img.stream == NULL) {
        fprintf(stderr, "Aconteceu algum problema ao abrir a imagem\ncaminho ou nome do arquivo incorreto\n");
        exit(1);
    }

    if(!fgets(aux, 100, img.stream)) exit(1);
    aux[strlen(aux) - 1] = '\0';
    if(strcmp(aux, "P3") == 0) {
        img.tipo = P3;
    }

    if(!fgets(aux, 100, img.stream)) exit(1);

    if(!fgets(aux, 100, img.stream)) exit(1);
    img.altura = atoi(strtok(aux, " "));
    img.largura = atoi(strtok(NULL, " "));
    img.pixels = malloc(img.altura * sizeof(Pixel *));
    int i;
    for(i = 0; i < img.altura; i++) {
        img.pixels[i] = malloc(img.largura * sizeof(Pixel));
    }
    if(img.pixels == NULL || img.pixels[0] == NULL) {
        fprintf(stderr, "O programa não conseguiu alocar memória suficiente para a imagem. Logo, teve que ser encerrado.");
        exit(1);
    }

    pegarPixels(&img);
    fclose(img.stream);
    return img;
}

void pegarPixels(Imagem *img) {
    char aux[5] = "", *ptr;
    int i, j;

    for(i = 0; i < img->altura; i++) {
        for(j = 0; j < img->largura; j++) {
            img->pixels[i][j].x = i;
            img->pixels[i][j].y = j;
            if(!fgets(aux, 5, img->stream)) exit(1);
            img->pixels[i][j].r = strtol(aux, &ptr, 10);
            if(!fgets(aux, 5, img->stream)) exit(1);
            img->pixels[i][j].g = strtol(aux, &ptr, 10);
            if(!fgets(aux, 5, img->stream)) exit(1);
            img->pixels[i][j].b = strtol(aux, &ptr, 10);
        }
    }
}

void aplicarFiltroCinza(Imagem *img){
    int i,j;
    FILE *output = fopen("Catarata.ppm","w");

    fprintf(output,"%s\n","P3");
    fprintf(output, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(output, "%d %d\n",img->altura,img->largura);

    for(i = 0; i < img->altura; i++) {
        for(j = 0; j < img->largura; j++) {
            int cinza = img->pixels[i][j].r * 1.3 + img->pixels[i][j].g * 1.59 + img->pixels[i][j].b * 1.11;
            fprintf(output, "%d\n", cinza);
            fprintf(output, "%d\n", cinza);
            fprintf(output, "%d\n", cinza);
        }
    }
    fclose(output);
}

void aplicarSegmentacao(Imagem *img){
    int f[5][5] = {
            {2,4,5,4,2},
            {4,9,12,9,4},
            {5,12,15,12,5},
            {4,9,12,9,4},
            {2,4,5,4,2}
    };
    int x,y,a,b;
    FILE *output = fopen("Catarata.ppm","w");

    fprintf(output,"%s\n","P3");
    fprintf(output, "%d %d\n",img->altura,img->largura);
    fprintf(output, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");

    Imagem *nova;
    for(a = -5/2; a <= 5/2;a++){
        for(b = -5/2; b <= 5/2;b++){
            for(y = 0;y < img->altura;y++){
                for(x = 0;x < img->largura;x++){
                    nova->pixels[x][y].r = f[a+5/2][b+5/2]*A*img->pixels[x+a][y+b].r;
                    nova->pixels[x][y].g = f[a+5/2][b+5/2]*A*img->pixels[x+a][y+b].g;
                    nova->pixels[x][y].b = f[a+5/2][b+5/2]*A*img->pixels[x+a][y+b].b;
                    fprintf(output, "%d\n", nova->pixels[x][y].r);
                    fprintf(output, "%d\n", nova->pixels[x][y].g);
                    fprintf(output, "%d\n", nova->pixels[x][y].b);
                }
            }
        }
    }
    fclose(output);
}