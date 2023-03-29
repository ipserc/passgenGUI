/*
 * passgen_Status.c
 *
 *  Created on: 8 mar. 2023
 *      Author: ipserc
 */

#include "passgen_status.h"

#define __DEBUG__ false


char statusLevelName[LAST_STATUS][10] = {"BASIC", "NORMAL", "HIGH"};

/**
* Prints the status on the default output according with the interface in use
 * @param level The level required to display the status
 * @param fmtstr Text to be written using the tags prototype as %[flags][width][.precision][length]specifier
 * @param ... The parameters used by fmtstr
 */
void printStatus(enum STATUS_LEVEL level, const char * fmtstr,...)
{
	if (level > statusLevel) return;

	va_list arglist;

	va_start(arglist, fmtstr);
	vsprintf(status, fmtstr, arglist);
	va_end(arglist);

	if (userInterface == CLI)
	{
		puts(status);
	}
	else
	{
		gtkTextViewStatusAppend();
	}
}

/**
 * Retrieves the status Id from its name
 * @param The statusName "BASIC", "NORMAL", "HIGH"
 * @return The status Id, -1 if statusName is not one of "BASIC", "NORMAL", "HIGH"
 */
int getStatusIdFromName(const char * inStatusName)
{
	int statusId = -1;
	char * statusName = malloc(strlen(inStatusName)+1);
	statusName = strToUpper(statusName);
	if (!strcmp(statusName, "BASIC")) statusId =  BASIC;
	else if (!strcmp(statusName, "NORMAL")) statusId =  NORMAL;
		 else if (!strcmp(statusName, "HIGH")) statusId =  HIGH;
	free(statusName);
	return statusId;
}

/**
 * Gets the status level name from the id
 * @param status The id of the status level
 * @return The status level name
 */
char * getStatusNameFromId(enum STATUS_LEVEL status)
{
	return statusLevelName[status];
}

/**
 * Gets the current status level name
 * @return The current status level name
 */
char * getCurrentStatusName(void)
{
	return getStatusNameFromId(statusLevel);
}

