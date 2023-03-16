/*
 * passgen_gui_AboutDialog.c
 *
 *  Created on: 15 mar. 2023
 *      Author: ipserc
 */

#include "passgen_gui_AboutDialog.h"

/**
 *
 */
void gtkMenuItemHelpAboutShow(void)
{
	GtkDialog * gtkDialogPassgen = GTK_DIALOG(gtk_builder_get_object(getGtkBuilder(), "gtkDialog_passgen"));
	GtkAboutDialog * gtkAboutDialogPassgen = GTK_ABOUT_DIALOG(gtk_builder_get_object(getGtkBuilder(), "gtkAboutDialog_passgen"));
	gtk_window_present((GtkWindow *) gtkAboutDialogPassgen);
}

/**
 *
 */
void gtkMenuItemHelpAboutHide(void)
{
	GtkAboutDialog * gtkAboutDialogPassgen = GTK_ABOUT_DIALOG(gtk_builder_get_object(getGtkBuilder(), "gtkAboutDialog_passgen"));
	gtk_window_close((GtkWindow *) gtkAboutDialogPassgen);

}
