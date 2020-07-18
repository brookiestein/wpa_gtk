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

#include "get_help.h"

gint
get_help(GtkWidget *parent)
{
        GtkMessageType mtype    = GTK_MESSAGE_INFO;
        GtkButtonsType btype    = GTK_BUTTONS_OK;
        gchar *title            = "Help";

        gchar *message          = "Using this tool is very simple! You only need to input your\n\
Wi-Fi network's SSID in the field called \"SSID\" and the same process for the password. \
If your Wi-Fi network is hidden, you need\n\
to inform to WPA Supplicant marking the check box below the last field.\n\n\
Also, you may want to restart the WPA Supplicant service.\n\
So WPA Supplicant will read the new configuration that includes the newest Wi-Fi network.";

        return show_message(GTK_WINDOW(parent), mtype, btype, title, message);
}
