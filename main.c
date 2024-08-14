#include <gtk/gtk.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <unistd.h>

int interval = 1000;
gboolean auto_clicking = FALSE;
guint timeout_id = 0;

void leftClick(CGPoint pos)
{
    CGEventRef click_down = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseDown,
        pos, kCGMouseButtonLeft);

    CGEventRef click_up = CGEventCreateMouseEvent(
        NULL, kCGEventLeftMouseUp,
        pos, kCGMouseButtonLeft);

    CGEventPost(kCGHIDEventTap, click_down);
    CGEventPost(kCGHIDEventTap, click_up);

    CFRelease(click_down);
    CFRelease(click_up);
}

CGPoint getMousePosition()
{
    CGEventRef event = CGEventCreate(NULL);
    CGPoint point = CGEventGetLocation(event);
    CFRelease(event);
    return point;
}

gboolean checkForExitKey()
{
    if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_Escape))
        return TRUE;
    if (CGEventSourceKeyState(kCGEventSourceStateHIDSystemState, kVK_ANSI_Q))
        return TRUE;
    return FALSE;
}

gboolean auto_clicker(gpointer data)
{
    if (!auto_clicking) return FALSE;

    if (checkForExitKey())
    {
        auto_clicking = FALSE;
        return FALSE;
    }

    CGPoint pos = getMousePosition();
    leftClick(pos);

    return TRUE;
}

void on_start_button_clicked(GtkWidget *widget, gpointer entry)
{
    const char *entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
    interval = atoi(entry_text);

    if (auto_clicking) return;

    auto_clicking = TRUE;
    sleep(3);

    timeout_id = g_timeout_add(interval, auto_clicker, NULL);
}

void on_stop_button_clicked(GtkWidget *widget, gpointer data)
{
    if (timeout_id > 0)
    {
        g_source_remove(timeout_id);
        timeout_id = 0;
    }
    auto_clicking = FALSE;
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Autoclicker");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 150);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    GtkWidget *label = gtk_label_new("Intervalle entre les clics (ms) :");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    GtkWidget *entry = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entry), "1000");
    gtk_box_pack_start(GTK_BOX(vbox), entry, FALSE, FALSE, 0);

    GtkWidget *start_button = gtk_button_new_with_label("Cliquez pour activer");
    gtk_box_pack_start(GTK_BOX(vbox), start_button, FALSE, FALSE, 0);

    GtkWidget *stop_button = gtk_button_new_with_label("Stop");
    gtk_box_pack_start(GTK_BOX(vbox), stop_button, FALSE, FALSE, 0);

    g_signal_connect(start_button, "clicked", G_CALLBACK(on_start_button_clicked), entry);
    g_signal_connect(stop_button, "clicked", G_CALLBACK(on_stop_button_clicked), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
