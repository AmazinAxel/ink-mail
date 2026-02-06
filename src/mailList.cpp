#include <gtk-2.0/gtk/gtk.h>
#include <string>
#include "app.hpp"
#include "icons/refresh_icon.h"
#include "icons/arrowBack_icon.h"
#include "icons/mail_icon.h"
#include <curl/curl.h>
#include <iostream>

GtkWidget *globalRefreshButton;

void refreshMail(GtkWidget*, GdkEventButton*, gpointer data) {
  // Make refresh button not clickable
  gtk_widget_set_sensitive(globalRefreshButton, FALSE);

  GtkWidget *vbox = GTK_WIDGET(data);

  gtk_box_pack_start(GTK_BOX(vbox), horizontalRule(), FALSE, FALSE, 0);
  GtkWidget *fetchText = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(fetchText), "<span size=\"25000\" foreground=\"black\">Fetching mail...</span>");
  gtk_box_pack_start(GTK_BOX(vbox), fetchText, FALSE, FALSE, 10);
  gtk_widget_show_all(vbox);

  fetchMailAsync(IMAP, EMAIL, PASSWORD, [=]() { mailList(vbox); });
};

int mailList(GtkWidget *vbox) {
  clearWindow(vbox); // Cleanup & hide Fetching mail text

  /* Top title/navigation bar */
  GtkWidget *nav = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), nav, FALSE, FALSE, 0);
  GtkBox *navBox = GTK_BOX(nav);

  // Exit button
  GdkPixbuf *exitPixbuf = gdk_pixbuf_new_from_inline(arrowBack_png_len, arrowBack_png, FALSE, NULL);
  GtkWidget *exitIcon = gtk_image_new_from_pixbuf(exitPixbuf);
  g_object_unref(exitPixbuf);

  GtkWidget *exitButton = gtk_event_box_new();
  gtk_container_add(GTK_CONTAINER(exitButton), exitIcon);
  g_signal_connect(exitButton, "button-press-event", gtk_main_quit, NULL);
  gtk_box_pack_start(navBox, exitButton, FALSE, FALSE, 10);
  gtk_widget_modify_bg(exitButton, GTK_STATE_NORMAL, &white);

  GtkWidget *leftCenterSpacer = gtk_label_new(NULL);
  gtk_box_pack_start(navBox, leftCenterSpacer, TRUE, TRUE, 0);

  // Mail icon
  GdkPixbuf *mailPixbuf = gdk_pixbuf_new_from_inline(mail_png_len, mail_png, FALSE, NULL);
  GtkWidget *mailIcon = gtk_image_new_from_pixbuf(mailPixbuf);
  g_object_unref(mailPixbuf);
  gtk_box_pack_start(navBox, mailIcon, FALSE, FALSE, 0);

  // Mail title
  GtkWidget *title = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(title), "<span size=\"30000\" foreground=\"black\">Mail</span>");
  gtk_box_pack_start(navBox, title, FALSE, FALSE, 10);

  GtkWidget *rightCenterSpacer = gtk_label_new(NULL);
  gtk_box_pack_start(navBox, rightCenterSpacer, TRUE, TRUE, 0);

  // Refresh button
  GdkPixbuf *refreshPixbuf = gdk_pixbuf_new_from_inline(refresh_png_len, refresh_png, FALSE, NULL);
  GtkWidget *refreshIcon = gtk_image_new_from_pixbuf(refreshPixbuf);
  g_object_unref(refreshPixbuf);

  GtkWidget *refreshButton = gtk_event_box_new();
  globalRefreshButton = refreshButton; // For disabling while refreshing

  gtk_container_add(GTK_CONTAINER(refreshButton), refreshIcon);
  g_signal_connect(refreshButton, "button-press-event", G_CALLBACK(refreshMail), vbox);
  gtk_widget_modify_bg(refreshButton, GTK_STATE_NORMAL, &white);
  gtk_widget_modify_bg(refreshButton, GTK_STATE_INSENSITIVE, &white); // For when button is disabled
  gtk_box_pack_end(navBox, refreshButton, FALSE, FALSE, 10);

  /* Mail list */

  GtkWidget *mailListScrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(mailListScrollbar), GTK_POLICY_NEVER, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start(GTK_BOX(vbox), mailListScrollbar, TRUE, TRUE, 5);

  GtkWidget *centerAlign = gtk_alignment_new(0.5, 0, 0.5, 0);
  GtkWidget *listBox = gtk_vbox_new(FALSE, 10);

  gtk_container_add(GTK_CONTAINER(centerAlign), listBox);
  gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(mailListScrollbar), centerAlign);

  // Make scrollable background white
  GtkWidget *viewport = gtk_bin_get_child(GTK_BIN(mailListScrollbar));
  gtk_widget_modify_bg(viewport, GTK_STATE_NORMAL, &white);

  // Fetching
  if (emails.empty()) {
    refreshMail(nullptr, nullptr, vbox);
  } else {
    for (auto &mail : emails)
      gtk_box_pack_start(GTK_BOX(listBox), mailItem(vbox, mail.subject.c_str(), mail.message.c_str(), mail.from.c_str(), mail.sendDate.c_str()), FALSE, FALSE, 0);
    gtk_widget_show_all(vbox);
  };

  return 0;
};
