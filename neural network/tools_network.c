#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
 
#include "function.h"
#include "tools_network.h"
#include "correction.h"

matrix* makeLW(int L[], int size)
{
  matrix* lw = NULL;
  lw = malloc((size-1) * sizeof(matrix));
  if(lw == NULL){
      exit(0);
}


  for( int i= 0 ; i < size-1; i++)
    {

      double** list = matw(L[i],L[i+1]);
      lw[i].width = L[i+1];
      lw[i].height = L[i] ;
      lw[i].List = list ;
    }
    return lw;
}

double** matw(int height, int width)
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

matrix* makeLayer(int L[], int size, int nb)
{
  matrix* layer = NULL;
  layer = malloc((size) * sizeof(matrix));
  if(layer == NULL){
      exit(0);
  }


  for( int i= 0 ; i < size; i++)
    {
      double** list = NULL;
      list = malloc((nb) * sizeof(double*));
      if(list == NULL){
          exit(0);
      }
      for(int j = 0; j < nb;j++)
      {
        if((list[j] = malloc(sizeof(double) * L[i])) == NULL)
        {exit(0);}
      }
      
      layer[i].width = L[i];
      layer[i].height = nb ;
      layer[i].List = list ;
    }
    return layer;
}

void forward( int sizeL, matrix* lw, matrix* layer,
 matrix* biais, matrix* lz)
{
  double** l;
  double** l1;
  for(int i = 0; i < sizeL-1; i++)
  {
    l = layer[i].List;
    l1 = layer[i+1].List;
    mul(l, lw[i].List, layer[i].height, lw[i].height, lw[i].width, l1);
    add(l1, biais[i+1].List, layer[i+1].height, layer[i+1].width );
    copy(l1, lz[i+1].List ,layer[i+1].height, layer[i+1].width);
    vector_apply(sigmoid, l1, layer[i+1].height, layer[i+1].width,l1);
    
  }
}

void copy(double** layer , double** lz , int height , int width)
{
  for(int i = 0; i < height;i++)
  {
    for(int j = 0; j < width;j++)
    {
      lz[i][j] = layer[i][j] ;
    }
  }
}

void putEnter(matrix* layer, double* enter)
{
    for(int j = 0; j < layer[0].width;j++)
    {
      layer[0].List[0][j] = enter[j];
    }
}


void savealltofile(matrix* l, int nbelement, char* path)
{ 
  FILE* fichier = fopen(path, "w+");
  for(int i =0; i < nbelement ; i++)
  {
    matricefile(l[i].List,l[i].height ,l[i].width,fichier);
  } 
  fclose(fichier); 
}
matrix* alltomatrice(int nbelement, char* path)
{ 
  matrix* recup = malloc(2 * sizeof(matrix));
  recup[0].List = filetomatrice(750,300,0, path);
  recup[0].height = 750;
  recup[0].width = 300;
  for(int i =1; i < nbelement ; i++)
  {
    recup[i].List = filetomatrice(300,52 
    ,750*300, path);
    recup[i].height = 300;
    recup[i].width = 52;
    
  }
  return recup;
}

matrix* alltomatriceb(char* path)
{ 
  matrix* recup = malloc(3 * sizeof(matrix));
  recup[0].List = filetomatrice(1,750,0, path);
  recup[0].height = 1;
  recup[0].width = 750;
  recup[1].List = filetomatrice(1,300,750, path);
  recup[1].height = 1;
  recup[1].width = 300;
  recup[2].List = filetomatrice(1,52,750+300, path);
  recup[2].height = 1;
  recup[2].width = 52;
  return recup;
}


void matricefile (double** matrice, int height, int width, FILE* fichier)
{
  for(int i = 0; i < height;i++)
    {
      for(int j = 0; j < width;j++)
	{
	  fprintf(fichier,"%4g",matrice[i][j]);
	  fprintf(fichier,"\n");
	}
    }
}

char* gline(FILE* f)
{
  size_t len = 0;
  ssize_t read;
  char* line = NULL;
  if ((read = getline(&line,&len,f))==-1)
    {
      exit(0);
    }
  line[read-1]=0;
  return line;
}


