#include <gtk-2.0/gtk/gtk.h>
#include <string> // std::string
#include "../app.hpp"
#include "../icons/mail_icon.h"
#include "../icons/clock_icon.h"

gboolean openMail(GtkWidget*, GdkEventButton*, gpointer data) {
  emailData *ctx = (emailData*)data;

  GtkWidget *page = mailPage(ctx->vbox, ctx->subject.c_str(), ctx->message.c_str(), ctx->from.c_str(), ctx->sendDate.c_str());
  gtk_box_pack_start(GTK_BOX(ctx->vbox), page, TRUE, TRUE, 0);
  gtk_widget_show_all(ctx->vbox);

  return true;
};

GtkWidget *mailItem(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time, const bool isRead) {
  GtkWidget *titleRow = gtk_hbox_new(FALSE, 2);
  GtkWidget *box = gtk_vbox_new(FALSE, 2);
  GtkWidget *eventBox = gtk_event_box_new();
  gtk_event_box_set_visible_window(GTK_EVENT_BOX(eventBox), FALSE);

  gtk_box_pack_start(GTK_BOX(box), horizontalRule(), FALSE, FALSE, 0);

  const char * color = "#000";
  if (isRead)
    color = "#383838";

  // Labels
  GtkWidget *titleLabel = gtk_label_new(nullptr);
  std::string titleMarkup = "<span size=\"20000\" foreground=\""  + std::string(color) + "\">" + std::string(g_markup_escape_text(title, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(titleLabel), titleMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(titleLabel), 0.0, 0.5); // Left align

  GtkWidget *messageLabel = gtk_label_new(nullptr);
  std::string messageMarkup = "<span size=\"15000\" foreground=\""  + std::string(color) + "\">" + std::string(g_markup_escape_text(message, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(messageLabel), messageMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(messageLabel), 0.0, 0.5); // Left align

  GtkWidget *senderLabel = gtk_label_new(nullptr);
  std::string senderMarkup = "<span size=\"12000\" foreground=\""  + std::string(color) + "\">" + std::string(g_markup_escape_text(sender, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(senderLabel), senderMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(senderLabel), 0.0, 0.5); // Left align

  GtkWidget *timeLabel = gtk_label_new(nullptr);
  std::string timeMarkup = "<span size=\"12000\" foreground=\""  + std::string(color) + "\">" + std::string(g_markup_escape_text(time, -1)) + "</span>";
  gtk_label_set_markup(GTK_LABEL(timeLabel), timeMarkup.c_str());
  gtk_misc_set_alignment(GTK_MISC(timeLabel), 1.0, 0.5); // Right align

  // Scaled down clock icon
  GdkPixbuf *clockIconPixbuf = gdk_pixbuf_new_from_inline(clock_png_len, clock_png, FALSE, NULL);
  GdkPixbuf *clockIconScaled = gdk_pixbuf_scale_simple(clockIconPixbuf, 25, 25, GDK_INTERP_BILINEAR);
  g_object_unref(clockIconPixbuf);
  GtkWidget *clockIcon = gtk_image_new_from_pixbuf(clockIconScaled);
  g_object_unref(clockIconScaled);

  // Scaled down email icon
  GtkWidget *senderRow = gtk_hbox_new(FALSE, 3); // 3px padding
  GdkPixbuf *mailIconPixbuf = gdk_pixbuf_new_from_inline(mail_png_len, mail_png, FALSE, NULL);

  GdkPixbuf *mailIconScaled = gdk_pixbuf_scale_simple(mailIconPixbuf, 20, 20, GDK_INTERP_BILINEAR);
  g_object_unref(mailIconPixbuf);
  GtkWidget *mailIcon = gtk_image_new_from_pixbuf(mailIconScaled);
  g_object_unref(mailIconScaled);
  gtk_box_pack_start(GTK_BOX(senderRow), mailIcon, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(senderRow), senderLabel, FALSE, FALSE, 0);

  /* Layout */
  // Title + time + icons on same row
  gtk_box_pack_start(GTK_BOX(titleRow), titleLabel, TRUE, TRUE, 0); // Expands to right
  gtk_box_pack_start(GTK_BOX(titleRow), clockIcon, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(titleRow), timeLabel, FALSE, FALSE, 0);

  // Title, sender, message
  gtk_box_pack_start(GTK_BOX(box), titleRow, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(box), senderRow, TRUE, TRUE, 0);

  if (isRead) {
    GtkWidget *notReadLabel = gtk_label_new(nullptr);
    std::string notReadMarkup = "<span size=\"12000\" foreground=\""  + std::string(color) + "\">(Read)</span>";
    gtk_label_set_markup(GTK_LABEL(notReadLabel), notReadMarkup.c_str());
    gtk_misc_set_alignment(GTK_MISC(notReadLabel), 0.0, 0.5); // Left align
    gtk_box_pack_start(GTK_BOX(box), notReadLabel, FALSE, FALSE, 0);
  };

  gtk_box_pack_start(GTK_BOX(box), messageLabel, FALSE, FALSE, 0);

  // Clickable event box
  gtk_container_add(GTK_CONTAINER(eventBox), box);
  emailData *ctx = new emailData{vbox, title, message, sender, time};
  g_signal_connect(eventBox, "button-press-event", G_CALLBACK(openMail), ctx);
  return eventBox;
};
