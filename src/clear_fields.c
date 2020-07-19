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

#include "clear_fields.h"

gint
clear_fields(GtkWidget *parent)
{
        int c                   = 0;
        const gchar *ssid       = gtk_entry_buffer_get_text(ssid_buffer);
        const gchar *password   = gtk_entry_buffer_get_text(password_buffer);
        const gchar *security   = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(security_combo));

        if (strlen(ssid) > 0) {
                gtk_entry_buffer_set_text(ssid_buffer, "", -1);
                c++;
        }

        if (strlen(password) > 0) {
                gtk_entry_buffer_set_text(password_buffer, "", -1);
                c++;
        }

        if (security != NULL) {
                gtk_combo_box_set_active(GTK_COMBO_BOX(security_combo), -1);
                c++;
        }

        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(hidden_check))) {
                gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(hidden_check), FALSE);
                c++;
        }

        if (c == 0) {
                GtkMessageType mtype    = GTK_MESSAGE_WARNING;
                GtkButtonsType btype    = GTK_BUTTONS_OK;
                gchar *title            = "Warning";
                gchar *message          = "There's nothing to do.";
                return show_message(GTK_WINDOW(parent), mtype, btype,
                        title, message);
        }

        return 0;
}
