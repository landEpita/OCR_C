#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
#include "neuronal.h"
#include <SDL.h>
#include "pixel_operations.h"
#include <SDL/SDL_image.h>
#include <sys/types.h>
#include <dirent.h>

void wait_for_keypressed(void) {
    SDL_Event             event;
    // Infinite loop, waiting for event
    for (;;) {
      // Take an event
      SDL_PollEvent( &event );
      // Switch on event type
      switch (event.type) {
      // Someone pressed a key -> leave the function
      case SDL_KEYDOWN: return;
      default: break;
      }
    // Loop until we got the expected event
    }
  }
void init_sdl(void) {
    // Init only the video part
    if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
        // If it fails, die with an error message
        errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
    }
    // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
    SDL_Surface          *img;
    // Load an image using SDL_image with format detection
    img = IMG_Load(path);
    if (!img)
      // If it fails, die with an error message
      errx(3, "can't load %s: %s", path, IMG_GetError());
    return img;
  }

SDL_Surface* display_image(SDL_Surface *img) {
    SDL_Surface          *screen;
    // Set the window to the same size as the image
    screen = SDL_SetVideoMode(img->w, img->h, 0,
     SDL_SWSURFACE|SDL_ANYFORMAT);
    if ( screen == NULL ) {
        // error management
        errx(1, "Couldn't set %dx%d video mode: %s\n",
            img->w, img->h, SDL_GetError());
    }

    // Blit onto the screen surface
    if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
        warnx("BlitSurface error: %s\n", SDL_GetError());

    // Update the screen
    SDL_UpdateRect(screen, 0, 0, img->w, img->h);

    // wait for a key
    wait_for_keypressed();

    // return the screen for further uses
    return screen;
}

// 19x30

char** listOfLearning(char* dirName, int *sizeOfList){
    DIR *dp;
    struct dirent *ep;
    int mySize = 0;
    dp = opendir(dirName);
    if (dp != NULL)
      {
        while(readdir (dp)){
            mySize++;
        }
        (void) closedir (dp);
      }
    else{
        perror ("Couldn't open the directory");
        exit(0);
    }
    dp = opendir(dirName);

    //mySize = 100;
    int testSize = mySize;

    char** listOfName = NULL;
    if((listOfName = malloc(sizeof(char*) * mySize)) == NULL){
        exit(0);
    }
    *sizeOfList = mySize;
    mySize = 0;
    while((ep = readdir (dp)) !=  NULL && mySize != testSize){
        if(strcmp(ep->d_name, ".") && strcmp(ep->d_name, "..")){
            listOfName[mySize] = NULL;
            if((listOfName[mySize] = malloc(sizeof(ep->d_name))) == NULL){
                exit(0);
            }
            for(unsigned int j = 0; j < sizeof(ep->d_name)/sizeof(char); j++){
                listOfName[mySize][j] = (ep->d_name)[j];
            }
            mySize++;
        }
        else{
            *sizeOfList = *sizeOfList - 1;
        }
    }
    (void) closedir (dp);
    return listOfName;
}
int doubleToInt(double myDouble){
    return (myDouble > 0.5) ? 1 : 0;
}

int byteToInt(double* bytes){
    int result = 0;
    int twoPow = 1;
    for(int i = 7; i >= 0; i--){
        result += doubleToInt(bytes[i]) * twoPow;
        twoPow *= 2;
    }
    return result;
}
int byteCellsToInt(NeuralCell* bytes){
    int result = 0;
    int twoPow = 1;
    double directValue;
    for(int i = 0; i < 8; i++){
        directValue = bytes[7 - i].value;
        if(directValue > 0.5)
            result += twoPow;
        twoPow *= 2;
    }
    return result;
}

double* intToByte(int myVal){
    double* myByte;
    if((myByte = malloc(sizeof(double) * 8)) == NULL)
        exit(0);
    int steps = 0;
    while(myVal != 0){
        if(steps >= 8){
            printf("%i is too high for a byte !", myVal);
            exit(0);
        }
        myByte[7 - steps] = myVal % 2;
        myVal /= 2;
        steps++;
    }
    
    return myByte;

}     

char* concatenateString(char* string1, char* string2){
    char* myNewString;
    size_t size1 = strlen(string1);
    size_t size2 = strlen(string2);
    if((myNewString = malloc(sizeof(char) * (size1 + size2 + 1))) == NULL){
        exit(0);
    }
    for(unsigned int i = 0; i < size1; i++){
        *(myNewString + i) = *(string1 + i);
    }
    for(unsigned int i = 0; i < size2; i++){
        *(myNewString + size1 + i) = *(string2 + i);
    }
    *(myNewString + size1 + size2) = 0;
    return myNewString;

}

Learning initLearningByPath(char* myPath, char* dir){
    Learning myLearning;
    if((myLearning.inputsBytes = malloc(sizeof(double) * 875)) == NULL)
        exit(0);
    for(int i = 0; i < 875; i++){
        *(myLearning.inputsBytes + i) = 0;
    }
    myLearning.inputsChar = myPath[0];
    SDL_Surface* myImg = load_image(concatenateString(dir, myPath));
    unsigned int height = myImg->h;
    unsigned int width = myImg->w;
    Uint32 myPixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    if(width > 25 || height > 35){
        printf("Too tall !! : (%i, %i) but expected less than (25, 35). \nFileName : %s \n", width, height, myPath);
        free(myImg);
        exit(0);
    }
    for(unsigned i = 0; i < height; i++){
        for(unsigned j = 0; j < width; j++){
            myPixel = getpixel(myImg, j, i);
            SDL_GetRGB(myPixel, myImg->format, &r, &g, &b);
            if(r + g + b < 500){
                myLearning.inputsBytes[j + (i * 25)] = 1;
            }
        }
    }
    myLearning.outputs = intToByte((int)myLearning.inputsChar);
    free(myImg);
    return myLearning;
}
