#ifndef _SEARCH_H
#define _SEARCH_Ha

#include <gtk/gtk.h>
#include <ftw.h>

void on_search(const char *);
int check_file(const char *, const struct stat *, int);
GtkWidget *create_search_result_label(const char *);

#endif
