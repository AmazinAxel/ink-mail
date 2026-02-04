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

  // For some reason all labels are white
  GdkColor black;
  gdk_color_parse("#000000", &black);

  // Labels
  GtkWidget *titleLabel = gtk_label_new(NULL);
  std::string titleMarkup = "<b>" + std::string(title) + "</b>";
  gtk_label_set_markup(GTK_LABEL(titleLabel), titleMarkup.c_str());
  gtk_widget_modify_fg(titleLabel, GTK_STATE_NORMAL, &black);

  GtkWidget *messageLabel = gtk_label_new(message);
  gtk_widget_modify_fg(messageLabel, GTK_STATE_NORMAL, &black);

  GtkWidget *senderLabel = gtk_label_new(sender);
  gtk_widget_modify_fg(senderLabel, GTK_STATE_NORMAL, &black);

  // Layout
  gtk_box_pack_start(GTK_BOX(box), titleLabel, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), senderLabel, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), messageLabel, FALSE, FALSE, 0);

  // mail icon
  //GdkPixbuf *mailIconPixbuf = gdk_pixbuf_new_from_inline(mail_png_len, mail_png, FALSE, NULL);
  //GtkWidget *mailIcon = gtk_image_new_from_pixbuf(mailIconPixbuf);
  //g_object_unref(mailIconPixbuf);
  //gtk_box_pack_start(GTK_BOX(box), mailIcon, FALSE, FALSE, 0);

  // GTK2 doesnt have horizontal rules or gtk.seperator so we use this workaround
  GtkWidget *line = gtk_event_box_new();
  gtk_widget_set_size_request(line, -1, 2); // full width + 2px height
  gtk_widget_modify_bg(line, GTK_STATE_NORMAL, &black);
  gtk_box_pack_start(GTK_BOX(box), line, FALSE, FALSE, 0);

  return box;

  // todo
  //gtk_container_add(GTK_CONTAINER(event), frame);

  //return event;
};
