#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

# include <SDL/SDL_image.h>
# include <SDL/SDL.h>
#include "segmentation.h"
#include <gtk/gtk.h>
 
#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"

#include "resize.h"



int training(network* net,tuple* enter,int L[], int nbexemple)
{
  double s= 0;
  double val_abs;
  int r;
  for(int i = 0; i < nbexemple; i++)
  {
    r = random_index(nbexemple-1);
    val_abs = neural_network_training(net, enter[r] ,L);
    if(val_abs< 0.005 )
    {
        s+=1;
    } 
  }
  return s/((double)(nbexemple))*100 ;
}


int main(int argc, char *path[])
{
  if (argc==2)
    {
      int size = 3;
      int L[] = {750 ,300 , 52};
      network* net = make_network(size, L);
     // net-> lw = alltomatrice(2, "poid.txt");
      //net-> biais = alltomatriceb("biais.txt");
      //print_matrix(net->lw[1].List,net->lw[1].height,net->lw[1].width);
      int nbimage = 0;
      matrix * texte = give_matrix(path[1],&nbimage);
      for(int i =0; i<nbimage;i++)
	  { 
	   if (verifline(texte[i])==1)
		    {
	              printf(" ");
		      continue;
                    } 
           texte[i] = removewhite(texte[i]);
           texte[i] = resize_matrix(texte[i], 30 ,25);
           //print_matrixx(texte[i].List, texte[i].height, texte[i].width);
           double* a = matToList(texte[i]);
           putEnter(net->layer, a);
           forward(net->size,net->lw, net->layer, net->biais, net->lz);
	   int index = findindex (net,L);
	   char lettre = inttochar(index);
	   printf("%c",lettre);
	 }
      printf("\n");
      return 1;
    }
  else
  {
    int taille;
    char** listchar = listOfLearning("newlearn/",&taille);

    tuple* list_tuple =  make_list_tuple(listchar,taille);
    for(int i = 0; i < taille; i++)
    {
      printf("%c\n",list_tuple[i].inputsChar);
      matrix l = resize_matrix(list_tuple[i].mat, 30 ,25);
      l = removewhite(l);
      l = resize_matrix(l, 30 ,25);
      list_tuple[i].mat = l;
      print_matrixx(list_tuple[i].mat.List, list_tuple[i].mat.height, 
      list_tuple[i].mat.width);
      printf("\n");
    }
  
    srand(time(NULL));
    int size = 3;

    int L[] = {750 ,300 , 52};
    network* net = make_network(size, L);

  
  //############################################### 
    int s= 0;
    //int nb = 1;
    while(s < 10)
    {
      s= training(net,list_tuple, L,taille);
      printf("reussite : %d \n",s);
      /*if(nb%5 == 0)
	    {
	      savealltofile(net->lw,2,"poid.txt");
	    }
      nb++;*/
    }
    //print_matrix(net->lw[1].List,net->lw[1].height,net->lw[1].width);
    savealltofile(net->lw,2,"poid.txt");
    savealltofile(net->biais,3,"biais.txt");
  }
  return 0;
}
