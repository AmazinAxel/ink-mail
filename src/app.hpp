#pragma once
#include <string>
#include <vector>
#include <gtk-2.0/gtk/gtk.h>

struct emailData {
  GtkWidget *vbox;
  std::string subject;
  std::string message;
  std::string from;
  std::string sendDate;
};

int mailList(GtkWidget *vbox);
GtkWidget* mailItem(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time);
GtkWidget* mailPage(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time);
void clearWindow(GtkWidget *container);
GtkWidget* horizontalRule();

std::vector<emailData> fetchMail(const std::string &imap, const std::string &email, const std::string &password);

extern GdkColor white; // defined in main.cpp
