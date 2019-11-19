/* X/O game version 1.0 */

#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

GtkWidget *button[9];
GtkWidget *button_Q;
GtkWidget *grid;
GtkWidget *window; // Window 


static int filled[9],j = 0,ply[9],com[9];

// Function to open a dialog box with a message
void quick_message (GtkWindow *parent, gchar *message)
{
 GtkWidget *dialog, *label, *content_area;
 GtkDialogFlags flags;

 // Create the widgets
 flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 dialog = gtk_dialog_new_with_buttons ("Result",
                                       parent,
                                       flags,
                                       ("_OK"),
                                       GTK_RESPONSE_NONE,
                                       NULL);
 content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 label = gtk_label_new (message);

 // Ensure that the dialog box is destroyed when the user responds

 g_signal_connect_swapped (dialog,
                           "response",
                           G_CALLBACK (gtk_widget_destroy),
                           dialog);

 // Add the label, and show everything we’ve added

 gtk_container_add (GTK_CONTAINER (content_area), label);
 gtk_widget_show_all (dialog);
}

static void logic (GtkWidget *widget,
             gpointer   data)
{
  
  int i = 0,val,cond = 1;
// Player's Chance to set X 
  gtk_button_set_label(GTK_BUTTON(widget),"  X  ");
  gtk_widget_set_sensitive(widget, FALSE);

  for(i=0;i<9;i++){
		  if(button[i] == widget){
				  filled[j] = i;
				  j++;
				  ply[i] = i;
  		  		  break;
		  }
  }
  

  if( ((ply[0]<10)&&(ply[1]<10)&&(ply[2]<10)) ||
      ((ply[3]<10)&&(ply[4]<10)&&(ply[5]<10)) ||
  	  ((ply[6]<10)&&(ply[7]<10)&&(ply[8]<10)) ||
  	  ((ply[0]<10)&&(ply[3]<10)&&(ply[6]<10)) ||
      ((ply[1]<10)&&(ply[4]<10)&&(ply[7]<10)) ||
 	  ((ply[2]<10)&&(ply[5]<10)&&(ply[8]<10)) ||
  	  ((ply[0]<10)&&(ply[4]<10)&&(ply[8]<10)) ||
  	  ((ply[2]<10)&&(ply[4]<10)&&(ply[6]<10)) ){

		  //pop up player won 		  
		  quick_message ((GtkWindow *)window, "Won");
		  
		  //reset all button
		  for(i = 0;i < 9;i++){
  		  gtk_widget_set_sensitive(button[i], TRUE);
  		  gtk_button_set_label(GTK_BUTTON(button[i]),"  Z  ");
		  filled[i] = 10;
		  ply[i] = 10;
		  com[i] = 10;
		  j=0;
		  }

		  // return from function
		  return;
  }

  // Draw
  if(j >= 8){

		  //pop up Draw 		  
		  quick_message ((GtkWindow *)window, "Draw");
		  
		  //reset all button
		  for(i = 0;i < 9;i++){
  		  gtk_widget_set_sensitive(button[i], TRUE);
  		  gtk_button_set_label(GTK_BUTTON(button[i]),"  Z  ");
		  filled[i] = 10;
		  ply[i] = 10;
		  com[i] = 10;
		  j=0;
		  }

		  return;
  }

  //computer chance to play	 
  if(j <= 7){

  srand(time(0)); // use current time as seed for random generator
 
  do{
		cond = 1;
		val = rand()%10;
		if(val < 9)
		{
		  for(i=0;i<9;i++){
				  if(val == filled[i]){
						  cond = 0;
						  break;
				  }
		  }
		}
  }while(cond == 0 || button[val] == widget || val == 9);

  filled[j] = val;
  com[val] = val;
  j++;
  
  gtk_button_set_label(GTK_BUTTON(button[val]),"  O  ");
  gtk_widget_set_sensitive(button[val], FALSE);


  if(   ((com[0]<10)&&(com[1]<10)&&(com[2]<10)) ||
        ((com[3]<10)&&(com[4]<10)&&(com[5]<10)) ||
        ((com[6]<10)&&(com[7]<10)&&(com[8]<10)) ||
        ((com[0]<10)&&(com[3]<10)&&(com[6]<10)) ||
        ((com[1]<10)&&(com[4]<10)&&(com[7]<10)) ||
        ((com[2]<10)&&(com[5]<10)&&(com[8]<10)) ||
        ((com[0]<10)&&(com[4]<10)&&(com[8]<10)) ||
        ((com[2]<10)&&(com[4]<10)&&(com[6]<10)) ){
  
            //pop up player lost         
            quick_message ((GtkWindow *)window, "lost");
  
            //reset all button
            for(i = 0;i < 9;i++){
            gtk_widget_set_sensitive(button[i], TRUE);
            gtk_button_set_label(GTK_BUTTON(button[i]),"  Z  ");
            filled[i] = 10;
            com[i] = 10;
			ply[i] = 10;
            j=0;
            }
  
            // return from function
            return;
    }
  
  }
  
}

