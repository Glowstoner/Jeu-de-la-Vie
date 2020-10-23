#include <gtk/gtk.h>
#include <math.h>
#include <cairo.h>
 
#define WIDTH 640
#define HEIGHT 480
 
 
static gboolean
expose (GtkWidget * widget, GdkEventExpose * event, gpointer userdata)
{
  int x_zero = WIDTH/2;
  int y_zero = HEIGHT/2;
 
  cairo_surface_t * surface = NULL;
 
  cairo_t *cr = NULL;
  gint x[3] =
  {
	  -WIDTH / 2,
	  -WIDTH / 2,
	  -WIDTH / 2
  };
  gint y[3] = {0};
 
 
  cr = gdk_cairo_create (widget->window);
 
  cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);
  cairo_paint (cr);
  cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
 
  surface = cairo_get_target(cr);
 
  cairo_surface_set_device_offset(surface, WIDTH/2, HEIGHT/2);
 
  while (x[0] != WIDTH)
    {
      x[0] = x[2];
      x[1] = x[0] + 1;
      x[2] = x[1] + 2;
 
      /* On calcul y = f(x) tous les trois points */
      y[0] = pow(0.03*x[0] , 3);
      y[1] = pow(0.03*x[1] , 3);
      y[2] = pow(0.03*x[2] , 3);
 
      /* On affiche le morceau de courbe qui
       * passe par ces trois points
       */
      cairo_curve_to (cr,
		      x[0],   -y[0],
		      x[1],   -y[1], 
		      x[2],   -y[2]
		      );
    }
  cairo_stroke (cr);
 
  cairo_destroy (cr);
  return FALSE;
}
 
 
int
main (int argc, char **argv)
{
  GtkWidget *window = NULL;
 
  gtk_init (&argc, &argv);
 
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size (GTK_WINDOW (window), WIDTH, HEIGHT);
  gtk_window_set_title (GTK_WINDOW (window), "Affichage de courbe");
  g_signal_connect (G_OBJECT (window), "delete-event", gtk_main_quit, NULL);
 
 
  gtk_widget_set_app_paintable (window, TRUE);
 
  g_signal_connect (G_OBJECT (window), "expose-event", G_CALLBACK (expose),
		    NULL);
 
  gtk_widget_show_all (window);
  gtk_main ();
 
  return 0;
}