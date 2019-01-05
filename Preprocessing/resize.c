#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

//#include "resize.h"

struct matrix {
  size_t h, w;
  double *tab;
};

struct matrix_d {
  size_t h, w;
  double **tab;
};

void print_matrix(struct matrix *mat)
{
  for(size_t i = 0; i < mat->h; i++) {
    printf("\n");
    for(size_t j = 0; j < mat->w; j++)
      if(mat->tab[j+i*mat->w] != 0)
	printf("%s %.2f   ", KRED, mat->tab[j + i * mat->w]);
      else
	printf("%s %.2f   ", KNRM, mat->tab[j + i * mat->w]);
  }
  printf("\n");
}

void print_matrix_d(double **mat, size_t lines, size_t cols) {
  for(size_t i = 0; i < lines; i++) {
    printf("\n");
    for(size_t j = 0; j < cols; j++) {
      if(mat->tab[j+i*mat->w] != 0)
	printf("%s %.2f   ", KRED, mat->tab[i][j]);
      else
	printf("%s %.2f   ", KNRM, mat->tab[i][j]);
    }
  }
  
  printf("\n");
}

struct matrix_d *from_matrix_to_matrix_d(struct matrix *mat)
{
  struct matrix_d *res = malloc(sizeof(struct matrix_d));
  res->h = mat->h;
  res->w = mat->w;
  res->tab = malloc(sizeof(double)*res->h);
  
  for(size_t i = 0; i < mat->h; i++) {
    res->tab[i] = malloc(sizeof(double)*res->w);
    for(size_t j = 0; j < mat->w; j++) {
      //res->tab[i][j] = malloc(sizeof(double));
      res->tab[i][j] = mat->tab[j+i*mat->w];
    }
  }

  free(mat->tab);
  free(mat);
  return res;
}

struct matrix *from_matrix_d_to_matrix(struct matrix_d *mat)
{
  struct matrix *res = malloc(sizeof(struct matrix));
  res->h = mat->h;
  res->w = mat->w;
  res->tab = malloc(sizeof(double)*res->h*res->w);

  for(size_t i = 0; i < mat->h; i++) {
    for(size_t j = 0; j < mat->w; j++) {
      res->tab[j+i*mat->w] = mat->tab[i][j];
    }
    free(mat->tab[i]);
  }
  
  free(mat->tab);
  free(mat);
  return res;
}

struct matrix *resize_matrix(struct matrix *src, size_t newH, size_t newW)
{

  struct matrix *dst = malloc(sizeof(struct matrix));
  dst->h = newH;
  dst->w = newW;
  dst->tab = malloc(sizeof(double)*dst->h*dst->w);

  double *temp = malloc(sizeof(double)*src->h*dst->w);
  
  size_t coefH;
  size_t coefW;
  float restH;
  float restW;
  //float refH;
  //float refW;

  if(src->w > dst->w) {
 
    //coefW = src->w/dst->w;
    restW = (float)src->w/(float)dst->w; 
    if(restW != 0)
      coefW = (size_t)restW+1;
    else
      coefW = (size_t)restW;
    //restW = restW-coefW;
    //refW = restW;
    
    //printf("%f & %ld\n", refW, coefW);

    /*
    for(size_t i = 0; i < src->h; i++) {
      double buff = 0;
      for(size_t j = 0, k = 0; j < src->w; j++, k++) {
	buff += src->tab[i*src->w+j];
	//printf("%5f\n", restW);
	if((k+1) == (coefW+(size_t)restW)) {
	  //printf("BUFF = %.f & RESTW = %.2f\n", buff, restW);
	  temp[i*dst->w+j/coefW] = (buff/((double)coefW+restW));
	  buff = 0;
	  k = 0;
	  if(restW >= 1)
	    restW -= 1;
	  restW += refW;
	}
      }
    }
    */
    for(size_t i = 0; i < src->h; i++) {
      double buff = 0;
      for(size_t j = 0; j < src->w; j++) {
	buff += src->tab[i*src->w+j];
	if((j+1)%coefW == 0) {
 	  temp[i*dst->w+j/coefW] = buff/(double)coefW;
	  buff = 0;
	}
      }
    }
  }
  
  else {
    coefW = floor((double)dst->w/(double)src->w);

    for(size_t i = 0; i < src->h; i++) {
      for(size_t j = 0, k = 0; j < src->w  && k < dst->w; j++) {
	for(size_t l = 0; l < coefW; k++, l++) {
	  temp[i*dst->w+k] = src->tab[i*src->w+j];
	}
      }
    }
  }

  if(src->h > dst->h) {
    
    restH = (float)src->h/(float)dst->h; 
    if(restH != 0)
      coefH = (size_t)restH+1;
    else
      coefH = (size_t)restH;
    //coefH = (int)/*floor*/((double)src->h/(double)dst->h);
    
    for(size_t i = 0; i < dst->w; i++) {
      double buff = 0;
      for(size_t j = 0; j < src->h; j++) {
	buff += temp[j*dst->w+i];
	
	if((j+1)%coefH == 0) {
	  dst->tab[j/coefH*dst->w+i] = buff/(double)coefH;
	  buff = 0;
	}
      }
    } 
  }

  else {
    coefH = floor((double)dst->h/(double)src->h);

    for(size_t i = 0; i < dst->w; i++) {
      for(size_t j = 0, k = 0; j < src->h; j++) {
	for(size_t l = 0; l < coefH; k++, l++) {
	  dst->tab[k*dst->w+i] = temp[j*dst->w+i];
	}
      }
    }
  }

  
  free(temp);

  return dst;
}

struct matrix_d *resize_matrix_d(struct matrix_d *src, size_t newH, size_t newW)
{
  struct matrix *temp = from_matrix_d_to_matrix(src);
  return from_matrix_to_matrix_d(resize_matrix(temp, newH, newW));
}

int main()
{
  struct matrix *m = malloc(sizeof(struct matrix));
  m->h = 20;
  m->w = 10;
  m->tab = malloc(sizeof(double)*m->h*m->w);

  for(size_t i = 0, j = 0; i < m->h && j < m->w; i+=1, j+=1) {
      m->tab[i*m->w+j] = 1;
      m->tab[(m->w-i)*m->w+j] = 1;
  }

  m->tab[5] = 1;

  
  print_matrix(m);
  
  struct matrix *m_resize = resize_matrix(m, 60, 10);
  print_matrix(m_resize);
}
