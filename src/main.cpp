#include <gtk-2.0/gtk/gtk.h>
#include <iostream>
#include <thread>
#include <list>

struct emailData {
  std::string title;
  std::string message;
  std::string date;
};

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "Ink Mail");
  gtk_window_set_default_size(GTK_WINDOW(window), 600, 800);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);
  gtk_window_set_icon_from_file(GTK_WINDOW(window), "./icons/mail.png", NULL);

  // todo fix icons
  GtkWidget *vbox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  gtk_window_set_icon_from_file(GTK_WINDOW(window), "./icons/mail.png", NULL);

  GtkWidget *icon = gtk_image_new_from_file("./icons/mail.png");
  gtk_box_pack_start(GTK_BOX(vbox), icon, FALSE, FALSE, 0);

  gtk_widget_show_all(window);
  gtk_main();
  return 0;
}
