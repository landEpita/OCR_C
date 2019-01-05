// pixel_operations.h
 
# ifndef PIXEL_OPERATIONS_H_
# define PIXEL_OPERATIONS_H_
 
# include <stdlib.h>
# include <SDL.h>
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
void blackandwhite(SDL_Surface *ecran);
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void init_sdl(void);
void wait_for_keypressed(void);
void Grey(SDL_Surface *surface);
# endif
