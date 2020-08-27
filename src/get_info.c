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

#include "get_info.h"

gint
get_info(GtkWidget *parent)
{
        GtkMessageType mtype    = GTK_MESSAGE_INFO;
        GtkButtonsType btype    = GTK_BUTTONS_OK;
        gchar *title            = "About";

        gchar *message          = "This is a little tool to save and connect \
to new Wi-Fi connections.\n\
This tool uses WPA Supplicant, so you need to have installed it.\n\
If you want to know more about this project, please don't forget\n\
to visit its website.\n\n\
Name: WPA GTK\n\
Version: 1.3.1\n\
License: GPL v2\n\
Author(s): Lord Brookie\n\
Website: https://github.com/brookiestein/wpa_gtk";

        return show_message(GTK_WINDOW(parent), mtype, btype, title, message);
}
