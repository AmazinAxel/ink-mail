#pragma once
#include <string>

struct emailData {
  std::string title;
  std::string message;
  std::string date;
};

int mailList(int argc, char *argv[], GtkWidget *vbox);
GtkWidget* mailItem(const char *title, const char *message, const char *sender);
