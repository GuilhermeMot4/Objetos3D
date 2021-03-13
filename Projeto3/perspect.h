// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#ifndef __PERSPECT__
#define __PERSPECT__

double min(double *vetor, int tam);

double max(double *vetor, int tam);

void inicCamera(double *coordenada, Vertices *v, int i, double *xc, double *yc, double *zc);

void calculaPerspectiva(double *xP, double *yP, int i, Vertices *v, double xc, double yc, double zc);

void converteCoord(double *xP, double *yP, double *xD, double *yD, int i);

#endif