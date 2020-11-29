#include <stdio.h>
#include <stdlib.h>

#include "gui.h"

GtkWidget* button_higher;
GtkWidget* frame_box;
GtkWidget* north_container;
GtkWidget* panel_container;
GtkWidget* button_container;
GtkWidget* info_container;
GtkWidget* south_container;
GtkWidget* button_higher;
GtkWidget* button_lower;
GtkWidget* button_pass;		// Extension part
GtkWidget* button_new;
GtkWidget* button_quit;
GtkWidget* button_hint;		// Extension part
GtkWidget* button_cheat;	// Extension part
GtkWidget* text_prompt;
GtkTextBuffer* buffer_prompt;

void clear_child(GtkWidget* container) {
	GList *children, *iter;
	children = gtk_container_get_children(GTK_CONTAINER(container));
	for (iter = children; iter != NULL; iter = g_list_next(iter))
		gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);
}

void clear_container(int container_id) {
	if (container_id == 0) {
		clear_child(north_container);
	} else {
		clear_child(south_container);
	}
}

void set_prompt(char* prompt) {
	gtk_text_buffer_set_text(buffer_prompt, prompt, -1);
}

void show_ingame_buttons() {
	gtk_widget_show(button_higher);
	gtk_widget_show(button_lower);
	gtk_widget_show(button_pass);  // Extension part
	gtk_widget_show(button_hint);  // Extension part
	gtk_widget_show(button_cheat);  // Extension part
}

void hide_ingame_buttons() {
	gtk_widget_hide(button_higher);
	gtk_widget_hide(button_lower);
	gtk_widget_hide(button_pass);  // Extension part
	gtk_widget_hide(button_hint);  // Extension part
	gtk_widget_hdie(button_cheat); // Extension part
}

void swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

char* get_image_path(int card) {
	char* path = malloc(20);

	int bound = ((card / 4) * 4 + 4) %
		    52;	     // (0-3) -> 4, ..., (15-18) -> 16, ...,(48-51) -> 0
	int pos = card % 4;  // position of the "cards" array

	int cards[4] = {0};

	int i;
	for (i = 0; i < 4; i++) {
		cards[i] = bound;
		bound++;
	}

	// e.g. card = 15, bound = 16, pos = 3
	// original cards = [4, 5, 6, 7]
	// swapped cards = [7, 6, 4, 5]

	// original -> h, s, d, c
	// convert to
	// desired -> c, d, h, s
	swap(&cards[3], &cards[0]);  // swapped to c, s, d, h
	swap(&cards[3], &cards[1]);  // swapped to c, h, d, s
	swap(&cards[2], &cards[1]);  // swapped to c, d, h, s

	sprintf(path, "picture/%d.png", cards[pos]);
	return path;
}

void add_image(int container_id, int card) {
	GtkWidget* image;
	GtkWidget* container;
	if (container_id == 0) {
		container = north_container;
	} else {
		container = south_container;
	}
	char* file_name = get_image_path(card);
	image = gtk_image_new_from_file(file_name);
	gtk_container_add(GTK_CONTAINER(container), image);
	gtk_widget_show_all(container);
}

void quit_game(GtkWindow* window) {
	// close the game
	// This contains extended functionalities
	GtkDialogFlags flags =
	    GTK_DIALOG_MODAL |
	    GTK_DIALOG_DESTROY_WITH_PARENT;  // modal dialog to force user
					     // attention
	GtkWidget* dialog =
	    gtk_message_dialog_new(window, flags, GTK_MESSAGE_QUESTION,
				   GTK_BUTTONS_YES_NO, "Are you sure to quit?");

	gtk_window_set_title(GTK_WINDOW(dialog), "Confirmation");

	int result = gtk_dialog_run(GTK_DIALOG(dialog));  // get response signal
	switch (result) {
		case GTK_RESPONSE_YES:
			gtk_widget_destroy(dialog);
			gtk_widget_destroy(GTK_WIDGET(window));
			break;
		default:
			gtk_widget_destroy(dialog);
			break;
	}
}

