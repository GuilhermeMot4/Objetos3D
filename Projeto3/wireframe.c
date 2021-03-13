// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "datatypes.h"
#include "objread.h"
#include "graphics.h"
#include "perspect.h"

int main(int argc, char **argv){

	int i,j,a,b,alocaVertice, totalVertice, alocaFace, totalFace, numV;
	double xc, yc, zc,*xP, *yP,*xD,*yD,*coordenada;
	char l[128], l_tmp[128];

	Vertices *v;
	Faces *f;

	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Event evento;

	FILE *arq;

	//alocação inicial dos vetores
	v  = calloc (1000, sizeof(Vertices));
	f  = calloc (1000, sizeof(Faces));
	
	//abertura arquivo obj
	if(argc == 1){
		arq = stdin;
	}else{
		arq = fopen(argv[1], "r");
		if(!arq){
			printf("Erro ao abrir arquivo de leitura!\n");
			exit(1);
		}
	}


	i = 0; //numero de vertices
	alocaVertice = 1; //contador para alocacao de vertices
	totalVertice = 1000;
	j = 0; //numero de faces 
	alocaFace = 1; //contador para alocacao de faces
    totalFace = 1000;
    numV = 0; //numero de vertices em uma face

	while(!feof(arq)){ //leitura do arquivo obj
		fgets(l, 128, arq);
		if(!strncmp(l, "v ", 2)){
			leVertice(v, i, l);
			i++;

			if(i == totalVertice){
                alocaVertice++;
                totalVertice = alocaVertice * 1000;
                v = realloc(v, totalVertice * sizeof(Vertices));
            }
        }else if (!strncmp (l, "f ", 2)){
            strcpy(l_tmp, l);
            numV = numVert(l_tmp); //calcula quantos vertices cada face contem
            f[j].numV = numV;
            f[j].valores = malloc (numV * sizeof(int));

            leFace(f, j, l);
            j++;

            if(j == totalFace){
                alocaFace++;
                totalFace = alocaFace * 1000;
                f = realloc(f, totalFace * sizeof(Faces));
            }
        }
	}

	xP = calloc (i, sizeof(double));
	yP = calloc (i, sizeof(double));
	xD = calloc (i, sizeof(double));
	yD = calloc (i, sizeof(double));
	coordenada = calloc (i, sizeof(double));

	//calcula coordenadas iniciais da camera [xc yc zc]
	inicCamera(coordenada,v,i,&xc,&yc,&zc);

    //inicializacao dos recursos da biblioteca SDL
    if(!initJanela(&window, &renderer)){
    	printf("Erro na inicialização!\n");
    }else{ //calculo e exibicao na janela
    	int fim = 0;
    
    	while(fim != 1){ //ate evento QUIT

    		//redefine cor e limpa a tela
    		SDL_SetRenderDrawColor(renderer,0,0,0,100);
			SDL_RenderClear(renderer);

			//xv -> xp   yv ->yp
			calculaPerspectiva(xP, yP, i,v, xc,yc,zc);

			//xp -> xd   yp ->yd
			converteCoord(xP,yP,xD,yD,i);

			//escreve as retas entre os vertices
			for (a=0; a < j; a++){
	            int v1, v2, x1, x2, y1, y2;

	            SDL_SetRenderDrawColor(renderer,0,255,0,100); //cor das linhas

	            for (b=0; b < f[a].numV-1; b++){
	                v1 = f[a].valores[b]-1;
	                v2 = f[a].valores[b+1]-1;

	                x1 = xD[v1];
	                y1 = yD[v1];
	                x2 = xD[v2];
	                y2 = yD[v2];

	                SDL_RenderDrawLine (renderer, x1, y1, x2, y2); //desenha reta
	            }

	            v1 = f[a].valores[b]-1;
	            v2 = f[a].valores[0]-1;

	            x1 = xD[v1];
	            y1 = yD[v1];
	            x2 = xD[v2];
	            y2 = yD[v2];

	            SDL_RenderDrawLine (renderer, x1, y1, x2, y2);
	       		}

			SDL_RenderPresent(renderer); //exibe na tela

			//leitura dos eventos do teclado
			while (SDL_PollEvent(&evento)) {
	            switch (evento.type){
		            case SDL_QUIT:
		                fim = 1;
		                break;
		            case SDL_KEYDOWN:
		                if(evento.key.keysym.sym == SDLK_LEFT){
		                	xc--; 
		                }else if (evento.key.keysym.sym == SDLK_RIGHT){
		                	xc++; 
		                }else if (evento.key.keysym.sym == SDLK_UP){
		                	yc++; 
		                }else if (evento.key.keysym.sym == SDLK_DOWN){
		                	yc--; 
		                }else if (evento.key.keysym.sym == SDLK_ESCAPE)
		                    fim = 1;
		                else if (evento.key.keysym.sym == SDLK_q)
		                    fim = 1;
	                	break;
		        }
            }
	
		}
    }

    //finalização
    free(v);
    free(f);
    free(xP);
    free(yP);
    free(xD);
    free(yD);
    free(coordenada);
    
    fclose(arq);

    closeJanela(window, renderer); //fecha a janela
    
 	return 0;
 }
