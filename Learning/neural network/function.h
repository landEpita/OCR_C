/*
 * function.h: some useful linear function operations
 *
 * 2017 Marwan Burelle / EPITA
 */
 
#ifndef _SOMEfunction_function_H_
#define _SOMEfunction_function_H_

#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"

/*
 * func_t: function pointer type
 */
typedef double (*func_t)(double);
typedef struct network network;
typedef struct matrix matrix;
typedef struct tuple tuple;




 
/*
 * vector_apply(f, vect, size, res)
 * applies a function to all element on a vector of size n
 * for i in 0..size, res[i] = f[vect[i]]
 */
void vector_apply(func_t f, double** vect, int height,int width,double** res);


double sigmoid(double x);

void mul(double** m1, double** m2, int n, int m, int p, double** res);

void print_matrix(double** mat, size_t cols, size_t lines);

void add(double** m1,double** m2, size_t cols , size_t lines);
void pprint(matrix* l, int size);
 
double abso(double i);

double neural_network_training (network* reseau,tuple enter, int L[]);

network* make_network(int size , int L[]);

double errtaux2(network * net, char letter, int L[]);

#endif /* _SOMEfunction_function_H_ */
 
