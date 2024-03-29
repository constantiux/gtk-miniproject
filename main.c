#include <gtk/gtk.h>

void activate(GtkApplication* app, gpointer user_data);

int main(int argc, char** argv) {
	srand(time(0));
	GtkApplication* app;
	int status;
	app = gtk_application_new("org.gtk.highlow", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return status;
}