#ifndef _FILE_LIST_H
#define _FILE_LIST_H

#include <gtk/gtk.h>
#include <stdbool.h>

//Callbacks
void on_path_select(GtkEntry *, gpointer);
void on_file_activate(GtkListBox *, GtkListBoxRow *, gpointer);

//Logic Functions
void on_new_path(const char *);
void display_files(const char *);

//Helper Functions
GtkWidget *create_file_label(const char *, unsigned char);
gint sort_files(GtkListBoxRow *, GtkListBoxRow *, gpointer);
bool is_dir(const char *);
gchar *get_icon(gunichar);
char *get_full_path(const char *, const char *);
void clear_file_list();
#endif // _FILE_LIST_H
