#ifndef _HANDLERS_H
#define _HANDLERS_H

#include <gtk/gtk.h>

//Callbacks
void on_path_select(GtkEntry *, gpointer);
void on_file_select(GtkListBox *, GtkListBoxRow *, gpointer);

//Logic Functions
void display_files(const char *);

//Helper Functions
void clear_file_list();
GtkWidget *create_file_containter(const char *);
gint sort_files(GtkListBoxRow *, GtkListBoxRow *, gpointer);

#endif // _HANDLERS_H