static void activate (GtkApplication *app,
          gpointer        user_data)
{

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "X/O  ");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* Here we construct the container that is going pack our buttons */
  grid = gtk_grid_new ();

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), grid);

  button[0] = gtk_button_new_with_label ("  Z  "); 
  g_signal_connect (button[0], "clicked", G_CALLBACK (logic), (void*)0);

  /* Place the first button in the grid cell (0, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button[0], 0, 0, 1, 1);

  button[1] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[1], "clicked", G_CALLBACK (logic), (void*)1);

  /* Place the second button in the grid cell (1, 0), and make it fill
   * just 1 cell horizontally and vertically (ie no spanning)
   */
  gtk_grid_attach (GTK_GRID (grid), button[1], 1, 0, 1, 1);


  button[2] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[2], "clicked", G_CALLBACK (logic), (void*)2);
 
    /* Place the second button in the grid cell (2, 0), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
  gtk_grid_attach (GTK_GRID (grid), button[2], 2, 0, 1, 1);

  button[3] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[3], "clicked", G_CALLBACK (logic), (void*)3);
 
    /* Place the second button in the grid cell (0, 1), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
  gtk_grid_attach (GTK_GRID (grid), button[3], 0, 1, 1, 1);
  
  button[4] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[4], "clicked", G_CALLBACK (logic), (void*)4);
 
    /* Place the second button in the grid cell (1, 1), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
  gtk_grid_attach (GTK_GRID (grid), button[4], 1, 1, 1, 1);
  

  button[5] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[5], "clicked", G_CALLBACK (logic), (void*)5);
 
    /* Place the second button in the grid cell (2, 1), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
  gtk_grid_attach (GTK_GRID (grid), button[5], 2, 1, 1, 1);

  button[6] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[6], "clicked", G_CALLBACK (logic), (void*)6);
 
    /* Place the second button in the grid cell (0, 2), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
  gtk_grid_attach (GTK_GRID (grid), button[6], 0, 2, 1, 1);
  
  button[7] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[7], "clicked", G_CALLBACK (logic), (void*)7);
 
    /* Place the second button in the grid cell (1, 2), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
  gtk_grid_attach (GTK_GRID (grid), button[7], 1, 2, 1, 1);

  button[8] = gtk_button_new_with_label ("  Z  ");
  g_signal_connect (button[8], "clicked", G_CALLBACK (logic), (void*)8);
 
    /* Place the second button in the grid cell (2, 2), and make it fill
     * just 1 cell horizontally and vertically (ie no spanning)
     */
  gtk_grid_attach (GTK_GRID (grid), button[8], 2, 2, 1, 1);
  
  button_Q = gtk_button_new_with_label ("Quit");
  g_signal_connect_swapped (button_Q, "clicked", G_CALLBACK (gtk_widget_destroy), window);

  /* Place the Quit button in the grid cell (0, 3), and make it
   * span 3 columns.
   */
  gtk_grid_attach (GTK_GRID (grid), button_Q, 0, 3, 3, 1);

  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
  gtk_widget_show_all (window);

}

int main (int    argc,char **argv)
{
  GtkApplication *app;
  int status;
  
  int i;
  // initialization
  for(i=0;i<9;i++){
		  filled[i] = 10;
		  ply[i] = 10;
		  com[i] = 10;
  }

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}


