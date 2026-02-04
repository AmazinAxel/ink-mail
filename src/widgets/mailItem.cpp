#include <gtk-2.0/gtk/gtk.h>
#include "../app.hpp"
#include <iostream>
#include <thread>
#include <list>
#include "../icons/mail_icon.h"
#include "../icons/clock_icon.h"

GtkWidget *mailItem(const char *title, const char *message, const char *sender, const char *time) {
  GtkWidget *hbox = gtk_vbox_new(FALSE, 2);
  GtkWidget *box = gtk_vbox_new(FALSE, 2);
  //gtk_box_pack_start(GTK_BOX(hbox), gtk_label_new(title), FALSE, FALSE, 0);

  // GTK2 doesnt have horizontal rules or gtk.seperator so we use this workaround
  GtkWidget *line = gtk_event_box_new();
  gtk_widget_set_size_request(line, -1, 2); // full width + 2px height
  gtk_box_pack_start(GTK_BOX(box), line, FALSE, FALSE, 0);

  // Labels
  GtkWidget *titleLabel = gtk_label_new(NULL);
  std::string titleMarkup = "<span size=\"20000\" foreground=\"black\">" + std::string(title) + "</span>";
  gtk_label_set_markup(GTK_LABEL(titleLabel), titleMarkup.c_str());

  GtkWidget *messageLabel = gtk_label_new(message);
  std::string messageMarkup = "<span size=\"15000\" foreground=\"black\">" + std::string(message) + "</span>";
  gtk_label_set_markup(GTK_LABEL(messageLabel), messageMarkup.c_str());

  GtkWidget *senderLabel = gtk_label_new(sender);
  std::string senderMarkup = "<span size=\"12000\" foreground=\"black\">" + std::string(sender) + "</span>";
  gtk_label_set_markup(GTK_LABEL(senderLabel), senderMarkup.c_str());

  GtkWidget *timeLabel = gtk_label_new(time);
  std::string timeMarkup = "<span size=\"12000\" foreground=\"black\">" + std::string(time) + "</span>";
  gtk_label_set_markup(GTK_LABEL(timeLabel), timeMarkup.c_str());

  /*
  // Mail icon
  GdkPixbuf *mailIconPixbuf = gdk_pixbuf_new_from_inline(mail_png_len, mail_png, FALSE, NULL);
  GtkWidget *mailIcon = gtk_image_new_from_pixbuf(mailIconPixbuf);
  g_object_unref(mailIconPixbuf);
  gtk_box_pack_start(GTK_BOX(box), mailIcon, FALSE, FALSE, 0);

  // Clock icon
  GdkPixbuf *clockIconPixbuf = gdk_pixbuf_new_from_inline(clock_png_len, clock_png, FALSE, NULL);
  GtkWidget *clockIcon = gtk_image_new_from_pixbuf(clockIconPixbuf);
  g_object_unref(clockIconPixbuf);
  gtk_box_pack_start(GTK_BOX(box), clockIcon, FALSE, FALSE, 0);
  */

  // Layout
  gtk_box_pack_start(GTK_BOX(box), titleLabel, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), senderLabel, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), messageLabel, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), timeLabel, FALSE, FALSE, 0);

  return box;

  // todo
  //gtk_container_add(GTK_CONTAINER(event), frame);

  //return event;
};
