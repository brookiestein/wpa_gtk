/*
* Copyright (C) 19aa <Lord Brookie>
* This program is free software. You can redistribute it and/or
* modify it under the terms of the General Public License
* GNU as published by the Free Software Foundation,
* either version 2 of said License or --according to its
* choice-- of any later version.
* This program is distributed in the hope that it will be
* useful, but WITHOUT ANY WARRANTY, even without warranty
* MERCANTIL implicit or without guaranteeing CONVENIENCE FOR A
* PARTICULAR PURPOSE. For more details, see the License
* GNU General Public.
* You should have received a copy of the Public License
* General along with this program. Otherwise, write
* to the Free Software Foundation, Inc., at 675 Mass Ave,
* Cambridge, MA 02139, USA.
*/

#include "main.h"

static gint
set_sensitive(GtkWidget *password_entry)
{
        gboolean setting        = TRUE;
        const gchar *security   = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(security_combo));
        if (security != NULL && strncmp(security, "Open", 4) == 0) {
                setting         = FALSE;
        }

        gtk_widget_set_sensitive(password_entry, setting);
        return 0;
}

static gint
inform(GtkWindow *parent)
{
        GtkMessageType mtype    = GTK_MESSAGE_WARNING;
        GtkButtonsType btype    = GTK_BUTTONS_OK;
        char title[]            = "Warning";
        char message[]          = "You have executed it as normal user. \
Your experience will be limited.\n\
If you want to enjoy all wpagtk's features, please consider to execute\n\
it as user root.";
        return show_message(parent, mtype, btype, title, message);
}

int
main(int argc, char *argv[])
{
        GtkBuilder *builder;
        GtkWidget *window;
        GtkWidget *quit_item, *clear_item, *help_item, *about_item;
        GtkWidget *ssid_entry, *password_entry;
        GtkWidget *save_button, *leave_button;
        gchar *ui       = "resources/ui.glade";

        gtk_init(&argc, &argv);

        FILE *res_file  = fopen(ui, "r");
        if (res_file == NULL) {
                /* This path is just created when you run the make install order. */
                ui      = "/usr/share/wpagtk/resources/ui.glade";
        } else {
                fclose(res_file);
        }

        builder         = gtk_builder_new_from_file(ui);
        window          = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

        quit_item       = GTK_WIDGET(gtk_builder_get_object(builder, "quit_item"));
        clear_item      = GTK_WIDGET(gtk_builder_get_object(builder, "clear_fields_item"));
        about_item      = GTK_WIDGET(gtk_builder_get_object(builder, "about_item"));
        help_item       = GTK_WIDGET(gtk_builder_get_object(builder, "help_item"));

        ssid_entry      = GTK_WIDGET(gtk_builder_get_object(builder, "ssid_entry"));
        password_entry  = GTK_WIDGET(gtk_builder_get_object(builder, "password_entry"));

        security_combo  = GTK_WIDGET(gtk_builder_get_object(builder, "security_combo"));

        hidden_check    = GTK_WIDGET(gtk_builder_get_object(builder, "hidden_check"));

        save_button     = GTK_WIDGET(gtk_builder_get_object(builder, "save_and_connect_button"));
        leave_button    = GTK_WIDGET(gtk_builder_get_object(builder, "close_button"));

        ssid_buffer     = gtk_entry_buffer_new(NULL, -1);
        password_buffer  = gtk_entry_buffer_new(NULL, -1);

        gtk_entry_set_buffer(GTK_ENTRY(ssid_entry), ssid_buffer);
        gtk_entry_set_buffer(GTK_ENTRY(password_entry), password_buffer);

        gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
        gtk_entry_set_input_purpose(GTK_ENTRY(password_entry), GTK_INPUT_PURPOSE_PASSWORD);

        gtk_builder_connect_signals(builder, NULL);
        g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

        g_signal_connect_swapped(quit_item, "activate", G_CALLBACK(leave), window);

        g_signal_connect_swapped(clear_item, "activate", G_CALLBACK(clear_fields), window);

        g_signal_connect_swapped(about_item, "activate", G_CALLBACK(get_info), window);
        g_signal_connect_swapped(help_item, "activate", G_CALLBACK(get_help), window);

        g_signal_connect_swapped(security_combo, "changed", G_CALLBACK(set_sensitive), password_entry);

        g_signal_connect_swapped(save_button, "clicked", G_CALLBACK(save_and_connect), window);
        g_signal_connect_swapped(leave_button, "clicked", G_CALLBACK(leave), window);

        gtk_widget_show_all(window);

        if (geteuid()) {
                inform(GTK_WINDOW(window));
        }

        gtk_main();
        return 0;
}
