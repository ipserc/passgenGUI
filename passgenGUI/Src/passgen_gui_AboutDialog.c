/*
 * passgen_gui_AboutDialog.c
 *
 *  Created on: 15 mar. 2023
 *      Author: ipserc
 */

#include "passgen_gui_AboutDialog.h"

/**
 * Presents the gtkAboutDialog_passgen
 */
void gtkMenuItemHelpAboutShow(void)
{
	GtkAboutDialog * gtkAboutDialogPassgen = GTK_ABOUT_DIALOG(gtk_builder_get_object(getGtkBuilder(), "gtkAboutDialog_passgen"));
	gtk_window_present((GtkWindow *) gtkAboutDialogPassgen);
}

/**
 * Hides the gtkAboutDialog_passgen
 */
void gtkMenuItemHelpAboutHide(void)
{
	GtkAboutDialog * gtkAboutDialogPassgen = GTK_ABOUT_DIALOG(gtk_builder_get_object(getGtkBuilder(), "gtkAboutDialog_passgen"));
	gtk_window_close((GtkWindow *) gtkAboutDialogPassgen);

}
