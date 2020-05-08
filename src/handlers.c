#include "handlers.h"

#include "ui.h"

#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


gchar *get_icon(gunichar c) {
  gchar *icon = malloc(sizeof(gchar) * 6);
  memset(icon, 0, 6);
  assert(icon);
  int bytes_read = g_unichar_to_utf8(c, icon);
  assert(bytes_read == 4);
  return icon;
} /* get_icon() */


GtkWidget *create_file_label(const char *path) {
  gchar *icon;
  if (is_dir(path)){ // DIRECTORY
    icon = get_icon(0x0001F4C1);
  } else { // FILE
    icon = get_icon(0x0001F5CE);
  }

  gchar *text = g_strdup_printf("%s %s", icon, path);
  GtkWidget *label = gtk_label_new(text);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0);
  gtk_widget_show(label);
  g_free(icon);
  g_free(text);
  return label;
} /* create_file_container() */


void display_files(const char *path) {
  if (!is_dir(path)) {
    puts("TODO ADD SUPPORT FOR ENTERING FILE");
    return;
  }
  
  DIR *d = opendir(path);
  struct dirent *entry;
  while ((entry = readdir(d)) != NULL) {
    char *entry_path = entry->d_name;
    if ((strncmp(entry_path, ".", 2) == 0) ||
        (strncmp(entry_path, "..", 3) == 0)) {
      continue;
    }
    GtkWidget *file_label = create_file_label(entry_path);
    gtk_container_add(GTK_CONTAINER(g_widgets.file_list), file_label);
  } /* end while */
  closedir(d);
} /* display_files() */


void clear_file_list() {
  gtk_container_foreach(GTK_CONTAINER(g_widgets.file_list),
                       (GtkCallback) gtk_widget_destroy, NULL);
} /* clear_file_list() */


void on_path_select(GtkEntry *entry, gpointer use_data) {
  printf("New Path: <%s>\n", gtk_entry_get_text(GTK_ENTRY(entry)));
  clear_file_list();
  display_files(gtk_entry_get_text(GTK_ENTRY(entry)));
} /* on_path_select() */


void on_file_select(GtkListBox *list_box, GtkListBoxRow *row, gpointer user_data) {
  clear_file_list();
  printf("TODO FILE SELECT\n");
} /* on_file_select() */


gint sort_files(GtkListBoxRow *row1, GtkListBoxRow *row2, gpointer user_data) {
  const char *text1 = gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row1))));
  const char *text2 = gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row2))));
  return strcmp(&text1[5], &text2[5]);
}

bool is_dir(const char *path) {
  struct stat sb;
  stat(path, &sb);
  return S_ISDIR(sb.st_mode);
} /* is_dir() */
