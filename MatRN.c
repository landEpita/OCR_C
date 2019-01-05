#include <stdio.h>
#include <stdlib.h>
#include "MatRN.h"

//Build une matrice aleatoire avec les dimensions
double** matbuild(int height, int width)
{
  double** w = NULL;
  w = malloc((height) * sizeof(double*));
  if(w == NULL){
      exit(0);
  }
  for(int i = 0; i < height;i++)
  {
    if((w[i] = malloc(sizeof(double) * width)) == NULL)
    {exit(0);}
    for(int j = 0; j < width;j++)
    {
      w[i][j]=((double)rand() /(double)RAND_MAX)*20 -10;
    }
  }

  return w;
}


void print_matrix_beautiful(double** mat, size_t cols , size_t lines)
{
  for(size_t i =0; i < cols; i++)
    {
      for (size_t j = 0; j < lines; j++)
        {

            printf("%4g ",(float)(mat[i][j]));
        }
      
      printf("\n");
    }
}
//Met une valeur x autour de la matrice
double** onearound(double** mat,size_t x,size_t height,size_t width)
{
    
    height +=1;
    width +=1;
    double** w = NULL;
    w = matbuild(height+1,width+1);
    if(w == NULL){
        exit(0);
    }
    for(size_t k = 0; k < width +1;k++)
    {
        w[0][k] = x;
        w[height][k] = x;
    }
    
    for(size_t i = 1; i < height;i++)
    {
      
      w[i][0] = x;
      for(size_t j = 1; j < width ;j++)
      {
        w[i][j]=mat[i-1][j-1];
      }
      w[i][width] = x;
    }
  
    return w;
}
//moyenne autour d' un point
double average(double** ref,double** mat, size_t x , size_t y, size_t sizeref )
{
    double s = mat[x-1][y-1] * ref[0][0];
    s += mat[x][y-1]  *   ref[0][1];
    s += mat[x+1][y-1] * ref[0][2];
    s += mat[x-1][y] *   ref[1][0];
    s += mat[x][y] *     ref[1][1];
    s += mat[x+1][y] *   ref[1][2];
    s += mat[x-1][y+1] * ref[2][0];
    s += mat[x][y+1] *   ref[2][1];
    s += mat[x+1][y+1] * ref[2][2];
    double t = (double)(s)/(double)(sizeref* sizeref);
    return (t);
}
//Mise a zero de ceux negatifs
double** Relu(double** mat,size_t width,size_t height)
{
    for(size_t i =0 ; i<height;i++)
    {
        for(size_t j =0 ; j<width;j++)
        {
            if(mat[i][j]<0)
            {
                mat[i][j] = 0;
            }
        }
    }
    return mat;
}
//Max de 4 entrees
double max(double a, double b, double c, double d)
{
    if(c>d)
    {
        d = c;
    }
    else
    {
        c = d;
    }
    if(b>c)
    {
        c = b ;
    }
    else
    {
        b = c;
    }
    if(a>b)
    {
        b = a;
    }
    else
    {
        a = b;
    }
    return a;
}
/*
mat = matrice d' entree
height et width ses dimensions respectivement
*/
double** maxpooling(double** mat,size_t height, size_t width)
{
     mat = onearound(mat,0,height,width);
     height +=2;
     width +=2;
    double** final = matbuild(height/2,width/2);
    size_t y =0;
    for(size_t i =1 ; i<(height);i+=2)
    {
        size_t x =0;
        for(size_t j =1 ; j<(width);j+=2)
        {
            final[y][x] = max(mat[i][j],mat[i+1][j],mat[i+1][j+1],mat[i][j+1]);
            x++;
        }
        y++;
    }
    return final;

}
/*
mat = matrice d' entree
height et width ses dimensions respectivement
ref = matrice de reference celle pour les paternes
sizeref = longeur d' un cote de la matrice de reference de preference 3 vu que -2
*/
double** convolution(double** mat, size_t height,size_t width,double** ref, size_t sizeref)
{
   
    double** final = matbuild(height-2,width-2);
    for(size_t i =1 ; i<height-1;i++)
    {
        for(size_t j =1 ; j<width-1;j++)
        {
            
            
            final[i-1][j-1] = average(ref,mat,i,j,sizeref);
        }
    }
    return final;

}
double** transform(double** mat, size_t height,size_t width)
{
    double maxi = max(mat[0][0],mat[0][1],mat[1][0],mat[1][1]);
    for(size_t i =0 ; i<height;i++)
    {
        for(size_t j =0 ; j<width;j++)
        {
            if(mat[i][j] >= maxi-0.000001)
            {
                mat[i][j] = 1;
            }
            else
            {
                mat[i][j] = 0.55;
            }
        }
    }
    return mat;
}
double** CRM(double** mat,size_t height,size_t width,double** ref,size_t sizeref)
{
    while(height > 3)
    {
        mat = convolution(mat,height,width,ref,sizeref);
        height -= 2;
        width -= 2;
        mat = Relu(mat,height,width);
    }
    mat = maxpooling(mat,height,width);
    
    height -= 1;
    width -= 1;

    mat = transform(mat,height,width);
    return mat;

}
double** exemple_ref()
{
    double** r = matbuild(3,3);
    //Ref
    r[0][0] = -1;
    r[0][1] = -1;
    r[0][2] = 1;
    r[1][0] = -1;
    r[1][1] = 1;
    r[1][2] = -1;
    r[2][0] = 1;
    r[2][1] = -1;
    r[2][2] = -1;
    return r;
}
double** mat_init()
{
    double** m = matbuild(9,9);
    // ligne 1
    m[0][0] = -1;
    m[0][1] = -1;
    m[0][2] = -1;
    m[0][3] = -1;
    m[0][4] = -1;
    m[0][5] = -1;
    m[0][6] = -1;
    m[0][7] = -1;
    m[0][8] = -1;

    //ligne 2
    m[1][0] = -1;
    m[1][1] = 1;
    m[1][2] = -1;
    m[1][3] = -1;
    m[1][4] = -1;
    m[1][5] = -1;
    m[1][6] = -1;
    m[1][7] = 1;
    m[1][8] = -1;
    //ligne 3
    m[2][0] = -1;
    m[2][1] = -1;
    m[2][2] = 1;
    m[2][3] = -1;
    m[2][4] = -1;
    m[2][5] = -1;
    m[2][6] = 1;
    m[2][7] = -1;
    m[2][8] = -1;

    //ligne 4
    m[3][0] = -1;
    m[3][1] = -1;
    m[3][2] = -1;
    m[3][3] = 1;
    m[3][4] = -1;
    m[3][5] = 1;
    m[3][6] = -1;
    m[3][7] = -1;
    m[3][8] = -1;


    //ligne 5
    m[4][0] = -1;
    m[4][1] = -1;
    m[4][2] = -1;
    m[4][3] = -1;
    m[4][4] = 1;
    m[4][5] = -1;
    m[4][6] = -1;
    m[4][7] = -1;
    m[4][8] = -1;

    //ligne 6
    m[5][0] = -1;
    m[5][1] = -1;
    m[5][2] = -1;
    m[5][3] = 1;
    m[5][4] = -1;
    m[5][5] = 1;
    m[5][6] = -1;
    m[5][7] = -1;
    m[5][8] = -1;


    //ligne 7
    m[6][0] = -1;
    m[6][1] = -1;
    m[6][2] = 1;
    m[6][3] = -1;
    m[6][4] = -1;
    m[6][5] = -1;
    m[6][6] = 1;
    m[6][7] = -1;
    m[6][8] = -1;

    //ligne 8
    m[7][0] = -1;
    m[7][1] = 1;
    m[7][2] = -1;
    m[7][3] = -1;
    m[7][4] = -1;
    m[7][5] = -1;
    m[7][6] = -1;
    m[7][7] = 1;
    m[7][8] = -1;
    // ligne 9
    m[8][0] = -1;
    m[8][1] = -1;
    m[8][2] = -1;
    m[8][3] = -1;
    m[8][4] = -1;
    m[8][5] = -1;
    m[8][6] = -1;
    m[8][7] = -1;
    m[8][8] = -1;

    return m;

}
