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

#include "save_and_connect.h"

static const unsigned char ARRAY_MAX_SIZE = 255;
static gchar *title, *message;

static gint
shell(const gchar *command)
{
        FILE *fp        = popen(command, "r");
        if (fp == NULL) {
                fprintf(stderr, "An error occurred while the command '%s' was being executed.\n",
                        command);
                return 1;
        }

        return pclose(fp);
}

static gboolean
verify_protocol_and_password_length(const gchar *security,
const gchar *password)
{
        gboolean is_there_an_error = FALSE;

        if (security == NULL) {
                title             = "Unselected protocol";
                message           = "The security protocol has not been chosen.";
                is_there_an_error = TRUE;
        } else if (strlen(password) < 8 && strncmp(security, "Open", 4)) {
                title             = "Short password";
                message           = "The given password is so short.";
                is_there_an_error = TRUE;
        }

        return is_there_an_error;
}

static gint
clear_fields(gint value)
{
        gtk_entry_buffer_set_text(ssid_buffer, "", -1);
        gtk_entry_buffer_set_text(password_buffer, "", -1);
        gtk_combo_box_set_active(GTK_COMBO_BOX(security_combo), -1);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(hidden_check), FALSE);
        return value;
}

gint
save_and_connect(GtkWidget *parent)
{
        GtkMessageType mtype    = GTK_MESSAGE_WARNING;
        GtkButtonsType btype    = GTK_BUTTONS_OK;

        if (shell("which wpa_supplicant > /dev/null 2>&1")) { /* Error */
                title           = "Warning";
                message         = "The WPA Supplicant binary has not been found in your system.";
                show_message(GTK_WINDOW(parent), mtype, btype, title, message);
                return clear_fields(EXIT_FAILURE);
        }

        const gchar *ssid         = gtk_entry_buffer_get_text(ssid_buffer);
        const gchar *password     = gtk_entry_buffer_get_text(password_buffer);
        const gchar *security     = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(security_combo));
        const gchar *wpa_file     = "/etc/wpa_supplicant/wpa_supplicant.conf";
        gchar scan_ssid;

        if (verify_protocol_and_password_length(security, password)) {
                show_message(GTK_WINDOW(parent), mtype, btype, title, message);
                return clear_fields(EXIT_FAILURE);
        }

        scan_ssid = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(hidden_check)) ? '1' : '0';

        FILE *fp;
        gchar *content = (gchar *) malloc(ARRAY_MAX_SIZE * sizeof(gchar));

        if (strncmp(security, "WPA2-PSK", 8) == 0) {
                size_t command_len      = 16 + strlen(ssid) + 2 + strlen(password) + 26;

                gchar *hashed_pass      = (gchar *) malloc(ARRAY_MAX_SIZE * sizeof(gchar));
                gchar command[ARRAY_MAX_SIZE];

                snprintf(command, command_len,
                        "wpa_passphrase \"%s\" \"%s\" | grep psk | tail -n 1",
                        ssid, password);

                fp              = popen(command, "r");
                hashed_pass     = fgets(hashed_pass, ARRAY_MAX_SIZE, fp);

                snprintf(content, ARRAY_MAX_SIZE, "\nnetwork={\n\
\tssid=\"%s\"\n\
\tscan_ssid=%c\n\
%s\
\tpriority=5\n\
}\n", ssid, scan_ssid, hashed_pass);

                free(hashed_pass);
                pclose(fp);
        /* end if */
        } else if (strncmp(security, "WEP", 3) == 0) {

                snprintf(content, ARRAY_MAX_SIZE, "\nnetwork={\n\
\tssid=\"%s\"\n\
\tscan_ssid=%c\n\
\twep_key0=\"%s\"\n\
\twep_tx_keyidx=0\n\
\tpriority=5\n\
}\n", ssid, scan_ssid, password);
        /* end else if */
        } else {
                snprintf(content, ARRAY_MAX_SIZE, "\nnetwork={\n\
\tssid=\"%s\"\n\
\tscan_ssid=%c\n\
\tkey_mgmt=NONE\n\
\tpriority=5\n\
}\n", ssid, scan_ssid);
        /* end else */
        }

        fp              = fopen(wpa_file, "a");
        if (fp == NULL) {
                free(content);
                title           = "Warning";
                message         = "You don't have enough privileges to do that.\n\
Make sure you have writing permission in the WPA Supplicant's configuration file.\n\
Or consider to run this program as user root.";
                show_message(GTK_WINDOW(parent), mtype, btype, title, message);
                return clear_fields(EXIT_FAILURE);
        }

        fwrite(content, sizeof(gchar), strlen(content), fp);

        fclose(fp);
        free(content);

        mtype     = GTK_MESSAGE_QUESTION;
        btype     = GTK_BUTTONS_YES_NO;
        title     = "Congratulation";
        message   = "The network has been added successfully!\n\
Would you like to restart the WPA Supplicant service?";

        gint res  = show_message(GTK_WINDOW(parent), mtype, btype, title, message);

        if (res == GTK_RESPONSE_YES) {
                btype           = GTK_BUTTONS_OK;
                char command[]  = "/etc/init.d/wpa_supplicant restart > /dev/null 2>&1";
                int state       = shell(command);

                if (state == 0) {
                        mtype   = GTK_MESSAGE_INFO;
                        message = "The WPA Supplicant service has been restarted successfully.";
                } else {
                        mtype   = GTK_MESSAGE_WARNING;
                        message = "An error occurred while the WPA Supplicant\n\
service was being restarted.";
                }

                show_message(GTK_WINDOW(parent), mtype, btype, title, message);
        }

        return clear_fields(EXIT_SUCCESS);
}
