/*
 * passgen_gui.h
 *
 *  Created on: 13 feb. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_GUI_H_
#define SRC_PASSGEN_GUI_H_

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
#include <math.h>

#include "passgen_errtra.h"
#include "passgen_config.h"
#include "passgen_glade.h"
#include "passgen_gui_AboutDialog.h"
#include "passgen_gui_PasswordLength.h"
#include "passgen_gui_PasswordRules.h"
#include "passgen_gui_Password.h"
#include "passgen_gui_MenuBar.h"

extern int PASS_LEN;
extern char *passgenConf2Rules(void);
extern char *genPass(char *passContainer);
extern void gtkTextViewStatusClear(void);
extern bool checkPasswordRules(void);
extern bool checkGrpChrLimit(int charGroup, int value);
extern char * decodeGroupType(int charGroup);
extern void setPassgenConfCaseRule2Values(void);
extern void initGrpChrLimit(void);
extern void initExcludedGroups(void);
extern void traceGrpChrExcluded(void);
extern void printExcludedGroups(void);

#define NORMAL_CURSOR GDK_LEFT_PTR

typedef struct
{
	char signal[30];
}
user_data_t;

/* PROTOTYPES */
/* passgen_gui.c */
GtkBuilder *setGtkBuilder(void);
GtkBuilder *getGtkBuilder(void);
GtkClipboard *setClipboard(void);
GtkClipboard *getClipboard(void);
user_data_t *gtkUserData(void);
void catchSigterm(void);
void gtkSetCursor(GdkCursorType cursorType);
void gtkWarning(const char *fmtstr, ...);
void gtkClosePassgen(void);
void gtkPassgenFileQuit(GtkImageMenuItem *fileQuit, gpointer user_data);
void gtkWidgetSetEditable(GtkWidget *gtkWidget, gboolean editable);
void passgenGtkSettings2PassgenConf(void);
void gtkPasswordGenerate(void);
gboolean _gtkCheckPasswordRules(void);
gboolean gtkCheckPasswordRules(void);
gboolean gtkCheckGrpChrLimit(int charSetGroup, int value);
void passgenConfRulesValuesSet(void);
gboolean gtkCheckRules(void);
void gtkInitPassgen(void);
void gtkSignalsConnect(void);


#endif /* SRC_PASSGEN_GUI_H_ */
