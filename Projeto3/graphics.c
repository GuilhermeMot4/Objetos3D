// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "datatypes.h"

bool initJanela(SDL_Window **window, SDL_Renderer **renderer){
	bool sucess = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        sucess = false;
	}else{
        *window = SDL_CreateWindow("Wireframe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (*window == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            sucess = false;
        }else{           
            *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);
    		if (*renderer == NULL){
        		printf("Renderer could not initialize! SDL_Error: %s\n", SDL_GetError());
        		sucess = false;
    		}
        SDL_SetRenderDrawColor(*renderer, 0, 0, 0,100);
    	SDL_RenderClear(*renderer);
    	}
    }
    return sucess;	
}

void closeJanela(SDL_Window *window, SDL_Renderer *renderer){
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	window = NULL;
	SDL_DestroyWindow(window);
	SDL_Quit();
}