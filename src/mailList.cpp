#include <gtk-2.0/gtk/gtk.h>
#include "app.hpp"
#include "icons/refresh_icon.h"
#include "icons/arrowBack_icon.h"

int mailList(int argc, char *argv[], GtkWidget *vbox) {
  
  /* Top title/navigation bar */

  GtkWidget *nav = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), nav, FALSE, FALSE, 0);
  GtkBox *navBox GTK_BOX(nav);

  // Exit
  GdkPixbuf *exitPixbuf = gdk_pixbuf_new_from_inline(arrowBack_png_len, arrowBack_png, FALSE, NULL);
  GtkWidget *exitIcon = gtk_image_new_from_pixbuf(exitPixbuf);
  g_object_unref(exitPixbuf);
  gtk_box_pack_start(navBox, exitIcon, FALSE, FALSE, 10);

  GtkWidget *leftCenterSpacer = gtk_label_new(NULL);
  gtk_box_pack_start(navBox, leftCenterSpacer, TRUE, TRUE, 0);

  // Mail title
  GtkWidget *title = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(title), "<span size=\"30000\" foreground=\"black\">Mail</span>");
  gtk_box_pack_start(navBox, title, FALSE, FALSE, 0);

  GtkWidget *rightCenterSpacer = gtk_label_new(NULL);
  gtk_box_pack_start(navBox, rightCenterSpacer, TRUE, TRUE, 0);

  // Refresh
  GdkPixbuf *refreshPixbuf = gdk_pixbuf_new_from_inline(refresh_png_len, refresh_png, FALSE, NULL);
  GtkWidget *refreshIcon = gtk_image_new_from_pixbuf(refreshPixbuf);
  g_object_unref(refreshPixbuf);
  gtk_box_pack_end(navBox, refreshIcon, FALSE, FALSE, 10);

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
  GdkColor white;
  gdk_color_parse("#fff", &white);
  gtk_widget_modify_bg(viewport, GTK_STATE_NORMAL, &white);

  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (2)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (3)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (4)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (5)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (6)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (7)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (8)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (9)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(listBox), mailItem("This is a message subject (10)", "Message content", "axel@amazinaxel.com", "15:20"), FALSE, FALSE, 0);

  return 0;
};