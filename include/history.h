#ifndef _HISTORY_H
#define _HISTORY_H

#include <gtk/gtk.h>
#include <stdbool.h>

typedef struct hist_node_s {
  char *path;
  struct hist_node_s *prev;
  struct hist_node_s *next;
} hist_node_t;

extern hist_node_t *g_history_current;

//Button Functions
void on_forward_click(GtkButton *, gpointer);
void on_backward_click(GtkButton *, gpointer);
void update_buttons_status();


//List Functions
void clear_history_list(hist_node_t *);
void update_history(const char *);
bool path_in_history(const char *);


#endif // _HISTORY_H
