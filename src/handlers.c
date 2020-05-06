#include "handlers.h"

#include "ui.h"


GtkWidget *create_file_container(const char *path) {
  return NULL;
} /* create_file_container() */


void display_files(const char *path) {
} /* display_files() */


void clear_file_list() {
  gtk_container_foreach(GTK_CONTAINER(g_widgets.file_list),
                       (GtkCallback) gtk_widget_destroy, NULL);
} /* clear_file_list() */


void on_path_select(GtkEntry *entry, gpointer use_data) {
  printf("New Path: <%s>\n", gtk_entry_get_text(GTK_ENTRY(entry)));
  clear_file_list();
  puts("\U0001F4C1");
  display_files(gtk_entry_get_text(GTK_ENTRY(entry)));
} /* on_path_select() */


void on_file_select(GtkListBox *list_box, GtkListBoxRow *row, gpointer user_data) {
  clear_file_list();
  printf("TODO FILE SELECT\n");
} /* on_file_select() */


gint sort_files(GtkListBoxRow *row1, GtkListBoxRow *row2, gpointer user_data) {
  return 0;
}
