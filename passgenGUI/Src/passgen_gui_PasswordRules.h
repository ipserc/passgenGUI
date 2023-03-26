/*
 * passgen_gui_PasswordRules.h
 *
 *  Created on: 21 feb. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_GUI_PASSWORDRULES_H_
#define SRC_PASSGEN_GUI_PASSWORDRULES_H_

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
#include "passgen_config.h"
#include "passgen_glade.h"
#include "passgen_gui_PasswordLength.h"
#include "passgen_status.h"

extern char status[];
//extern void printStatus(enum STATUS_LEVEL level, const char * fmtstr,...);

/* PROTOTYPES */
/* passgen_gui_PasswordRules.c */
void gtkEntryPasswordRulesSetEditable(char *gtkEntryName, gboolean editable);
void gtkEntryPasswordRulesInit(char *gtkEntryName, int val, _Bool chkBox);
gboolean gtkCheckButtonPasswordRulesGetActive(char *gtkCheckButtonName);
void gtkCheckButtonPasswordRulesSetActive(char *gtkCheckButtonName);
void gtkCheckButtonPasswordRulesToggled(char *gtkCheckButtonName, char *gtkEntryName);
void gtkCheckButtonPasswordRulesInit(char *gtkCheckButtonName, _Bool chkBox);
gboolean gtkCheckButtonPasswordRulesLast(int checkButtonSet);
void gtkEntryPasswordRulesSetNumberSetEditable(gboolean editable);
void gtkEntryPasswordRulesSetNumberInit(void);
int gtkEntryPasswordRulesSetNumberGetVal(void);
gboolean gtkCheckButtonPasswordRulesSetNumberGetActive(void);
void gtkCheckButtonPasswordRulesSetNumberToggled(void);
void gtkCheckButtonPasswordRulesSetNumberInit(void);
void gtkEntryPasswordRulesSetSymbolSetEditable(gboolean editable);
void gtkEntryPasswordRulesSetSymbolInit(void);
int gtkEntryPasswordRulesSetSymbolGetVal(void);
gboolean gtkCheckButtonPasswordRulesSetSymbolGetActive(void);
void gtkCheckButtonPasswordRulesSetSymbolToggled(void);
void gtkCheckButtonPasswordRulesSetSymbolInit(void);
void gtkEntryPasswordRulesSetLowerSetEditable(gboolean editable);
void gtkEntryPasswordRulesSetLowerInit(void);
int gtkEntryPasswordRulesSetLowerGetVal(void);
gboolean gtkCheckButtonPasswordRulesSetLowerGetActive(void);
void gtkCheckButtonPasswordRulesSetLowerToggled(void);
void gtkCheckButtonPasswordRulesSetLowerInit(void);
void gtkEntryPasswordRulesSetUpperSetEditable(gboolean editable);
void gtkEntryPasswordRulesSetUpperInit(void);
int gtkEntryPasswordRulesSetUpperGetVal(void);
gboolean gtkCheckButtonPasswordRulesSetUpperGetActive(void);
void gtkCheckButtonPasswordRulesSetUpperToggled(void);
void gtkCheckButtonPasswordRulesSetUpperInit(void);
int gtkSumEntryPasswordRules(void);
int gtkGetActiveEntryPasswordRuleValue(int charSetGroup);
int gtkSumActiveEntryPasswordRules(void);
int gtkSumRestActiveEntryPasswordRules(int charSetGroup);

#endif /* SRC_PASSGEN_GUI_PASSWORDRULES_H_ */
