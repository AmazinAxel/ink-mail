#include <gtk-2.0/gtk/gtk.h>
#include "../app.hpp"
#include <iostream>
#include <thread>
#include <list>
#include "../icons/mail_icon.h"

GtkWidget *mailItem(const char *title, const char *message, const char *sender) {
  GtkWidget *hbox = gtk_vbox_new(FALSE, 2);
  GtkWidget *box = gtk_vbox_new(FALSE, 2);  

  //gtk_box_pack_start(GTK_BOX(hbox), gtk_label_new(title), FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), gtk_label_new(title), FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), gtk_label_new(message), FALSE, FALSE, 0);

  gtk_box_pack_start(GTK_BOX(box), gtk_label_new(sender), FALSE, FALSE, 0);

  GdkPixbuf *mailIconPixbuf = gdk_pixbuf_new_from_inline(mail_png_len, mail_png, FALSE, NULL);
  GtkWidget *mailIcon = gtk_image_new_from_pixbuf(mailIconPixbuf);
  g_object_unref(mailIconPixbuf);
  gtk_box_pack_start(GTK_BOX(box), mailIcon, FALSE, FALSE, 0); 

  return box;

  // todo
  //gtk_container_add(GTK_CONTAINER(event), frame);

  //return event;
};
