/*
 * passgen_config.h
 *
 *  Created on: 13 feb. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_CONFIG_H_
#define SRC_PASSGEN_CONFIG_H_

#include <gtk/gtk.h>

#include <stdio.h>
#include <libconfig.h>
#include <sys/stat.h>
#include <stdbool.h>

#include <asm-generic/errno-base.h>
#include <bits/types/FILE.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


#include "passgen_errtra.h"
#include "passgen_gui.h"

#define PGNHOMELEN 	320
#define PGNDIR		".passgen"
#define PGNFILENAME "passgen.conf"
#define PGNAPPNAME 	"passgen"

typedef struct
{
	char preset[15];
	int size;
	int user;
}
passwordLength_t;

typedef struct
{
	bool chkBox;
	int val;
}
passwordRule_t;

typedef enum
{
	USER_SIZE = 17,
	PIN_SIZE = 4,
	MEDIUM_SIZE = 8,
	LONG_SIZE = 16,
	ULTRA_SIZE = 32,
	PARANOIC_SIZE = 64
}
passwordLength_sizes;

typedef enum
{
	USER,
	PIN,
	MEDIUM,
	LONG,
	ULTRA,
	PARANOIC,
	LAST_PRESET
}
preset_idx;

typedef enum
{
	UPPER,
	LOWER,
	NUMBER,
	SYMBOL,
	LAST_SET
}
characterSets_t;

/**
 * PassgenConf structure
 */
typedef struct
{
	char appName[256];
	passwordLength_t passwordLength;
	passwordRule_t upperCaseRule;
	passwordRule_t lowerCaseRule;
	passwordRule_t symbolCaseRule;
	passwordRule_t numberCaseRule;
}
passgenConf_t;

/**
 * PassgenConf Items enumerator
 */
typedef enum passgenConfItems
{
	passwordLengthPreset,
	passwordLengthSize,
	passwordLengthUser,
	upperCaseRuleChkBox,
	upperCaseRuleSize,
	lowerCaseRuleChkBox,
	lowerCaseRuleSize,
	numberCaseRuleChkBox,
	numberCaseRuleSize,
	symbolCaseRuleChkBox,
	symbolCaseRuleSize
}
passgenConfItems_t;

/* PROTOTYPE */
/* passgen_config.c */
char *getPasswordLengthPresetsName(int idx);
int getPasswordLengthPresetsNameIdx(char *name);
int getPasswordLengthPresetsSize(int idx);
passgenConf_t *setPassgenConf(void);
passgenConf_t *getPassgenConf(void);
char *strToUpper(char *str);
char *strToLower(char *str);
_Bool strBool2Bool(char *strBool);
char *bool2StrBool(_Bool boolVal);
char *passGenConfigStreamFile(void);
_Bool writePassgenConfig(char *passgenHome);
void setupPassgenConfigStructDefaultValues(passgenConf_t *ptPassgenConf);
void createPassgenConf(char *pgnHome, passgenConf_t *ptPassgenConf);
_Bool configLoad(char *pgnHome, passgenConf_t *ptPassgenConf);
void printPassgenConfig(void);
char *passgenPath(passgenConf_t *ptPassgenConf);
void passgenConfigRead(passgenConf_t *ptPassgenConf);
void *lookupPassgenConfig(passgenConfItems_t passgenConfItem);
int passwordLengthPresetNameSize(char *name);
int passwordLengthPresetIdSize(preset_idx id);
_Bool isUSER(char *name);

#endif /* SRC_PASSGEN_CONFIG_H_ */
