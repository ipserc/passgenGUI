/*
 * passgen_gui_Status.h
 *
 *  Created on: 7 mar. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_GUI_STATUS_H_
#define SRC_PASSGEN_GUI_STATUS_H_

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

extern char status[];

/* PROTOTYPES */
/* passgen_gui_Status.c */
void gtkTextViewStatusAppendText(char *text);
void gtkTextViewStatusAppend(void);
void gtkTextViewStatusClear(void);
void gtkTextViewStatusInit(void);

#endif /* SRC_PASSGEN_GUI_STATUS_H_ */
