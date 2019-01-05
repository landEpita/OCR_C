#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"

double deriver_sigmoid(double x)
{
    return sigmoid(x) * (1 - sigmoid(x));
}

void corr(matrix* layer,matrix* lz, matrix* lw,matrix* error,
matrix* biais,int L[],int size)
{
    int l = lz[0].width;
    double deriv;
    double valErr;
    l++;
    for(int i =0; i< size-1; i++) // pour chaque couche 
    {
        for(int x =0; x< L[size - 2 - i]; x++) // neurone x d'une couche i
            {
                double s = 0;

                for(int h =0; h < layer[size - 2 - i].width; h++)
                {
                     s+=error[size-1-i].List[0][h]*lw[size-2-i].List[x][h];
                }
                deriv = deriver_sigmoid(lz[size-2-i].List[0][x]);
                error[size-2-i].List[0][x] = deriv*s;
                biais[size-2-i].List[0][x] -= error[size-2-i].List[0][x];
                
                
            }
        for(int y =0; y< lw[size-2 - i].height; y++)
        {
            for(int x =0; x< lw[size-2 - i].width; x++)
            {
                valErr = error[size-1-i].List[0][x];
                lw[size-2-i].List[y][x]-=layer[size-2-i].List[0][y]*valErr;
                
            }
        }
        
    }
}

void puterror(matrix* error, matrix* layer, char letter, int size)
{
    int pos = neuroneactif(letter);
    //printf("letter : %c -> %d\n",letter, pos);
    for(int i = 0; i < layer[size-1].width; i++)
    {
        if( i == pos)
            error[size-1].List[0][i] =  layer[size-1].List[0][i] - 1 ;
        else 
            error[size-1].List[0][i] =  layer[size-1].List[0][i]  ;
    }
}
