/*
 * passgen.h
 *
 *  Created on: 11 feb. 2023
 *      Author: ipserc
 */

#ifndef PASSGEN_H_
#define PASSGEN_H_

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
#include <time.h>

#include "randomize.h"

#include "passgen_errtra.h"
#include "passgen_gui_PasswordLength.h"
#include "passgen_gui.h"
#include "passgen_config.h"
#include "passgen_params.h"
#include "passgen_gui_Status.h"
#include "passgen_status.h"

/*
 * Constants (Defines)
 */

#define MEM_FAIL 666

#define SUCCESS true
#define FAIL false

#define UPPER_CASE "QWERTYUIOPASDFGHJKLZXCVBNM"
#define LOWER_CASE "mnbvcxzpoiuytrewqlkjhgfdsa"
#define SYMBL_CASE "@!#$%&/(){}=+-_|*[];:<,.>?"
#define NUMBR_CASE "1357908642"

// Predefined Passwords sizes
#define PIN_SIZE 		4 	// Password of PIN type
#define MEDIUM_SIZE 	8	// Regular Password size
#define LONG_SIZE 		16	// Recommended password size
#define VERY_LONG_SIZE 	32	// Secure password size
#define ULTRA_LONG_SIZE 64  // Paranoic password size

// Should match with passgen_config.h characterSets_t;
// Consider to remove it
enum GROUP_TYPE
{
	NONE_GROUP = -1,
	UPPER_CASE_GROUP,
	LOWER_CASE_GROUP,
	NUMBR_CASE_GROUP,
	SYMBL_CASE_GROUP,
	GROUPS_NBR
};

/*
 * Global Variables. Member variables
 */
int PASS_LEN;
int EXCLUDED_GRPS[GROUPS_NBR-1];
int GRPCHRS_LIMIT[GROUPS_NBR];

// Counters of groupChars
int NBR_SYMBL = 0;
int NBR_UPPER = 0;
int NBR_LOWER = 0;
int NBR_NUMBR = 0;

enum USER_INTERFACE userInterface;
enum STATUS_LEVEL statusLevel;
// status message limited to 299 characters
char status[300] = "";

/* PROTOTYPES */
/* passgen.c */
char *factsString(char *factsString);
void printfacts(void);
char *genpassVersion(void);
char *genpassProgramName(void);
void putsGenpassVersion(void);
char *shuffleCharacterSet(const char *array);
char *boolToString(_Bool value);
void initGrpChrLimit(void);
int sumGrpChrLimit(void);
int getGrpChrLimit(int charGroup);
_Bool isGrpChrExcluded(int charGroup);
void traceGrpChrExcluded(void);
int sumActiveGrpChrLimit(void);
int sumRestActiveGrpChrLimit(int charGroup);
_Bool setGrpChrLimit(int charGroup, int value);
_Bool checkGrpChrLimit(int charGroup, int value);
_Bool checkPasswordRules(void);
void resetCharGroupCounter(void);
char getCharFrom(char *setOfChars);
_Bool hasCharsRequired(int charGroup);
void initExcludedGroups(void);
_Bool appendExcludedGroups(int charGroup);
_Bool inExcludedGroups(int charGroup);
_Bool onlySymbols(void);
void printExcludedGroups(void);
int randomGroupSelector(int nbrItemsGroup);
char *decodeGroupType(int charGroup);
char *genPass(char *passContainer);
void setPassgenConfCaseRule2Values(void);
char *passgenConf2Rules(void);
void passgenGUI(void);
int passgenCCI(void);
int main(int argc, char *argv[]);

#endif /* PASSGEN_H_ */
