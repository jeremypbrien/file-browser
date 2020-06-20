#include "ui.h"

#include "file_list.h"
#include "history.h"

struct widgets_s g_widgets;

void activate(GtkApplication *app, gpointer user_data) {
  //Window
  GtkWidget *window = gtk_application_window_new(app);
  g_widgets.window = window;
  gtk_window_set_title(GTK_WINDOW(window), "File Browser");
  gtk_window_set_default_size(GTK_WINDOW(window), 700, 900);

  //CSS
  GtkCssProvider *css_provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(css_provider, "css/style.css", NULL);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                            GTK_STYLE_PROVIDER(css_provider),
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

  //Main container
  GtkWidget *main_ctr = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), main_ctr);
  
  /* TOP BAR */

  //Top bar container
  GtkWidget *top_bar_ctr = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(main_ctr), top_bar_ctr, FALSE, TRUE, 5);

  //Back button
  GtkWidget *back_button = gtk_button_new_with_label("\u2190");
  g_widgets.back_button = back_button;
  gtk_box_pack_start(GTK_BOX(top_bar_ctr), back_button, FALSE, TRUE, 5);
  g_signal_connect(back_button, "clicked", G_CALLBACK(on_backward_click), NULL);

  //Forward button
  GtkWidget *forward_button = gtk_button_new_with_label("\u2192");
  g_widgets.forward_button = forward_button;
  gtk_box_pack_start(GTK_BOX(top_bar_ctr), forward_button, FALSE, TRUE, 5);
  g_signal_connect(forward_button, "clicked", G_CALLBACK(on_forward_click), NULL);

  //Settings button
  GtkWidget *settings_button = gtk_button_new_with_label("Settings");
  gtk_box_pack_end(GTK_BOX(top_bar_ctr), settings_button, FALSE, TRUE, 5);

  /* MIDDLE BAR */
  
  //Middle bar container
  GtkWidget *mid_bar_ctr = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start(GTK_BOX(main_ctr), mid_bar_ctr, TRUE, TRUE, 0);

  //Left bar container
  GtkWidget *left_mid_ctr = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(mid_bar_ctr), left_mid_ctr, FALSE, TRUE, 5);

  //Right bar container
  GtkWidget *right_mid_ctr = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(mid_bar_ctr), right_mid_ctr, TRUE, TRUE, 5);

  //Left side TODO

  //Right side text entry
  GtkWidget *right_mid_entry = gtk_entry_new();
  g_widgets.text_entry = right_mid_entry;
  gtk_box_pack_start(GTK_BOX(right_mid_ctr), right_mid_entry, FALSE, TRUE, 0);
  g_signal_connect(right_mid_entry, "activate", G_CALLBACK(on_path_select), NULL);

  //Right side file list
  GtkWidget *file_scroll_bar = gtk_scrolled_window_new(NULL, NULL);
  GtkWidget *right_file_list = gtk_list_box_new();
  g_widgets.file_list = right_file_list;
  gtk_list_box_set_sort_func(GTK_LIST_BOX(right_file_list), sort_files, NULL, NULL);
  gtk_list_box_set_activate_on_single_click(GTK_LIST_BOX(right_file_list), FALSE);
  g_signal_connect(right_file_list, "row-activated", G_CALLBACK(on_file_activate), NULL);
  gtk_container_add(GTK_CONTAINER(file_scroll_bar), right_file_list);
  gtk_box_pack_start(GTK_BOX(right_mid_ctr), file_scroll_bar, TRUE, TRUE, 5);
  
  update_buttons_status();
  gtk_widget_show_all(window);
  on_new_path("/");
  update_history("/");
} /* activate() */
