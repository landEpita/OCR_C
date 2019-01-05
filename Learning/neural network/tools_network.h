#ifndef _TOOLSNET_H_
#define _TOOLSNET_H_

#include "function.h"
#include "correction.h"

typedef struct matrix matrix;
struct matrix
{
  int width;
  int height;
  double** List;
};

typedef struct tuple tuple;
struct tuple
{
  matrix mat;
  double* list;
  char inputsChar;
};

typedef struct network network;
struct network
{
    int size;
    matrix* lw;
    matrix* layer;
    matrix* lz;
    matrix* biais;
    matrix* error;
  
};
int verifline(matrix letter);
void matricefile (double** matrice, int col, int line,FILE* fichier);
double** filetomatrice(int line, int col, int delta, char* path);
void savealltofile(matrix* matrice, int nbelement, char* path);
matrix* alltomatrice(int nbelement, char* path);
int findindex (network* net,int L[]);
matrix* makeLW(int L[], int size);
double** matw(int height, int width);
matrix* makeLayer(int L[], int size, int nb);
void forward(int sizeL, matrix* lw, matrix* layer,
 matrix* biais, matrix* lz);
void putEnter(matrix* layer, double* enter);
void copy(double** layer , double** lz , int height , int width);
void serialisation ( char *file, int L[], matrix* lw, int size);

matrix* alltomatriceb(char* path);

int random_index(int nb);
int IsEmpty(char * nom_fichier);
matrix removewhite(matrix image);
int firstcolum(matrix image);
int endcolum(matrix image);
int firstline(matrix image);
int endline(matrix image);
matrix* randmatrix(int size , int L[], matrix* biais);

#endif /* _TOOLSNET_H_ */
