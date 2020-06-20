#include "history.h"
#include "ui.h"
#include "file_list.h"

#include <assert.h>

hist_node_t *g_history_current = NULL;


void update_buttons_status() {
  gtk_widget_set_sensitive(g_widgets.forward_button, TRUE);
  gtk_widget_set_sensitive(g_widgets.back_button, TRUE);

  if (g_history_current == NULL) {
    gtk_widget_set_sensitive(g_widgets.forward_button, FALSE);
    gtk_widget_set_sensitive(g_widgets.back_button, FALSE);
    return;
  }

  if (g_history_current->next == NULL) {
    gtk_widget_set_sensitive(g_widgets.forward_button, FALSE);
  }

  if (g_history_current->prev == NULL) {
    gtk_widget_set_sensitive(g_widgets.back_button, FALSE);
  }
} /* update_buttons_status() */


void on_forward_click(GtkButton *button, gpointer user_data) {
  assert(g_history_current);
  assert(g_history_current->next);

  g_history_current = g_history_current->next;
  on_new_path(g_history_current->path);
  gtk_entry_set_text(GTK_ENTRY(g_widgets.text_entry), g_history_current->path);
  update_buttons_status();
} /* on_forward_click() */


void on_backward_click(GtkButton *button, gpointer user_data) {
  assert(g_history_current);
  assert(g_history_current->prev);

  g_history_current = g_history_current->prev;
  on_new_path(g_history_current->path);
  gtk_entry_set_text(GTK_ENTRY(g_widgets.text_entry), g_history_current->path);
  update_buttons_status();
} /* on_backward_click() */


void clear_history_list(hist_node_t *current) {
  if (current == NULL) {
    return;
  }

  hist_node_t *prev = current->prev;
  if (prev != NULL) {
    prev->next = NULL;
  }

  hist_node_t *next = current->next;
  if (next != NULL) {
    next->prev = NULL;
  }

  free(current->path);
  free(current);
  clear_history_list(prev);
  clear_history_list(next);
} /* clear_history_list() */


void update_history(const char *path) {
  if (g_history_current == NULL) {
    hist_node_t *node = malloc(sizeof(hist_node_t));
    assert(node);
    node->prev = NULL;
    node->next = NULL;
    node->path = malloc(strlen(path) + 1);
    assert(node->path);
    strcpy(node->path, path);
    g_history_current = node;
  }
  else if (g_history_current->next == NULL) {
    hist_node_t *node = malloc(sizeof(hist_node_t));
    assert(node);
    node->prev = g_history_current;
    node->next = NULL;
    node->path = malloc(strlen(path) + 1);
    assert(node->path);
    strcpy(node->path, path);
    g_history_current->next = node;
    g_history_current = node;
  }
  else if (strcmp(g_history_current->next->path, path) != 0) {
    char *tmp_path = malloc(strlen(g_history_current->path) + 1);
    assert(tmp_path);
    strcpy(tmp_path, g_history_current->path);

    clear_history_list(g_history_current);
    g_history_current = NULL;
    update_history(tmp_path);
    free(tmp_path);
    update_history(path);
  }
  else {
    g_history_current = g_history_current->next;
  }
  update_buttons_status();
} /* add_path_to_history() */
