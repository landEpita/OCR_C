#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include <sys/types.h>
#include <dirent.h>

#include <gtk/gtk.h>

#include <SDL.h>
#include <SDL/SDL_image.h>

#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"
#include "segmentation.h"
#include "resize.h"

int neuroneactif(char letter)
{
    int n = (int)(letter);
    if (n>64 && n < 91)
    {
        return n-65;
    }
    if(n > 96 && n < 123)
    {
        return n-97+26;
    }
    return -1;
}
char inttochar(int n)
{ 
    if (n<26)
    {
        n+=65;
    }
    else 
    {
        n+=97-26;
    }
    return (char)(n);
}

int* charTobin(char letter)
{
    int* L = NULL;
    L = malloc(8 * sizeof(int));
    if(L == NULL){
        exit(0);
    }  
    int n;
    int intletter = (int)letter;
    for(int i = 7; i >= 0; i--)
    {
        n = pow(2,i);
        if(intletter-n >= 0)
        {
            L[i] = 1;
            intletter-=n;
        }
        else{
            L[i] = 0;
        }
    }
    return L;
}

char binTochar(int* L)
{
    int n=0;
    for(int i = 0; i< 8; i++)
    {
        n+= L[i] * pow(2,i);
    }
    return (char)n;
}

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
            for(unsigned int j = 0;j<sizeof(ep->d_name)/sizeof(char); j++){
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

tuple initLearningByPath(char* myPath, char* dir){
    tuple learning;
    learning.inputsChar = myPath[0];
    //learning.mat =  give_matrix_im(concatenateString(dir, myPath));
    learning.mat =  resize_matrix(give_matrix_im(concatenateString(dir, 
    myPath)), 30,25);
    learning.list = matToList( learning.mat);
    return learning;
}

tuple* initLearningByPath2(char* myPath, int* nb){
    matrix * m = give_matrix(myPath ,nb );
    tuple* l = malloc(sizeof(tuple) * *(nb));
    for(int i = 0; i < *(nb); i++)
    {
        l[i].mat= resize_matrix(m[i], 30, 25);

        l[i].list = matToList(l[i].mat);
    }
    return l;
}

tuple* make_list_tuple(char** listChar, int size)
{
    tuple* res = NULL;
    res = malloc(sizeof(tuple)* size);
    if(res == NULL){
        exit(0);
    }
    for(int i =0; i<size; i++)
    {
        res[i] = initLearningByPath(listChar[i],"learn/");
    }
    return res;
}

double* matToList(matrix mat)
{
    double* res = NULL;
    res = malloc(sizeof(double*)*(mat.height)*(mat.width));
    if(res == NULL){
        exit(0);
    }
    int v = 0;
    for(int i = 0; i< mat.height; i++)
    {
        for(int j = 0; j< mat.width; j++)
        {
            res[v] = mat.List[i][j];
            v++;
        }
    }
    return res;
}
