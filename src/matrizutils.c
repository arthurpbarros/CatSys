#define A 1/159
void aplicarSegmentacao(Imagem *img){
	int f[5][5] = {
		{2,4,5,4,2},
		{4,9,12,9,4},
		{5,12,15,12,5},
		{4,9,12,9,4},
		{2,4,5,4,2}
	}
	int i,j;
	for(i = -5/2; i <= 5/2;i++){
		for(j = -5/2; j <= 5/2;j++){
			for(i = 0;i < img->altura;i++){
				for(j = 0;j < img->largura;j++){
					
				}
			}
		}
	}
}