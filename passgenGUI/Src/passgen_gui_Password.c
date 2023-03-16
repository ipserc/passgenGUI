/*
 * passgen_gui_Password.c
 *
 *  Created on: 21 feb. 2023
 *      Author: ipserc
 */

#include "passgen_gui_Password.h"

#define __DEBUG__ false

/* ***********************************************************
 * gtkEntry_Password_Text
 *********************************************************** */

/**
 * Fills up gtkEntry_Password_Text with text
 */
void gtkEntryPasswordTextSet(char * text)
{
	GtkEntry * gtkEntryPasswordText = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_Password_Text"));
	gtk_entry_set_text((GtkEntry *) gtkEntryPasswordText, text);
}

/**
 *
 */
void gtkEntryPasswordTextSetEditable(gboolean editable)
{
	GtkEntry * gtkEntryPasswordText = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_Password_Text"));
	gtkWidgetSetEditable((GtkWidget *) gtkEntryPasswordText, editable);
}

/**
 * Clears gtkEntry_Password_Text
 */
void gtkEntryPasswordTextClear(void)
{
	gtkEntryPasswordTextSet("");
}

/**
 * Initiates gtkEntry_Password_Text
 */
void gtkEntryPasswordTextInit(void)
{
	gtkEntryPasswordTextClear();
	gtkEntryPasswordTextSetEditable(true);
}

/**
 * Copies gtkEntry_Password_Text to the clipboard
 */
char * gtkEntryPasswordTextCopy(void)
{
	GtkEntry * gtkEntryPasswordText = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_Password_Text"));
	gtk_clipboard_set_text (getClipboard(),
	                        gtk_entry_get_text(gtkEntryPasswordText),
	                        strlen((gchar *) gtk_entry_get_text(gtkEntryPasswordText)));
	return (char *)gtk_entry_get_text(gtkEntryPasswordText);
}

