#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

const char *homedir;
char save_dir[] = "/Pictures/Paperplane Screenshots";
char last_filename[20];

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

void option_close (GtkButton *button, gpointer user_data)
{
	gtk_main_quit ();
}

void option_copy (GtkButton *button, gpointer user_data)
{
    /*if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    char buf[150];
    snprintf(buf, 150, "xclip -selection clipboard -t image/png -o > \"%s%s/%s\"", homedir, save_dir, last_filename);
    printf("%s\n", buf);
	system(buf);*/
}

void option_open (GtkButton *button, gpointer user_data)
{
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    char buf[100];
    snprintf(buf, 100, "xdg-open \"%s%s\"", homedir, save_dir);
	system(buf);
}

static void show_success_modal ()
{
	printf("%s\n", "yeet");
	GtkBuilder      *builder; 
    GtkWidget       *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "success.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "success"));
    g_signal_connect(G_OBJECT(window), "destroy", gtk_main_quit, NULL);
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);
    gtk_main();
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    //delay (1000);
    Display *disp;
	Window root;
	cairo_surface_t *surface;
	int scr;
	/* try to connect to display, exit if it's NULL */
	disp = XOpenDisplay( 0 );
	if( disp == NULL ){
		fprintf(stderr, "Given display cannot be found, exiting: %s\n" , "0");
		return 1;    	
	}
	scr = DefaultScreen(disp);
	root = DefaultRootWindow(disp);
	/* get the root surface on given display */
	surface = cairo_xlib_surface_create(disp, root, DefaultVisual(disp, scr),
													DisplayWidth(disp, scr), 
													DisplayHeight(disp, scr));
	/* right now, the tool only outputs PNG images */
	char buf[100];
    int filename = (int)time(NULL);
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    snprintf(last_filename, 100, "%i.png", filename);
	snprintf(buf, 100, "%s%s/%i.png", homedir, save_dir, filename);
	cairo_surface_write_to_png( surface, buf );
	/* free the memory*/
	cairo_surface_destroy(surface);
	show_success_modal ();
    return 0;
}