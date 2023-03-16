/*
 * passgen_gui_PasswordLength.h
 *
 *  Created on: 21 feb. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_GUI_PASSWORDLENGTH_H_
#define SRC_PASSGEN_GUI_PASSWORDLENGTH_H_

#include <gtk/gtkx.h>
#include <gtk/gtk.h>
#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <libgen.h>
#include <signal.h>

#include "passgen_errtra.h"
#include "passgen_glade.h"
#include "passgen_config.h"

/* PROTYPES */
/* passgen_gui_PasswordLength.c */
void ptrTest(void);
int gtkEntryPasswordLengthSizeGet(void);
void gtkEntryPasswordLengthSizeEditable(gboolean editable);
void gtkEntryPasswordLengthSizeUpdate(const gchar *value);
void gtkEntryPasswordLengthInit(void);
void gtkComboBoxTextPasswordLengthPresetChanged(void);
void gtkComboBoxTextPasswordLengthPresetInit(void);


#endif /* SRC_PASSGEN_GUI_PASSWORDLENGTH_H_ */
