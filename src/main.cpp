#include <gtk-2.0/gtk/gtk.h>
#include "app.hpp"
#include "icons/refresh_icon.h"
#include "icons/arrowBack_icon.h"

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  GtkWindow *windowObj = GTK_WINDOW(window);
  gtk_window_set_title(windowObj, "Ink Mail");
  gtk_window_set_default_size(windowObj, 600, 800);
  gtk_container_set_border_width(GTK_CONTAINER(window), 5); // App padding

  // Viewbox
  GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  // White background
  GdkColor color;
  gdk_color_parse("#ffffff", &color);
  gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

  // Default view
  mailList(argc, argv, vbox);

  gtk_widget_show_all(window);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_main();
  return 0;
};
