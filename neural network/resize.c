#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

#include "function.h"
#include "tools_network.h"
#include "correction.h"
#include "tools_letter.h"
#include "segmentation.h"

#include "resize.h"

#define KRED "\x1B[31m"
#define KNRM "\x1B[0m"

void print_matrixx(double **mat, int lines, int cols)
{
  for(int i = 0; i < lines; i++) {
    printf("\n");
    for(int j = 0; j < cols; j++) {
      if(mat[i][j] != 0)
        printf("%s %4g",KRED, mat[i][j]);
      else
        printf("%s %4g",KNRM, mat[i][j]);
    }
  }
  printf("\n");

}

gboolean get_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y,
 guchar *red, guchar *green, guchar *blue)
{
  guchar *pixel=NULL;
  gint channel=0;
  gint rowstride=0;
  
  if (!pixbuf) return FALSE;
  if (x<0 || y<0) return FALSE;
  if (x>gdk_pixbuf_get_width(pixbuf)) return FALSE;
  if (y>gdk_pixbuf_get_height(pixbuf)) return FALSE;
  
  pixel=gdk_pixbuf_get_pixels(pixbuf);
  channel=gdk_pixbuf_get_n_channels(pixbuf);
  rowstride=gdk_pixbuf_get_rowstride(pixbuf);
  
  *red   = pixel[(x*channel)+(y*rowstride)];
  *green = pixel[(x*channel)+(y*rowstride)+1];
  *blue  = pixel[(x*channel)+(y*rowstride)+2];
  
  return TRUE;
}

gboolean set_colors_by_coordinates(GdkPixbuf *pixbuf, gint x, gint y, 
guchar red, guchar green, guchar blue)
{
  guchar *pixel=NULL;
  gint channel=0;
  gint rowstride=0;
  
  if (!pixbuf) return FALSE;
  if (x<0 || y<0) return FALSE;
  if (x>gdk_pixbuf_get_width(pixbuf)) return FALSE;
  if (y>gdk_pixbuf_get_height(pixbuf)) return FALSE;
  
  pixel=gdk_pixbuf_get_pixels(pixbuf);
  channel=gdk_pixbuf_get_n_channels(pixbuf);
  rowstride=gdk_pixbuf_get_rowstride(pixbuf);
  
  pixel[(x*channel)+(y*rowstride)] = red;
  pixel[(x*channel)+(y*rowstride)+1] = green;
  pixel[(x*channel)+(y*rowstride)+2] = blue;
  
  return TRUE;
}

matrix resize_matrix(matrix mat, int dstH, int dstW)
{
  
  GdkPixbuf *pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 1, 8,
   mat.width, mat.height);
  
  for(int i = 0; i < mat.height; i++)
    {
      for(int j = 0; j < mat.width; j++)
	{
	  if(mat.List[i][j] == 0)
	    set_colors_by_coordinates(pixbuf, j, i, 0, 0, 0);
	  else
	    set_colors_by_coordinates(pixbuf, j, i, 255, 255, 255);	 
	}
    }
  
  GdkPixbuf *r_pixbuf = gdk_pixbuf_scale_simple(pixbuf, dstW, dstH, 
  GDK_INTERP_NEAREST);
  
  matrix r_mat;
  r_mat.height = dstH;
  r_mat.width = dstW;
  r_mat.List = malloc(sizeof(double)*r_mat.height);
  for(int i = 0; i < r_mat.height; i++)
    r_mat.List[i] = malloc(sizeof(double)*r_mat.width);    
  
  guchar *r = malloc(sizeof(guchar)),
    *g = malloc(sizeof(guchar)),
    *b = malloc(sizeof(guchar));
  
  for(int i = 0; i < r_mat.height; i++)
    for(int j = 0; j < r_mat.width; j++)
      {
	get_colors_by_coordinates(r_pixbuf, j, i, r, g, b);
	guchar t = 0.21**r+0.72**g+0.07**b;
	if(t != 0)
	  r_mat.List[i][j] = 1;
	else
	  r_mat.List[i][j] = 0;
      }
  
  g_object_unref(r_pixbuf);
  //g_object_unref(pixbuf);
  
  for(int i = 0; i < mat.height; i++)
    free(mat.List[i]);
  free(mat.List);
  
  free(r);
  free(g);
  free(b);

  return r_mat;
}
