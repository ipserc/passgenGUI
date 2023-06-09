/*
 * passgen_gui_Status.c
 *
 *  Created on: 7 mar. 2023
 *      Author: ipserc
 */

#include "passgen_gui_Status.h"

/* ***********************************************************
 * gtkTextView_Status
 *********************************************************** */

/**
 * Appends a new line into gtkTextView_Status control
 * @param text The ew line text
 */
void gtkTextViewStatusAppendText(char * text)
{
	GtkTextView * gtkTextViewStatus = GTK_TEXT_VIEW(gtk_builder_get_object(getGtkBuilder(), "gtkTextView_Status"));
	GtkTextBuffer * gtkTextViewStatusBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkTextViewStatus));
	GtkTextIter iter;

	gtk_text_buffer_get_end_iter(gtkTextViewStatusBuffer, &iter);
	gtk_text_buffer_insert(gtkTextViewStatusBuffer, &iter, text, -1);

	gtk_text_buffer_get_end_iter(gtkTextViewStatusBuffer, &iter);
	gtk_text_buffer_insert(gtkTextViewStatusBuffer, &iter, "\n", -1);
}

/**
 * Shortcut to gtkTextViewStatusAppendText for using the global variable status
 */
void gtkTextViewStatusAppend(void)
{
	gtkTextViewStatusAppendText(status);
}

/**
 * Clears the gtkTextView_Status
 */
void gtkTextViewStatusClear(void)
{
	GtkTextView * gtkTextViewStatus = GTK_TEXT_VIEW(gtk_builder_get_object(getGtkBuilder(), "gtkTextView_Status"));
	GtkTextBuffer * gtkTextViewStatusBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtkTextViewStatus));
	GtkTextIter start, end;

    gtk_text_buffer_get_start_iter(gtkTextViewStatusBuffer, &start);
    gtk_text_buffer_get_end_iter(gtkTextViewStatusBuffer, &end);
    gtk_text_buffer_delete(gtkTextViewStatusBuffer, &start, &end);

    gtk_text_view_set_buffer(gtkTextViewStatus, gtkTextViewStatusBuffer);
}

/**
 * Initializes the gtkTextView_Status
 */
void gtkTextViewStatusInit(void)
{
	gtkTextViewStatusClear();
}
