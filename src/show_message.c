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

#include "show_message.h"

gint
show_message(GtkWindow *parent, GtkMessageType mtype,
GtkButtonsType btype, gchar *title, gchar *message)
{
        GtkDialogFlags flag     = GTK_DIALOG_DESTROY_WITH_PARENT;
        GtkWidget *dialog       = gtk_message_dialog_new(parent, flag, mtype, btype, "%s", message);
        gtk_window_set_title(GTK_WINDOW(dialog), title);
        gint response           = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return response;
}