void activate(GtkApplication* app, gpointer user_data) {
	GtkWidget* window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "HighLow");
	gtk_window_set_default_size(GTK_WINDOW(window), 1200, 400);
	int padding = 2;

	frame_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	north_container = gtk_box_new(FALSE, 0);
	panel_container = gtk_box_new(FALSE, 0);
	button_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	info_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	south_container = gtk_box_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(north_container), 20);
	gtk_container_set_border_width(GTK_CONTAINER(panel_container), 20);
	gtk_container_set_border_width(GTK_CONTAINER(button_container), 20);
	gtk_container_set_border_width(GTK_CONTAINER(info_container), 20);
	gtk_container_set_border_width(GTK_CONTAINER(south_container), 20);
	button_higher = gtk_button_new_with_label("Higher!");
	button_lower = gtk_button_new_with_label("Lower!");
	button_pass = gtk_button_new_with_label("Pass");  // Extension part
	button_new = gtk_button_new_with_label("New Game");
	button_quit = gtk_button_new_with_label("Quit Game");
	button_hint = gtk_button_new_with_label("Hint");  // Extension part
	button_hint = gtk_button_new_with_label("Cheat"); // Extension part
	text_prompt = gtk_text_view_new();
	buffer_prompt = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_prompt));

	gtk_container_add(GTK_CONTAINER(window), frame_box);
	gtk_box_pack_start(GTK_BOX(frame_box), north_container, FALSE, FALSE,
			   padding);
	gtk_box_pack_start(GTK_BOX(frame_box), panel_container, FALSE, FALSE,
			   padding);
	gtk_box_pack_start(GTK_BOX(panel_container), button_container, FALSE,
			   FALSE, padding);
	gtk_box_pack_start(GTK_BOX(panel_container), info_container, FALSE,
			   FALSE, padding);
	gtk_box_pack_start(GTK_BOX(frame_box), south_container, FALSE, FALSE,
			   padding);

	gtk_box_pack_start(GTK_BOX(button_container), button_higher, FALSE,
			   FALSE, padding);
	gtk_box_pack_start(GTK_BOX(button_container), button_lower, FALSE,
			   FALSE, padding);
	gtk_box_pack_start(GTK_BOX(button_container), button_pass, FALSE, FALSE,
			   padding);  // Extension part
	gtk_box_pack_start(GTK_BOX(button_container), button_cheat, FALSE, FALSE,
			   padding);  // Extension part
	gtk_box_pack_start(GTK_BOX(button_container), button_new, FALSE, FALSE,
			   padding);
	gtk_box_pack_start(GTK_BOX(button_container), button_quit, FALSE, FALSE,
			   padding);
	gtk_box_pack_start(GTK_BOX(button_container), button_hint, FALSE, FALSE,
			   padding);  // Extension part
	g_signal_connect_swapped(button_quit, "clicked", G_CALLBACK(quit_game),
				 window);
	gtk_box_pack_start(GTK_BOX(info_container), text_prompt, FALSE, FALSE,
			   padding);

	g_signal_connect(button_new, "clicked", G_CALLBACK(new_game), NULL);
	g_signal_connect(button_higher, "clicked", G_CALLBACK(on_click_higher),
			 NULL);
	g_signal_connect(button_lower, "clicked", G_CALLBACK(on_click_lower),
			 NULL);
	g_signal_connect(button_pass, "clicked", G_CALLBACK(on_click_pass),
			 NULL);	 // Extension part
	g_signal_connect(button_hint, "clicked", G_CALLBACK(on_click_hint),
			 (gpointer)window);  // Extension part
	g_signal_connect(button_cheat, "clicked", G_CALLBACK(on_click_cheat),
			 (gpointer)window);  // Extension part
	gtk_text_buffer_set_text(buffer_prompt, "", -1);

	gtk_widget_show_all(window);
	hide_ingame_buttons();
}