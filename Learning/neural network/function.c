#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
 
#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"




/*
 * vector_apply(f, vect, size, res)
 * applies a function to all element on a vector of size n
 * for i in 0..size, res[i] = f[vect[i]]
 */
void vector_apply(func_t f, double** vect, 
int height, int width,double** res)
{
  for(int i = 0; i < height;i++)
    {
      for(int j = 0; j < width;j++)
      {
      res[i][j] = f(vect[i][j]);
      }
    }
}


double sigmoid(double x)
{
  return 1 / (1 + exp(-x));
}
//
void mul(double** m1, double** m2, int m1H, int m, int m2L, double** res)
{
  for(int i =0; i < m1H ;i++)//lines
    {
      for(int j =0; j < m2L ;j++) // cols
	      {
	        for(int h =0; h < m ;h++)
	         {
	          res[i][j]+= m1[i][h]*m2[h][j];
	         }
        }       
    }
}
void print_matrix(double** mat, size_t cols , size_t lines)
{
  for(size_t i =0; i < cols; i++)
    {
      for (size_t j = 0; j < lines; j++)
        {
          printf("%4g|",mat[i][j]);
        }
      
      printf("\n");
    }
}
void add(double** m1,double** m2, size_t cols , size_t lines)
{
  for(size_t i =0; i < cols; i++)
    {
      for (size_t j = 0; j < lines; j++)
        {
          m1[i][j] += m2[i][j]; 
        }
    }
}

void pprint(matrix* l, int size)
{
  for(int i =0; i < size ; i++)
  {
    print_matrix( l[i].List,l[i].height ,l[i].width);
    printf("\n");
  }
}


double abso(double i)
{
  if(i < 0)
  {
    return -1 * i;
  }
  return i;
}
double neural_network_training (network* reseau,tuple enter, int L[])
{
  putEnter(reseau->layer, enter.list);
  forward(reseau->size,reseau->lw, reseau->layer, reseau->biais, reseau->lz);
  puterror(reseau->error,reseau->layer,enter.inputsChar , reseau->size);
  double terr = errtaux2(reseau, enter.inputsChar, L);
  corr(reseau->layer, reseau->lz, reseau->lw, reseau->error,
  reseau->biais, L, reseau->size);
  return terr;
}

network* make_network(int size , int L[])
{
  network *net = malloc(sizeof(network));
  net->size = size;
  net->lw  = makeLW(L, size);
  net->layer = makeLayer(L, size, 1);
  net->lz = makeLayer(L, size , 1);  //double val_abs;
  net->biais = randmatrix(size, L, makeLayer(L, size , 1));
  net->error = makeLayer(L, size , 1);
  return net;
}


double errtaux2(network * net, char letter, int L[])
{
  int a = findindex(net, L);
  int b = neuroneactif(letter);
  if(a == b)
  {
    return 1;
  }
  return 0;
}
