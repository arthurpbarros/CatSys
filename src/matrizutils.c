#include "matrizutils.h"
#define A 1/159

void aplicarSegmentacao(Imagem *img){
	int f[5][5] = {
		{2,4,5,4,2},
		{4,9,12,9,4},
		{5,12,15,12,5},
		{4,9,12,9,4},
		{2,4,5,4,2}
	}
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
					fprintf(output, "%d\n", nova->pixels[i][j].r);
            		fprintf(output, "%d\n", nova->pixels[i][j].g);
           	 		fprintf(output, "%d\n", nova->pixels[i][j].b);
				}
			}
		}
	}
	fclose(output);
}