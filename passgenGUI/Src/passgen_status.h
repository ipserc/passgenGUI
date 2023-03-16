/*
 * passgen_Status.h
 *
 *  Created on: 8 mar. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_STATUS_H_
#define SRC_PASSGEN_STATUS_H_

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

// Interface used type
enum USER_INTERFACE
{
	CLI,
	GUI
};

// Status Level
enum STATUS_LEVEL
{
	BASIC		,	// Log Status Messages BASIC output level. Default output level. This Log Status Messages is shown always
	NORMAL		,	// Log Status Messages NORMAL output level. Slightly detailed information is displayed
	HIGH		,	// Log Status Messages HIGH output level. Detailed information is displayed
	LAST_STATUS
};

extern enum STATUS_LEVEL statusLevel;
extern enum USER_INTERFACE userInterface;
extern char status[];

extern void gtkTextViewStatusAppend(void);

/* PROTOTYPES */
/* passgen_status.c */
void printStatus(enum STATUS_LEVEL level, const char *fmtstr, ...);
int getStatusIdFromName(const char * inStatusName);
char * getStatusNameFromId(enum STATUS_LEVEL status);
char * getCurrentStatusName(void);


#endif /* SRC_PASSGEN_STATUS_H_ */
