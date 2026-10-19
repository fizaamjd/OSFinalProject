#include <gtk/gtk.h>
#include <time.h>
#include <string.h>

static gboolean update_clock(gpointer data) {
    time_t now = time(NULL);
    struct tm *info = localtime(&now);
    char buffer[80];
    if (info && strftime(buffer, sizeof buffer, "%H:%M:%S [%Z]", info))
        gtk_label_set_text(GTK_LABEL(data), buffer);
    return G_SOURCE_CONTINUE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Clock");
    gtk_window_set_default_size(GTK_WINDOW(window), 250, 100);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *label = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(label), "<span font_desc='40' foreground='#333'>00:00:00 [Time Zone]</span>");

    gtk_container_add(GTK_CONTAINER(window), label);

    update_clock(label);
    g_timeout_add(1000, update_clock, label); // Update every second

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
