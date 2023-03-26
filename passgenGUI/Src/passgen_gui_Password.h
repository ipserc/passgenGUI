/*
 * passgen_gui_Password.h
 *
 *  Created on: 21 feb. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_GUI_PASSWORD_H_
#define SRC_PASSGEN_GUI_PASSWORD_H_

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

/* PROTOTYPES */
/* passgen_gui_Password.c */
void gtkEntryPasswordTextSet(char *text);
void gtkEntryPasswordTextSetEditable(gboolean editable);
void gtkEntryPasswordTextClear(void);
void gtkEntryPasswordTextInit(void);
char *gtkEntryPasswordTextCopy(void);

#endif /* SRC_PASSGEN_GUI_PASSWORD_H_ */
