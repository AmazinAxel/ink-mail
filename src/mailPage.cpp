#include <gtk-2.0/gtk/gtk.h>
#include "app.hpp"
#include <string> // std::string
#include "icons/arrowBack_icon.h"
#include "icons/mail_icon.h"
#include "icons/clock_icon.h"

void backToMailList(GtkWidget*, GdkEventButton*, gpointer data) {
  GtkWidget *vbox = GTK_WIDGET(data);
  mailList(vbox);
};

GtkWidget *mailPage(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time) {
  clearWindow(vbox); // Cleanup

  // Back button
  GtkWidget *backButtonParent = gtk_hbox_new(FALSE, 0);
  GdkPixbuf *backPixbuf = gdk_pixbuf_new_from_inline(arrowBack_png_len, arrowBack_png, FALSE, NULL);
  GtkWidget *backIcon = gtk_image_new_from_pixbuf(backPixbuf);
  g_object_unref(backPixbuf);

  GtkWidget *backButton = gtk_event_box_new();
  gtk_container_add(GTK_CONTAINER(backButton), backIcon);
  g_signal_connect(backButton, "button-press-event", G_CALLBACK(backToMailList), vbox);
  gtk_widget_modify_bg(backButton, GTK_STATE_NORMAL, &white);
  gtk_box_pack_start(GTK_BOX(backButtonParent), backButton, FALSE, FALSE, 10); // Left padding

  /* Mail window */

  GtkWidget *listBox = gtk_vbox_new(FALSE, 10);
  GtkWidget *titleRow = gtk_hbox_new(FALSE, 2);

  GtkWidget *pageScrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pageScrollbar), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  GtkWidget *centerAlign = gtk_alignment_new(0.5, 0, 0.5, 0);
  gtk_container_add(GTK_CONTAINER(centerAlign), listBox);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pageScrollbar), centerAlign);

  // Make scrollable background white
  GtkWidget *viewport = gtk_bin_get_child(GTK_BIN(pageScrollbar));
  gtk_widget_modify_bg(viewport, GTK_STATE_NORMAL, &white);

  // Labels
  GtkWidget *titleLabel = gtk_label_new(NULL);
  std::string titleMarkup = "<span size=\"20000\" foreground=\"black\">" + std::string(g_markup_escape_text(title, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(titleLabel), titleMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(titleLabel), 0.0, 0.5); // Left align
  gtk_label_set_max_width_chars(GTK_LABEL(titleLabel), 20);
  gtk_label_set_ellipsize(GTK_LABEL(titleLabel), PANGO_ELLIPSIZE_END);

  GtkWidget *messageLabel = gtk_label_new(message);
  std::string messageMarkup = "<span size=\"15000\" foreground=\"black\">" + std::string(g_markup_escape_text(message, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(messageLabel), messageMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(messageLabel), 0.0, 0.5); // Left align

  gtk_label_set_line_wrap(GTK_LABEL(messageLabel), TRUE);
  gtk_label_set_line_wrap_mode(GTK_LABEL(messageLabel), PANGO_WRAP_WORD_CHAR);
  gtk_misc_set_alignment(GTK_MISC(messageLabel), 0.0, 0.0);
  gtk_widget_set_size_request(messageLabel, 800, -1);

GtkWidget *senderLabel = gtk_label_new(sender);
  std::string senderMarkup = "<span size=\"12000\" foreground=\"black\">" + std::string(g_markup_escape_text(sender, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(senderLabel), senderMarkup.c_str());

  GtkWidget *timeLabel = gtk_label_new(time);
  std::string timeMarkup = "<span size=\"12000\" foreground=\"black\">" + std::string(g_markup_escape_text(time, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(timeLabel), timeMarkup.c_str());

  // Scaled down mail icon
  GtkWidget *senderRow = gtk_hbox_new(FALSE, 3); // 3px padding
  GdkPixbuf *mailIconPixbuf = gdk_pixbuf_new_from_inline(mail_png_len, mail_png, FALSE, NULL);

  GdkPixbuf *mailIconScaled = gdk_pixbuf_scale_simple(mailIconPixbuf, 25, 25, GDK_INTERP_BILINEAR);
  g_object_unref(mailIconPixbuf);
  GtkWidget *mailIcon = gtk_image_new_from_pixbuf(mailIconScaled);
  g_object_unref(mailIconScaled);

  // Scaled down clock icon
  GdkPixbuf *clockIconPixbuf = gdk_pixbuf_new_from_inline(clock_png_len, clock_png, FALSE, NULL);
  GdkPixbuf *clockIconScaled = gdk_pixbuf_scale_simple(clockIconPixbuf, 25, 25, GDK_INTERP_BILINEAR);
  g_object_unref(clockIconPixbuf);
  GtkWidget *clockIcon = gtk_image_new_from_pixbuf(clockIconScaled);
  g_object_unref(clockIconScaled);

  /* Layout */

  gtk_box_pack_start(GTK_BOX(vbox), backButtonParent, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), horizontalRule(), FALSE, FALSE, 0);

  // Title + time + icons on same row
  gtk_box_pack_start(GTK_BOX(titleRow), titleLabel, TRUE, TRUE, 0); // Expands to right
  gtk_box_pack_start(GTK_BOX(titleRow), clockIcon, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(titleRow), timeLabel, FALSE, FALSE, 0);

  // Sender icon + label on same row
  gtk_box_pack_start(GTK_BOX(senderRow), mailIcon, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(senderRow), senderLabel, FALSE, FALSE, 0);

  // Title, sender, message
  gtk_box_pack_start(GTK_BOX(listBox), titleRow, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), senderRow, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), messageLabel, FALSE, FALSE, 10);

  return pageScrollbar;
};
