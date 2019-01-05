#ifndef _CORRECTION_H_
#define _CORRECTION_H_

#include "function.h"
#include "tools_network.h"


typedef struct matrix matrix;
double deriver_sigmoid(double x);
void corr(matrix* layer,matrix* lz, matrix* lw,matrix* error,
matrix* biais,int L[],int size);
void puterror(matrix* error, matrix* layer, char letter, int size);

#endif /* _CORRECTION_H_ */
