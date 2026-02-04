#include <gtk-2.0/gtk/gtk.h>
#include "app.hpp"

void clearWindow(GtkWidget *container) {
    GList *children = gtk_container_get_children(GTK_CONTAINER(container));
    for (GList *l = children; l != NULL; l = l->next) {
        gtk_widget_destroy(GTK_WIDGET(l->data));
    };
    g_list_free(children);
};
