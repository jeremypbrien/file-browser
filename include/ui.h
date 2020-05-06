#ifndef _UI_H
#define _UI_H

#include <gtk/gtk.h>

struct widgets_s {
  GtkWidget *window;
  GtkWidget *back_button;
  GtkWidget *forward_button;
  GtkWidget *text_entry;
  GtkWidget *file_list;
};

extern struct widgets_s g_widgets;


void activate(GtkApplication *, gpointer);

#endif // _UI_H
