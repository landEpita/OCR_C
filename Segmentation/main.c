# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
# include "segmentation.h"

void print_tab(double** mat, size_t cols , size_t lines)
{
  for(size_t i =0; i < cols; i++)
    {
      for (size_t j = 0; j < lines; j++)
        {
          printf("%4g",mat[i][j]);
        }
      
      printf("\n");
    }
}

void pprint(matrix* l, int size)
{
  for(int i =0; i < size ; i++)
  {
    print_tab(l[i].List,l[i].height ,l[i].width);
    printf("\n");
  }
}


int main(int argc, char *path[])
{
  if (argc!=2)
    {
      return 1;
    }
  SDL_Surface *surface = IMG_Load(path[1]);
  int* line = cutline(surface);
  //findfirstletters(surface,begin);
  //findendletters(surface,begin,0);
  int *colum = cutcolum(surface,line);
  addcoord (surface,line,colum);
  SDL_Surface *newsurface = IMG_Load(path[1]);
  matrix* matrice = print_matrix(newsurface,line,colum);
  free(colum);
  free(line);
  //pprint(matrice,3);
  display_image(surface);
  SDL_FreeSurface(surface);
  free(matrice);
  return 0;

}
