# ifndef RESIZE_H_
# define RESIZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  Matrix linear with a simple pointer 
 */
struct matrix {
  size_t h, w;
  double *tab;
};

/*
  Matrix with a double pointer
 */
struct matrix_d {
  size_t h, w;
  double **tab;
};


/*
  Print a struct matrix
 */
void print_matrix(struct matrix *mat);

/*
  Print a struct matrix_d
 */
void print_matrix_d(double **mat, size_t lines, size_t cols);

/*
  Convert a matrix to a matrix_d
 */
struct matrix_d *from_matrix_to_matrix_d(struct matrix *mat);

/*
  Convert a matrix_d to a matrix
 */
struct matrix *from_matrix_d_to_matrix(struct matrix_d *mat);

/*
  Resize a struct matrix to the given height & width
 */
struct matrix *resize_matrix(struct matrix *src, size_t newH, size_t newW);

/*
  Resize a struct matrix_d to the given height & width
 */
struct matrix_d *resize_matrix_d(struct matrix_d *src, size_t newH, size_t newW);

# endif
