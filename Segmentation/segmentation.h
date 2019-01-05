// pixel_operations.h

# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_

# include <stdlib.h>
# include <SDL.h>

typedef double (*func_t)(double);
typedef struct matrix matrix;
struct matrix
{
  int width;
  int height;
  double** List;
};


Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void drawLines(SDL_Surface *surface, int x, int y, int* begin);
void drawBorders(SDL_Surface *surface, int* x, int y);
int findendline(SDL_Surface *surface,int posy);
int findfirstline(SDL_Surface *surface,int posy);
int* cutline(SDL_Surface *surface);
SDL_Surface* display_image(SDL_Surface *img);
int findfirstletters(SDL_Surface *surface,int* begin,int posx);
int findendletters(SDL_Surface *surface,int* begin,int posx);
int* cutcolum(SDL_Surface *surface,int* begin);
void wait_for_keypressed(void);
void addcoord (SDL_Surface *surface,int* line, int*colum);
matrix* print_matrix (SDL_Surface *surface,int* line, int*colum);

# endif
