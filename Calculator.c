#include <gtk/gtk.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>

static GtkWidget *left_entry, *right_entry, *operation, *result;
static gboolean read_number(GtkWidget *entry, double *value) {
    const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
    char *end;
    errno = 0;
    *value = g_ascii_strtod(text, &end);
    if (end == text) return FALSE;
    while (g_ascii_isspace(*end)) ++end;
    return end != text && *end == '\0' && errno != ERANGE && isfinite(*value);
}
static void calculate(GtkWidget *widget, gpointer data) {
    (void)widget; (void)data;
    double a, b, answer;
    if (!read_number(left_entry, &a) || !read_number(right_entry, &b)) {
        gtk_label_set_text(GTK_LABEL(result), "Enter two finite numbers."); return;
    }
    int op = gtk_combo_box_get_active(GTK_COMBO_BOX(operation));
    if (op == 3 && b == 0) {
        gtk_label_set_text(GTK_LABEL(result), "Cannot divide by zero."); return;
    }
    switch (op) {
        case 0: answer = a + b; break;
        case 1: answer = a - b; break;
        case 2: answer = a * b; break;
        case 3: answer = a / b; break;
        default: return;
    }
    if (!isfinite(answer)) {
        gtk_label_set_text(GTK_LABEL(result), "Result is outside the supported range."); return;
    }
    char text[G_ASCII_DTOSTR_BUF_SIZE];
    g_ascii_dtostr(text, sizeof text, answer);
    gtk_label_set_text(GTK_LABEL(result), text);
}
int main(int argc, char **argv) {
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 360, 240);
    gtk_container_set_border_width(GTK_CONTAINER(window), 16);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    left_entry = gtk_entry_new(); right_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(left_entry), "First number");
    gtk_entry_set_placeholder_text(GTK_ENTRY(right_entry), "Second number");
    gtk_widget_set_tooltip_text(left_entry, "First number");
    gtk_widget_set_tooltip_text(right_entry, "Second number");
    operation = gtk_combo_box_text_new();
    const char *ops[] = {"Add", "Subtract", "Multiply", "Divide"};
    for (int i = 0; i < 4; ++i) gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(operation), ops[i]);
    gtk_combo_box_set_active(GTK_COMBO_BOX(operation), 0);
    result = gtk_label_new("Enter numbers to calculate.");
    GtkWidget *button = gtk_button_new_with_label("Calculate");
    g_signal_connect(button, "clicked", G_CALLBACK(calculate), NULL);
    GtkWidget *children[] = {left_entry, operation, right_entry, button, result};
    for (int i = 0; i < 5; ++i) gtk_box_pack_start(GTK_BOX(box), children[i], FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
