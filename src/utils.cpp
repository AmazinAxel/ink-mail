#include <gtk-2.0/gtk/gtk.h>
#include "app.hpp"

void clearWindow(GtkWidget *container) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(container));
    for (GList *l = children; l != NULL; l = l->next) {
        gtk_widget_destroy(GTK_WIDGET(l->data));
    };
    g_list_free(children);
};

GtkWidget* horizontalRule() {
  // GTK2 doesnt have horizontal rules or gtk.seperator so we use this workaround
  GtkWidget *line = gtk_event_box_new();
  gtk_widget_set_size_request(line, -1, 2); // full width + 2px height
  return line;
}