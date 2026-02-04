#include <gtk-2.0/gtk/gtk.h>
#include "app.hpp"
#include <string> // std::string
#include "icons/mail_icon.h"
#include "icons/clock_icon.h"

GtkWidget *mailPage(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time) {
  clearWindow(vbox); // Cleanup

  GtkWidget *hbox = gtk_vbox_new(FALSE, 2);
  GtkWidget *box = gtk_vbox_new(FALSE, 2);
  GtkWidget *titleRow = gtk_hbox_new(FALSE, 2);

  // GTK2 doesnt have horizontal rules or gtk.seperator so we use this workaround
  GtkWidget *line = gtk_event_box_new();
  gtk_widget_set_size_request(line, -1, 2); // full width + 2px height
  gtk_box_pack_start(GTK_BOX(box), line, FALSE, FALSE, 0);

  // Labels
  GtkWidget *titleLabel = gtk_label_new(NULL);
  std::string titleMarkup = "<span size=\"20000\" foreground=\"black\">" + std::string(title) + "</span>";
  gtk_label_set_markup(GTK_LABEL(titleLabel), titleMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(titleLabel), 0.0, 0.5); // Left align

  GtkWidget *messageLabel = gtk_label_new(message);
  std::string messageMarkup = "<span size=\"15000\" foreground=\"black\">" + std::string(message) + "</span>";
  gtk_label_set_markup(GTK_LABEL(messageLabel), messageMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(messageLabel), 0.0, 0.5); // Left align

  GtkWidget *senderLabel = gtk_label_new(sender);
  std::string senderMarkup = "<span size=\"12000\" foreground=\"black\">" + std::string(sender) + "</span>";
  gtk_label_set_markup(GTK_LABEL(senderLabel), senderMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(senderLabel), 0.0, 0.5); // Left align

  GtkWidget *timeLabel = gtk_label_new(time);
  std::string timeMarkup = "<span size=\"12000\" foreground=\"black\">" + std::string(time) + "</span>";
  gtk_label_set_markup(GTK_LABEL(timeLabel), timeMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(timeLabel), 1.0, 0.5); // Right align

  /*
  // Mail icon
  GdkPixbuf *mailIconPixbuf = gdk_pixbuf_new_from_inline(mail_png_len, mail_png, FALSE, NULL);
  GtkWidget *mailIcon = gtk_image_new_from_pixbuf(mailIconPixbuf);
  g_object_unref(mailIconPixbuf);
  gtk_box_pack_start(GTK_BOX(box), mailIcon, FALSE, FALSE, 0);
  */

  // Scaled down clock icon
  GdkPixbuf *clockIconPixbuf = gdk_pixbuf_new_from_inline(clock_png_len, clock_png, FALSE, NULL);
  GdkPixbuf *clockIconScaled = gdk_pixbuf_scale_simple(clockIconPixbuf, 25, 25, GDK_INTERP_BILINEAR);
  g_object_unref(clockIconPixbuf);
  GtkWidget *clockIcon = gtk_image_new_from_pixbuf(clockIconScaled);
  g_object_unref(clockIconScaled);

  /* Layout */
  // Title + time + icons on same row
  gtk_box_pack_start(GTK_BOX(titleRow), titleLabel, TRUE, TRUE, 0); // Expands to right
  gtk_box_pack_start(GTK_BOX(titleRow), clockIcon, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(titleRow), timeLabel, FALSE, FALSE, 0);

  // Title, sender, message
  gtk_box_pack_start(GTK_BOX(box), titleRow, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), senderLabel, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), messageLabel, FALSE, FALSE, 0);

  return box;
};
