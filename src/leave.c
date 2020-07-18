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

#include "leave.h"

gint
leave(GtkWidget *parent)
{
        GtkMessageType mtype    = GTK_MESSAGE_QUESTION;
        GtkButtonsType btype    = GTK_BUTTONS_YES_NO;
        gchar *title            = "Confirmation";
        gchar *message          = "Are you really sure that want to leave?";
        gint response           = show_message(GTK_WINDOW(parent), mtype, btype, title, message);

        if (response == GTK_RESPONSE_YES) {
                gtk_widget_destroy(parent);
        }

        return response;
}
