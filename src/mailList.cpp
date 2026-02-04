#include <gtk-2.0/gtk/gtk.h>
#include "app.hpp"
#include <iostream>
#include <thread>
#include <list>
#include "icons/refresh_icon.h"
#include "icons/arrowBack_icon.h"

int mailList(int argc, char *argv[], GtkWidget *vbox) {
  
  // Title
  GtkWidget *titleMi = gtk_menu_item_new();
  GtkWidget *titleLabel = gtk_label_new(NULL);
  gtk_label_set(GTK_LABEL(titleLabel), "Mail");

  gtk_container_add(GTK_CONTAINER(titleMi), titleLabel);
  gtk_widget_set_sensitive(titleMi, FALSE);
  gtk_widget_set_can_focus(titleMi, FALSE);

  gtk_misc_set_alignment(GTK_MISC(titleLabel), 0.5, 0); // center
  gtk_container_add(GTK_CONTAINER(vbox), titleMi);


  // Refresh Button
  GtkWidget *refreshMi = gtk_menu_item_new();
  GtkWidget *refreshHbox = gtk_hbox_new(FALSE, 6);

  GtkWidget *refreshLabel = gtk_label_new("Refresh");
  gtk_box_pack_start(GTK_BOX(refreshHbox), refreshLabel, FALSE, FALSE, 0);

  GdkPixbuf *refreshPixbuf = gdk_pixbuf_new_from_inline(refresh_png_len, refresh_png, FALSE, NULL);
  GtkWidget *refreshIcon = gtk_image_new_from_pixbuf(refreshPixbuf);
  g_object_unref(refreshPixbuf);
  gtk_box_pack_start(GTK_BOX(refreshHbox), refreshIcon, FALSE, FALSE, 0);

//  gtk_misc_set_alignment(GTK_CONTAINER(refreshHbox), 1, 0); // right
  gtk_container_add(GTK_CONTAINER(vbox), refreshHbox);

  // Exit Button
  GtkWidget *exitMi = gtk_menu_item_new();
  g_signal_connect(G_OBJECT(exitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);

  GtkWidget *align = gtk_alignment_new(0, 0.5, 0, 0); // left

  GdkPixbuf *exitPixbuf = gdk_pixbuf_new_from_inline(arrowBack_png_len, arrowBack_png, FALSE, NULL);
  GtkWidget *exitIcon = gtk_image_new_from_pixbuf(exitPixbuf);
  g_object_unref(exitPixbuf);

  gtk_container_add(GTK_CONTAINER(vbox), exitIcon);
  gtk_container_add(GTK_CONTAINER(vbox), align);
  return 0;

  GtkWidget *mailListScrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(mailListScrollbar), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start(GTK_BOX(vbox), mailListScrollbar, TRUE, TRUE, 5);

  GtkWidget *centerAlign = gtk_alignment_new(0.5, 0, 0.5, 0);
  GtkWidget *listBox = gtk_vbox_new(FALSE, 10);

  gtk_container_add(GTK_CONTAINER(centerAlign), listBox);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(mailListScrollbar), centerAlign);
}