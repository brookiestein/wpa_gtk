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

#ifndef __GTK_H__
#include <gtk/gtk.h>
#endif

#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

#ifndef _STRING_H
#include <string.h>
#endif

#ifndef SHOW_MESSAGE_H
#include "show_message.h"
#endif

#ifndef SAVE_AND_CONNECT_H
#define SAVE_AND_CONNECT_H 1
#endif

/* Defined on main.h */
extern GtkEntryBuffer *ssid_buffer, *password_buffer;
extern GtkWidget *security_combo, *hidden_check;

gint save_and_connect(GtkWidget *parent);
