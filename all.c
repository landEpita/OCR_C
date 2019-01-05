#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
# include <err.h>
//#include"all.h"


int segmentation(char *path[])
{
    int ret;
    char path_fi[] = "Segmentation/main ";
    strcat(path_fi,path[1]);
    ret=system(path_fi);
    return ret;
}
int preprocessing(char *path[])
{
    int ret;
    char path_fi[] = "Preprocessing/main ";
    strcat(path_fi,path[1]);
    ret=system(path_fi);
    return ret;
}

int neural_network(char *path[])
{
    int ret;
    char path_fi[] = "neural?network/main ";
    strcat(path_fi,path[1]);
    ret=system(path_fi);
    return ret;
}

int main(int argc, char *path[])
{
   
    if(argc == 3)
    {
        if(preprocessing(path)!=0)
        {
            printf("Error in preprocessing occured");
        }
    }
    if(argc == 4)
    {
        if(segmentation(path)!=0)
        {
            printf("Error in segmentation occured");
        }
    }
    if(argc == 5)
    {
        if(neural_network(path)!=0)
        {
            printf("Error in neuronal_network occured");
        }
    }
    
    
   // 
    
}

