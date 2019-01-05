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
  int r;
  for(int i = 0; i < 100; i++)
  {
    r = random_index(nbexemple-1);
    s += neural_network_training(net, enter[r] ,L);
  }
  return s ;
}


int main(int argc, char *path[])
{
  if (argc==2)
    {
      int size = 3;
      int L[] = {750 ,300 , 52};
      network* net = make_network(size, L);
      net-> lw = alltomatrice(2, "poid.txt");
      net-> biais = alltomatriceb("biais.txt");
      //print_matrix(net->lw[0].List,net->lw[0].height,net->lw[0].width);
      /*int nbimage = 0;
      matrix * texte = give_matrix(path[1],&nbimage);
      for(int i =0; i<nbimage;i++)
	    {  
  	   if (verifline(texte[i]))
		    {
	           printf("\n");
		    continue;
        }
           print_matrixx(texte[i].List, texte[i].height, texte[i].width);
           double* a = matToList(texte[i]);
           putEnter(net->layer, a);
           forward(net->size,net->lw, net->layer, net->biais,
            net->lz);
           print_matrix(net->layer[size-1].List, net->layer[size-1].height ,
            net->layer[size-1].width);
	        int index = findindex (net,L);
	        char lettre = inttochar(index);
	        printf("%c",lettre);
        }*//*
          int nb = 0;
        tuple* list_tuple = initLearningByPath2(path[1], &nb);
        for(int i = 0; i < nb; i++)
        {
          matrix l = resize_matrix(list_tuple[i].mat, 30 ,25);
          l = removewhite(l);
          l = resize_matrix(l, 30 ,25);
          list_tuple[i].mat = l;
          print_matrixx(list_tuple[i].mat.List, list_tuple[i].mat.height,
           list_tuple[i].mat.width);
          printf("\n");
        }

        for(int i = 0; i< nb; i++)
        {
          tuple le = list_tuple[i];
          putEnter(net->layer, le.list);
          print_matrixx(le.mat.List, le.mat.height, le.mat.width);
          forward(net->size,net->lw, net->layer, net->biais, net->lz);
	        int index = findindex (net,L);
          char lettre = inttochar(index);
          printf("%c", lettre);
        }*/



      tuple le = initLearningByPath(path[1],"");
      putEnter(net->layer, le.list);
      print_matrixx(le.mat.List, le.mat.height, le.mat.width);
      forward(net->size,net->lw, net->layer, net->biais, net->lz);
	    int index = findindex (net,L);
	    char lettre = inttochar(index);
	    printf("ocr : %c\n",lettre);
      printf("\n");
      return 1;
    }
  else
  {
    int taille;
    char** listchar = listOfLearning("learn/",&taille);

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
    while(s < 100)
    {
      s= training(net,list_tuple, L,taille);
      printf("reussite : %d \n",s);
    }

    for(int j=0; j< 20; j++)
    {
      putEnter(net->layer, list_tuple[j].list);
      print_matrixx(list_tuple[j].mat.List, list_tuple[j].mat.height,
       list_tuple[j].mat.width);
      printf("rep : %c -> ",list_tuple[j].inputsChar);
      forward(net->size,net->lw, net->layer, net->biais, net->lz);
	    int index = findindex (net,L);
	    char lettre = inttochar(index);
	    printf("ocr : %c\n",lettre);
    }

    savealltofile(net->lw,2,"poid.txt");
    savealltofile(net->biais,3,"biais.txt");
  }
  return 0;
}
