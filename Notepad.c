#include <gtk/gtk.h>

static GtkWidget *editor;
static GtkWidget *window;

static void show_error(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),
        GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void open_file(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Open text file", GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL,
        "Open", GTK_RESPONSE_ACCEPT, NULL);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        char *contents = NULL;
        gsize length = 0;
        GError *error = NULL;
        if (!g_file_get_contents(filename, &contents, &length, &error)) {
            show_error(error->message);
            g_clear_error(&error);
        } else if (!g_utf8_validate(contents, (gssize)length, NULL)) {
            show_error("This editor supports UTF-8 text files only.");
        } else {
            gtk_text_buffer_set_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor)), contents, (gint)length);
        }
        g_free(contents);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

static void save_file(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    GtkWidget *dialog = gtk_file_chooser_dialog_new("Save text file", GTK_WINDOW(window),
        GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL,
        "Save", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(editor));
        GtkTextIter start, end;
        gtk_text_buffer_get_bounds(buffer, &start, &end);
        char *contents = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
        GError *error = NULL;
        if (!g_file_set_contents(filename, contents, -1, &error)) {
            show_error(error->message);
            g_clear_error(&error);
        }
        g_free(contents);
        g_free(filename);
    }
    gtk_widget_destroy(dialog);
}

int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Notepad");
    gtk_window_set_default_size(GTK_WINDOW(window), 640, 480);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget *open = gtk_button_new_with_label("Open");
    GtkWidget *save = gtk_button_new_with_label("Save");
    g_signal_connect(open, "clicked", G_CALLBACK(open_file), NULL);
    g_signal_connect(save, "clicked", G_CALLBACK(save_file), NULL);
    gtk_box_pack_start(GTK_BOX(toolbar), open, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(toolbar), save, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(layout), toolbar, FALSE, FALSE, 6);
    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    editor = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(editor), GTK_WRAP_WORD_CHAR);
    gtk_container_add(GTK_CONTAINER(scroll), editor);
    gtk_box_pack_start(GTK_BOX(layout), scroll, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(window), layout);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
