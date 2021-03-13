// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>

#include "datatypes.h"

//leitura dos vertices
void leVertice(Vertices *v , int pos, char *str){
    double valor;
    int i;
    char *token, *ptr;

    i = 0;

    token = strtok(str, " ");

    while(token != NULL){
        token = strtok(NULL, " ");
        if(token != NULL){
            //num_vert = strtod(token, NULL);
            valor = strtod(token, &ptr);
            if (i == 0)
                v[pos].x = valor;
            else if (i == 1)
                v[pos].y = valor;
            else
                v[pos].z = valor;
            i++;
        }
    }
}

//leitura das faces
void leFace(Faces *f , int pos, char *str){
    int valor, str_tam, i;
    char *token, *s, *pch;
    char *ptr;

    i = 0;

    token = strtok (str, " ");

    while (token != NULL){
        token = strtok(NULL, " ");

        if(token != NULL){
            pch = strchr (token, '/');
        
            if (pch != NULL){
                str_tam = pch - token + 1;
                s = (char *) malloc (str_tam * sizeof (char));
                strncpy(s, token, str_tam);
                valor = (int) strtol (s, &ptr, 10);

                f[pos].valores[i] = valor;
                i++;

                free(s);
            }
            else if (isdigit (token[0])){
                //num_face = (int) strtol (token, NULL, 10);
                valor = (int) strtol (token, &ptr, 10);

                f[pos].valores[i] = valor;
                i++;
            }
        }
    }
}

int numVert(char *str){
    int cont;
    char *token, *pch;

    cont = 0;

    token = strtok (str, " ");

    while (token != NULL)
    {
        token = strtok(NULL, " ");

        if(token != NULL)
        {
            pch = strchr (token, '/');
    
            if (pch != NULL || isdigit (token[0]))
                cont++;
        }
    }
    return cont;
}