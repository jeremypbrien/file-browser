#include "search.h"
#include "file_list.h"
#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <ftw.h>
#include <stdbool.h>

#define ROOT_DIRECTORY "/"

static const char *current_search = NULL;
static bool is_searching = false;

void on_search(const char *search_text) {
  if (is_searching) { // Lock to prevent multiple searches
    is_searching = false;
    while (current_search != NULL) { // waits for search to stop
    }
  }

  clear_file_list();
  current_search = search_text;
  is_searching = true;
  ftw(ROOT_DIRECTORY, check_file, 10);
  current_search = NULL;
  is_searching = false;
} /* on_search() */


int check_file(const char *path, const struct stat *sg, int typeflag) {
  if (!is_searching) {
    return -1;
  }

  char *relative_path = &strrchr(path, '/')[1];
  if (strstr(relative_path, current_search) != NULL) {
    GtkWidget *label = create_search_result_label(path);
    gtk_container_add(GTK_CONTAINER(g_widgets.file_list), label);
  }

  return 0;
} /* check_file() */


GtkWidget *create_search_result_label(const char *path) {
  gchar *label_markup = g_strdup_printf("<span font=\"Symbola_hint\">%s</span>", path);
  GtkWidget *label = gtk_label_new(NULL);

  gtk_label_set_markup(GTK_LABEL(label), label_markup);
  gtk_label_set_xalign(GTK_LABEL(label), 0.0);
  gtk_widget_show(label);

  g_free(label_markup);
  return label;
} /* create_search_result_label() */
