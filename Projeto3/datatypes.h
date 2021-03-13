// Nome: Guilherme Ferreira Mota 
//GRR: 20197268
#ifndef __DATATYPES__
#define __DATATYPES__

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct Vertices{
	double x;
	double y;
	double z;
}Vertices;

typedef struct Faces
{
    int numV;
    int *valores;
} Faces;

typedef enum
{
  FALSE = 0,
  False = 0,
  false = 0,
  TRUE  = 1,
  True  = 1,
  true  = 1
}bool;

#endif