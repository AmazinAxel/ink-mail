#pragma once
#include <string>
#include <functional>
#include <vector>
#include <gtk-2.0/gtk/gtk.h>

struct emailData {
  GtkWidget *vbox;
  std::string subject;
  std::string message;
  std::string from;
  std::string sendDate;
  bool isRead;
  int uid;
};

// Utils
void clearWindow(GtkWidget *container);
GtkWidget* horizontalRule();

int mailList(GtkWidget *vbox);
GtkWidget* mailItem(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time, const bool isRead, int uid);
GtkWidget* mailPage(GtkWidget *vbox, const char *title, const char *message, const char *sender, const char *time);
bool markEmailAsRead(const std::string& imap, const std::string& email, const std::string& password, int uid);

void fetchMailAsync(const std::string& imap, const std::string& email, const std::string& password, std::function<void()> onDone);

// All defined in main.cpp
extern GdkColor white;
extern std::vector<emailData> emails;
extern int currMailUID;
