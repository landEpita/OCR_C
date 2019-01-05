#ifndef _MRN_H_
#define _MRN_H_

#include <stdio.h>
#include <stdlib.h>
double** matbuild(int height, int width);
void print_matrix_beautiful(double** mat, size_t cols , size_t lines);
double** onearound(double** mat,size_t x,size_t height,size_t width);
double average(double** ref,double** mat, size_t x , size_t y, size_t sizeref );
double** Relu(double** mat,size_t width,size_t height);
double max(double a, double b, double c, double d);
double** maxpooling(double** mat,size_t height, size_t width);
double** convolution(double** mat, size_t height,size_t width,double** ref, size_t sizeref);
double** transform(double** mat, size_t height,size_t width);
//test pour la matrice de reference 
double** exemple_ref();
//test pour la matrice entree 
double** mat_init();
//CRM te fais tout utiliser juste celle-ci
double** CRM(double** mat,size_t height,size_t width,double** ref,size_t sizeref);

#endif