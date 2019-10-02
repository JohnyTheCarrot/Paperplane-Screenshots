#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <time.h>

bool success_modal_open = false;
GtkWidget *main_window;
bool hidden = false;

void delay(int number_of_seconds) 
{ 
    // Converting time into milli_seconds 
    int milli_seconds = 1000 * number_of_seconds; 
  
    // Stroing start time 
    clock_t start_time = clock(); 
  
    // looping till required time is not acheived 
    while (clock() < start_time + milli_seconds) 
        ;
} 

void main_window_hide_cb(GtkWidget *widget, gpointer   user_data)
{
	hidden = true;
}

void main_window_show_cb(GtkWidget *widget, gpointer   user_data)
{
	hidden = false;
}

static void take_screenshot ()
{
	system("screen -d -m ./paperplane-ss-dev");
	gtk_widget_destroy (main_window);
}


static void show_message_dialog2 (GtkWindow *parent)
{
	GtkWidget *dialog;

	dialog = GTK_WIDGET (gtk_message_dialog_new (parent,
												GTK_DIALOG_MODAL|
												GTK_DIALOG_DESTROY_WITH_PARENT|
												GTK_DIALOG_USE_HEADER_BAR,
												GTK_MESSAGE_INFO,
												GTK_BUTTONS_NONE,
												"Are you sure you'd like to quit?"));
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog),
												"You will lose your changes.");
	gtk_dialog_add_buttons (GTK_DIALOG (dialog), 
							"Cancel", GTK_RESPONSE_CANCEL,
							"Yes", GTK_RESPONSE_OK,
							NULL);  

	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

void settings_activate (GtkImageMenuItem *menuitem, gpointer user_data)
{
    GtkBuilder      *builder; 
    GtkWidget       *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "settings.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "settings_window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
}


void cancel_activate (GtkImageMenuItem *menuitem, gpointer user_data)
{
	gtk_main_quit ();
}

void option_cancel_activate (GtkButton *button, gpointer user_data)
{
	gtk_main_quit ();
}

void option_whole_screen (GtkButton *button, gpointer user_data)
{
  	take_screenshot ();
}

void attempt_quit (GtkWidget *window)
{
	if (success_modal_open != true)
	{
		gtk_main_quit ();
	}
}


int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		switch(argv[1][1])
		{
			case 'w': ;
				GtkBuilder      *builder; 
				gtk_init(&argc, &argv);

				builder = gtk_builder_new();
				gtk_builder_add_from_file (builder, "main_window.glade", NULL);

				main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
				gtk_builder_connect_signals(builder, NULL);
				g_signal_connect(G_OBJECT(main_window), "destroy", gtk_main_quit, NULL);
				g_object_unref(builder);

				gtk_widget_show(main_window);                
				gtk_main();
				return 0;
			case 'r': ;
				printf("%s\n", "Coming soon!");
				break;
			default: ;
				printf("%s\n", "Unknown flag.");
				break;
		}
		return 0;
	}
	take_screenshot ();
	return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
