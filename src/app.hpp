#pragma once
#include <string>
#include <gtk-2.0/gtk/gtk.h>

struct emailData {
  GtkWidget *vbox;
  std::string subject;
  std::string from;
  std::string sendDate;
  std::string message;
};

int mailList(GtkWidget *vbox);
GtkWidget* mailItem(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time);
GtkWidget* mailPage(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time);
void clearWindow(GtkWidget *container);
GtkWidget* horizontalRule();

std::string fetch_latest_email_raw(const std::string &server, const std::string &user, const std::string &pass);
std::string extract_field(const std::string &src, const std::string &field);

extern GdkColor white; // defined in main.cpp
