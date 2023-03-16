/*
 * passgen_gui_MenuBar.h
 *
 *  Created on: 12 mar. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_GUI_MENUBAR_H_
#define SRC_PASSGEN_GUI_MENUBAR_H_

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

#include "passgen_config.h"
#include "passgen_gui_Status.h"
#include "passgen_gui.h"

extern char *genpassProgramName(void);

/* PROTOTYPES */
/* passgen_gui_MenuBar.c */
void gtkMenuItemFileLoadActivate(void);
void gtkMenuItemFileSaveActivate(void);
void gtkMenuItemStatusLevelSetLabel(int level);
void gtkMenuItemStatusLevelBasicActivate(void);
void gtkMenuItemStatusLevelNormalActivate(void);
void gtkMenuItemStatusLevelHighActivate(void);
void gtkMenuItemStatusGroupSet(void);


#endif /* SRC_PASSGEN_GUI_MENUBAR_H_ */
