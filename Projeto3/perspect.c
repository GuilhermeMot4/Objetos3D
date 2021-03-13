// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <stdio.h>
#include <stdlib.h>

#include "datatypes.h"

double min(double *vetor, int tam){
	int i;
	double menor = vetor[0];
	for(i = 1;i < tam;i++){
		if(vetor[i] < menor){
			menor = vetor[i];
		}
	}
	return menor;
}

double max(double *vetor, int tam){
	int i;
	double maior = vetor[0];
	for(i = 1;i < tam;i++){
		if(vetor[i] > maior){
			maior = vetor[i];
		}
	}
	return maior;
}

//coordenadas iniciais da camera 
void inicCamera(double *coordenada, Vertices *v, int i, double *xc, double *yc, double *zc){
	int a;
	for(a = 0;a < i;a++){
		coordenada[a] = v[a].x;
	}
	*xc = (min(coordenada, i) + max(coordenada, i))/ 2;
	for(a = 0;a < i;a++){
		coordenada[a] = v[a].y;
	}
	*yc = (min(coordenada, i) + max(coordenada, i))/ 2;
	for(a = 0;a < i;a++){
		coordenada[a] = v[a].z;
	}
	*zc = max(coordenada, i)*2;
}

//calcula projecoes 2D dos vertices 3D
void calculaPerspectiva(double *xP, double *yP, int i, Vertices *v, double xc, double yc, double zc){
	int a;

	for(a = 0;a < i;a++){
		xP[a] = xc + zc * ( (v[a].x - xc) / (v[a].z + zc) );
	}

	for(a = 0;a < i;a++){
		yP[a] = yc + zc * ( (v[a].y - yc) / (v[a].z + zc) );
	}
	
}

//conversao para coordenadas de tela
void converteCoord(double *xP, double *yP, double *xD, double *yD, int i){
	double xcen,xdif,ycen,ydif,escx,escy,escala,
	escala_min,xd,yd,menorX,menorY,maiorX,maiorY;
	int a;

	menorX = min(xP, i);
	maiorX = max(xP, i);
	xcen = (maiorX + menorX) / 2;
	xdif = maiorX - menorX;

	menorY = min(yP, i);
	maiorY = max(yP, i);	
	ycen = (maiorY + menorY) / 2;
	ydif = maiorY - menorY;

	//escala
	escx = SCREEN_WIDTH / xdif;
	escy = SCREEN_HEIGHT / ydif;

	if(escx > escy){
		escala_min = escy;
	}else{
		escala_min = escx;
	}

	escala = escala_min;

	//converte os pontos projetados para coordenadas de tela (xp ->xd)
	for(a = 0;a < i;a++){
		xd = ( (xP[a] - xcen) * escala) + SCREEN_WIDTH / 2;
    	yd = ( (yP[a] - ycen) * escala) + SCREEN_HEIGHT / 2;

    	xD[a] = SCREEN_WIDTH - xd;
    	yD[a] = SCREEN_HEIGHT - yd;	
	}
}