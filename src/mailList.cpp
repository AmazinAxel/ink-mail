#include <gtk-2.0/gtk/gtk.h>
#include <iostream>
#include <thread>
#include <list>

struct emailData {
  std::string title;
  std::string message;
  std::string date;
};

int mailList(int argc, char *argv[]) {
  // Title
  GtkWidget *titleMi = gtk_menu_item_new();
  GtkWidget *titleLabel = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(titleLabel), "Mail");

  gtk_container_add(GTK_CONTAINER(titleMi), titleLabel);
  gtk_widget_set_sensitive(titleMi, FALSE);
  gtk_widget_set_can_focus(titleMi, FALSE);

  gtk_misc_set_alignment(GTK_MISC(titleLabel), 0.5, 0.5);

  // Refresh Button
  GtkWidget *refreshMi = gtk_menu_item_new();
  GtkWidget *refreshHbox = gtk_hbox_new(FALSE, 6);

  GtkWidget *refreshLabel = gtk_label_new("Refresh");
  gtk_box_pack_start(GTK_BOX(refreshHbox), refreshLabel, FALSE, FALSE, 0);

  //GdkPixbuf *shopPixbuf = gdk_pixbuf_new_from_inline(shop_png_len, shop_png, FALSE, NULL);
  //GdkPixbuf *shopScaled = gdk_pixbuf_scale_simple(shopPixbuf, 16, 16, GDK_INTERP_BILINEAR);
  //GtkWidget *shopIcon = gtk_image_new_from_pixbuf(shopScaled);
  //g_object_unref(shopPixbuf);
  //gtk_box_pack_start(GTK_BOX(shopHbox), shopIcon, FALSE, FALSE, 0);

  gtk_container_add(GTK_CONTAINER(shopMi), refreshHbox);
  
  // Quit Button
  GtkWidget *quitMi = gtk_menu_item_new();

  GtkWidget *align = gtk_alignment_new(1.0, 0.5, 0, 0); // xalign=1.0 → right aligned

  //GdkPixbuf *quitPixbuf = gdk_pixbuf_new_from_inline(quit_png_len, quit_png, FALSE, NULL);
  //GdkPixbuf *quitScaled = gdk_pixbuf_scale_simple(quitPixbuf, 16, 16, GDK_INTERP_BILINEAR);
  //GtkWidget *quitIcon = gtk_image_new_from_pixbuf(quitScaled);
  //g_object_unref(quitPixbuf);

 // gtk_container_add(GTK_CONTAINER(align), quitIcon);
 // gtk_container_add(GTK_CONTAINER(quitMi), align);  

  /*GtkWidget *currentBooksScrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(currentBooksScrollbar), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start(GTK_BOX(vbox), currentBooksScrollbar, TRUE, TRUE, 5);

  GtkWidget *centerAlign = gtk_alignment_new(0.5, 0, 0.5, 0);
  GtkWidget *listBox = gtk_vbox_new(FALSE, 10);

  gtk_container_add(GTK_CONTAINER(centerAlign), listBox);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(currentBooksScrollbar), centerAlign);

  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);
*/
  gtk_widget_show_all(window);
}