double** filetomatrice(int height, int width,int delta,char* path)  
 {
    
    double** l  = malloc((height) * sizeof(double*));
    for(int i =0; i< height ; i++)
      {
	      l[i] = malloc(sizeof(double) * width); 
      }
    FILE *fichier =fopen(path, "r");
    int i =0;
    int j =0;
    int x = 1;
    double value;
    char* line = NULL;
    while (delta--)
      {
        line = gline(fichier);
	      sscanf(line,"%lf",&value);
      }
    while (x <= height*width)
      {
	    line = gline(fichier);
	    sscanf(line,"%lf",&value);
	    if (j == width)
	      {
	        j=0;
	        i++;
	      }
	    //printf("%d",i);
	    l[i][j] = value;
	    j++;
	    x++;
	
      }
    fclose(fichier);
    return l;  
}  


int findindex (network* net,int L[])
{
  matrix mat = net->layer[net->size-1];
  int index = 0;
  for(int i = 0; i<L[(net->size)-1];i++)
   {
      if (mat.List[0][index] < mat.List[0][i])
	{
 	   index = i;
	}
   }
  return index;
}

int verifline(matrix letter)
{
   for(int i = 0; i < (letter.height)-1 ; i++)
    {
    for(int j = 0; j < (letter.width)-1; j++)
	{
	   if (letter.List[i][j] ==0)
		return 0;
	}
    }
    return 1;
}
int random_index(int nb)
{
  return (int)(((double)rand() /(double)RAND_MAX)*nb);
}

int IsEmpty(char * nom_fichier)
{
  FILE*fichier =fopen(nom_fichier,"r");
  int caracterePremier = 0;
  
     //On lit le prmeier caractère du fichier
     caracterePremier = fgetc(fichier);
     if(caracterePremier==EOF)
     {
         return 1;//le fichier est vide donc on retourne 1
     }
     return 0;
}
matrix removewhite(matrix image)
{
  //printf("%d ligne de l'image = ",image.height);
  //printf("\n");
  //printf("%d colone de l'image =",image.width);
  //printf("\n");
  int minline = firstline(image);
  //printf("%d minline",minline);
  //printf("\n");
  int maxline = endline(image);
  //printf("%d maxline",maxline);
  //printf("\n");
  int maxcolum = endcolum(image);
  //printf("%d maxcolum",maxcolum);
  //printf("\n");
  int mincolum = firstcolum(image);
  //printf("%d mincolum",mincolum);
  //printf("\n");
  double** l  = matw((maxline-minline), (maxcolum-mincolum));
  int a = 0;
  int b = 0;
  for (int i = minline; i < maxline; i++)
  {
    for (int j = mincolum; j < maxcolum; j++)
    {
	l[a][b]=image.List[i][j];
	b++;
    }
    a++;
    b = 0;
  }
  image.List=l;
  image.height=(maxline-minline);
  image.width=(maxcolum-mincolum);
  return image;
}
int firstcolum(matrix image)
{
  for (int i = 0; i < (image.height)-1; i++)
  {
    for (int j = 0; j < (image.width)-1; j++)
    {
	if(image.List[j][i]==1)
	  return i;
    }
  }
  return 0;
}

int endcolum(matrix image)
{
  int x = firstcolum(image);
  for (int i = (image.width)-1; i >=x; i--)
  {
    for (int j = (image.height)-1; j >0; j--)
    {
	if (image.List[j][i]==1)
      	{
	   return i;
      	}
    }
  }
  return (image.width)-1;
}

int firstline(matrix image)
{
 for (int j = 0; j < (image.height)-1; j++)
  {
    for (int i = 0; i < (image.width)-1; i++)
    {
      if (image.List[j][i]==1)
      {
	return j;
      }
    }
  }
  return (image.height);
}
int endline(matrix image)
{
  for (int j = (image.height)-1; j >= 0; j--)
  {
    for (int i = 0; i < image.width; i++)
    {
      if (image.List[j][i]==1)
      {
	return j+1;
      }
    }
  }
  return (image.height)-1;
}

matrix* randmatrix(int size , int L[], matrix* biais)
{
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j < L[i]; j++)
    {
      biais[i].List[0][j] = ((double)rand() /(double)RAND_MAX)* 40 - 20;
    }
  }
  return biais;
}
