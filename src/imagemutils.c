#include <stdlib.h>
#include <string.h>
#include "../include/imagemutils.h"
#define A 159

Imagem abrirImagem(char *nome) {
    Imagem img;
    char aux[100];
    img.stream = fopen(nome, "r");
    //Verificação de erro na leitura da imagem
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
    //Funcão para captar os pixeis da imagem, apartir do seu arquivo
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
    //Função para aplicar o filtro cinza nos pixeis.
    int i,j;
    FILE *output = fopen("Catarata.ppm","w");

    fprintf(output,"%s\n","P3");
    fprintf(output, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(output, "%d %d\n",img->altura,img->largura);

    for(i = 0; i < img->altura; i++) {
        for(j = 0; j < img->largura; j++) {
            img->pixels[i][j].r *= 1.3; //+30% no red
            img->pixels[i][j].g *= 1.59;//+59% no green
            img->pixels[i][j].b *= 1.11;//+11% no blue
            int cinza = img->pixels[i][j].r + img->pixels[i][j].g + img->pixels[i][j].b;
            img->pixels[i][j].r = cinza;
            img->pixels[i][j].g = cinza;
            img->pixels[i][j].b = cinza;
            //Escrita temporária num arquivo, a título de teste.
            fprintf(output, "%d\n", img->pixels[i][j].r);
            fprintf(output, "%d\n", img->pixels[i][j].g);
            fprintf(output, "%d\n", img->pixels[i][j].b);
        }
    }
    fclose(output);
}
int Ires(int i,int j,Imagem *img){
    //Filtragem em determinado pixel passado como argumento 
    int f[5][5] = {
            {2,4,5,4,2},
            {4,9,12,9,4},
            {5,12,15,12,5},
            {4,9,12,9,4},
            {2,4,5,4,2}
    };
    int a,b;
    int valor = 0;
    for(a = -2;a <= 2;a++){
        for(b = -2;b <= 2;b++){
            if(j+a >= 0 && i+b >= 0 && j+a < img->largura && i+b < img->altura){
                valor += (f[a+2][b+2]*img->pixels[i][j].r)/A;
            }
        }
    }
    return valor;
}

void aplicarSegmentacao(Imagem *img){
    //Aplicação de segmentação na imagem em tons de cinza.
    int i,j;
    FILE *output = fopen("Catarata.ppm","w");

    fprintf(output,"%s\n","P3");
    fprintf(output, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(output, "%d %d\n",img->altura,img->largura);
    
    for(i = 0;i < img->altura;i++){
        for(j = 0; j < img->largura;j++){
            fprintf(output, "%d\n%d\n%d\n", Ires(i,j,img),Ires(i,j,img),Ires(i,j,img));
        }
    }
    fclose(output);
}

/*void gravarImagem(Imagem *img){
    FILE *output;
    output = fopen("Catarata.ppm","w");
    fprintf(output,"%s\n","P3");
    fprintf(output, "%s\n", "# CREATOR: GIMP PNM Filter Version 1.1");
    fprintf(output, "%d %d\n",img->altura,img->largura);
    for(i = 0;i < img->altura;i++){
        for(j = 0; j < img->largura;j++){
            fprintf(output, "%d\n", img->pixels[i][j].r);
            fprintf(output, "%d\n", img->pixels[i][j].g);
            fprintf(output, "%d\n", img->pixels[i][j].b);
        }
    }
    fclose(output);
}*/     
