#include "file_list.h"

#include "ui.h"
#include "history.h"
#include "search.h"

#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>


/*
 * Clears all file entries in file list
 */

void clear_file_list() {
  gtk_container_foreach(GTK_CONTAINER(g_widgets.file_list),
                       (GtkCallback) gtk_widget_destroy, NULL);
} /* clear_file_list() */


/*
 * Called when new path is supplied for file list.
 * !!!!DOES NOT UPDATE HISTORY!!!!
 */

void on_new_path(const char *path) {
  clear_file_list();
  display_files(path);
} /* on_new_path() */


/*
 * Gets full path based on relative path and base path
 */

char *get_full_path(const char *base_path, const char *rel_path) {
  char *new_path;
  if (strncmp(base_path, "/", 2) == 0) {
    new_path = g_strdup_printf("/%s", rel_path);
  }
  else {
    new_path = g_strdup_printf("%s/%s", base_path, rel_path);
  }
  return new_path;
} /* get_full_path() */


/*
 * Used to convert icons of various file types from USC-4 to UTF-8
 */

gchar *get_icon(gunichar c) {
  gchar *icon = calloc(6, sizeof(gchar));
  assert(icon);
  g_unichar_to_utf8(c, icon);
  return icon;
} /* get_icon() */


/*
 * Creates file label for file with correct icon
 * Path is a relative path
 */

GtkWidget *create_file_label(const char *path, unsigned char type) {
  // Set icon based on if file or directory
  gchar *icon;
  if (type == DT_DIR) { // DIRECTORY
    icon = get_icon(0x0001F4C1);
  } 
  else if (type == DT_LNK) { // SYM LINK
    icon = get_icon(0x00001F4C2);
  }
  else { // FILE
    icon = get_icon(0x0001F4C4);
  }
  
  // Create label and its markup
  gchar *label_markup = g_strdup_printf("<span font=\"Symbola_hint\">%s %s</span>", icon, path);
  GtkWidget *label = gtk_label_new(NULL);
  gtk_label_set_markup(GTK_LABEL(label), label_markup);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0);
  gtk_widget_show(label);
  
  // Free strings
  g_free(icon);
  g_free(label_markup);

  return label;
} /* create_file_container() */


/*
 * Adds all files in a directory to file list
 * TODO ADD SUPPORT FOR FILE
 */

void display_files(const char *path) {
  // If file selected
  if (!is_dir(path)) {
    puts("TODO ADD SUPPORT FOR ENTERING FILE");
    return;
  }
  
  // Creates entry in list for each file in directory
  DIR *d = opendir(path);
  struct dirent *entry;
  while ((entry = readdir(d)) != NULL) {
    char *entry_path = entry->d_name;
    if ((strncmp(entry_path, ".", 2) == 0) ||
        (strncmp(entry_path, "..", 3) == 0)) { //ignore dot directories
      continue;
    }
    GtkWidget *file_label = create_file_label(entry_path, entry->d_type);
    gtk_container_add(GTK_CONTAINER(g_widgets.file_list), file_label);
  } /* end while */
  closedir(d);
} /* display_files() */


/*
 * Called when user hits enter on text field
 * Either goes to specified path or searches for files based on text
 * Updates history if path is specified
 */

void on_path_select(GtkEntry *entry, gpointer use_data) {
  const char *full_path = gtk_entry_get_text(GTK_ENTRY(entry));

  if (strlen(full_path) < 0) {
    return;
  }

  clear_history_list(g_history_current);
  g_history_current = NULL;

  if (full_path[0] == '/') { // Path entry
    on_new_path(full_path);
    update_history(full_path);
  }
  else { // Search entry
    on_search(full_path);
  }

} /* on_path_select() */


/*
 * Called when user clicks on file in file list
 * Updates history and displays next depth level of file structure
 */

void on_file_activate(GtkListBox *list_box, GtkListBoxRow *row, gpointer user_data) {
  const char *label_text = gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row))));

  if (label_text[0] == '/') { // Check if was search label
    on_new_path(label_text);
    gtk_entry_set_text(GTK_ENTRY(g_widgets.text_entry), label_text);
    update_history(label_text);
    return;
  }

  // Get full path
  const char *base_path = gtk_entry_get_text(GTK_ENTRY(g_widgets.text_entry));
  char *new_path = get_full_path(base_path, &label_text[5]); // 5 ignores icon
  
  on_new_path(new_path);
  gtk_entry_set_text(GTK_ENTRY(g_widgets.text_entry), new_path);
  update_history(new_path);

  free(new_path);
} /* on_file_select() */


/*
 * Returns if file is directory
 */

bool is_dir(const char *path) {
  struct stat sb;
  stat(path, &sb);
  return S_ISDIR(sb.st_mode);
} /* is_dir() */


/*
 * TODO
 */

gint sort_files(GtkListBoxRow *row1, GtkListBoxRow *row2, gpointer user_data) {
  const char *text1 = gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row1))));
  const char *text2 = gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(row2))));
  return strcmp(text1, text2);
} /* sort_files() */
