#ifndef _HANDLERS_H
#define _HANDLERS_H

#include <gtk/gtk.h>
#include <stdbool.h>

//Callbacks
void on_path_select(GtkEntry *, gpointer);
void on_file_select(GtkListBox *, GtkListBoxRow *, gpointer);

//Logic Functions
void display_files(const char *);

//Helper Functions
void clear_file_list();
GtkWidget *create_file_label(const char *);
gint sort_files(GtkListBoxRow *, GtkListBoxRow *, gpointer);
bool is_dir(const char *);
gchar *get_icon(gunichar);

#endif // _HANDLERS_H
