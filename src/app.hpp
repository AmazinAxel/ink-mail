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

struct Mail { GtkWidget *vbox; const char *title; const char *message; const char *sender; const char *time; };

extern GdkColor white; // defined in main.cpp
