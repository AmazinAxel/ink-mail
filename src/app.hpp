#pragma once
#include <string>

struct emailData {
  std::string title;
  std::string message;
  std::string date;
};

int mailList(GtkWidget *vbox);
GtkWidget* mailItem(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time);
GtkWidget* mailPage(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time);
void clearWindow(GtkWidget *container);
GtkWidget* horizontalRule();

std::string fetch_latest_email_raw(const std::string &server, const std::string &user, const std::string &pass);
std::string extract_field(const std::string &src, const std::string &field);

struct Mail { GtkWidget *vbox; const char *title; const char *message; const char *sender; const char *time; };

extern GdkColor white; // defined in main.cpp
