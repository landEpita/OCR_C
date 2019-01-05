# include <stdio.h>
# include <stdlib.h>
# include <gtk/gtk.h>
# include <string.h>

#include "gui.h"
char *g_path;

void call_black_and_white_fonction()
{
  char begin[100] = "./all ";
  int len=strlen(g_path);
  int i;
  for(i=len-1;i>=0 && g_path[i]!='/'; i--);
  if(i>=0)
    {
      g_path+=i+1;
    }
    strcat(begin,g_path);
    char end[] = " p";
    strcat(begin,end);
    
    system(begin);
    
}
void NeuralNet()
{
    system("./all test.bmp p e e");
}
void Seg()
{
   // call_black_and_white_fonction();
    system("./all test.bmp p e");
}

char *Opening(GtkWidget *window)
{
  GtkWidget *dialog;
  GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
  gint res;
  char *filename;

  dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(window), action,
					"Cancel", GTK_RESPONSE_CANCEL,
					"Open", GTK_RESPONSE_ACCEPT, NULL);

  res = gtk_dialog_run (GTK_DIALOG (dialog));
  if (res == GTK_RESPONSE_ACCEPT)
    {
      GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
      filename = gtk_file_chooser_get_filename (chooser);
    }

  gtk_widget_destroy (dialog);
  return filename;
}

 
GtkWidget *Header()//GtkWidget *window)
{
  GtkWidget *res = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);
  
  GtkWidget *start = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(start), "Start");
  g_signal_connect(G_OBJECT(start), "clicked", G_CALLBACK(NeuralNet), NULL);
  GtkWidget *bandw = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(bandw), "B & W");
  g_signal_connect(G_OBJECT(bandw), "clicked",
		   G_CALLBACK(call_black_and_white_fonction), NULL);
  GtkWidget *cut = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(cut), "Cut");
  g_signal_connect(G_OBJECT(cut), "clicked", G_CALLBACK(Seg), NULL);
 
  
  
  gtk_container_add(GTK_CONTAINER(res), bandw);
  gtk_container_add(GTK_CONTAINER(res), cut);
  gtk_container_add(GTK_CONTAINER(res), start);

  return res;
  
}

void All(int argc, char *argv[])
{
  gtk_init(&argc, &argv);
  
  GtkWidget *widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(widget), 600, 400);
  g_signal_connect(GTK_WINDOW(widget), "destroy", G_CALLBACK(gtk_main_quit),
		   NULL);

  GtkWidget *myBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,20);

  GtkWidget *header = Header(widget);
  gtk_box_set_homogeneous (GTK_BOX(header), TRUE);
  GtkWidget *image; 
  GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,10);

  char *path = Opening(widget);
  g_path = path;

  image = gtk_image_new_from_file(path);
  gtk_window_set_title(GTK_WINDOW(widget),path);
      



  
  gtk_container_add(GTK_CONTAINER(myBox), header);
  gtk_container_add(GTK_CONTAINER(myBox), image);
  gtk_container_add(GTK_CONTAINER(myBox), footer);

  gtk_box_set_center_widget(GTK_BOX(myBox), header);

  gtk_container_add(GTK_CONTAINER(widget), myBox);
  
  gtk_widget_show_all(widget);
  gtk_main();

}

int main(int argc, char *argv[])
{
  All(argc, argv);
  
  return EXIT_SUCCESS;
}

