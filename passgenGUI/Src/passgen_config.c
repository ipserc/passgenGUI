/*
 * passgen_config.c
 *
 *  Created on: 13 feb. 2023
 *      Author: ipserc
 */

#include "passgen_config.h"

#define __DEBUG__ false

/**
 * Array with the names of the password preset length
 */
char passwordLengthPresetsNames[LAST_PRESET][10] = {"USER", "PIN", "MEDIUM", "LONG", "ULTRA", "PARANOIC"};

/**
 * Returns the name of the password preset length corresponding with the idx
 * @param idx The id of the password preset length
 * @return The name of the password preset length passed in idx
 */
char * getPasswordLengthPresetsName(int idx)
{
	return passwordLengthPresetsNames[idx];
}

/**
 * Return the id of the preset name passed
 * @param name The preset name passed
 * @return The index in the list corresponding with the name passed if found, otherwise -1
 */
int getPasswordLengthPresetsNameIdx(char * name)
{
	for(int presetNameIdx = 0; presetNameIdx < LAST_PRESET; ++presetNameIdx)
	{
		if (!strcmp(name, passwordLengthPresetsNames[presetNameIdx])) return presetNameIdx;
	}
	return -1;
}

/**
 * Array with the password preset lengths
 * USER is assigned to 1 but the length is arbitrary
 */
int  passwordLengthPresetsSizes[LAST_PRESET] = {1, 4, 8, 16, 32, 64};

/**
 * Returns the the password preset length of the idx passed
 * @param idx The idx of the password preset length
 * @return The length of the password preset passed in idx
 */
int getPasswordLengthPresetsSize(int idx)
{
	if (idx == USER) return getPasswordLengthPresetsSize(USER);
	return passwordLengthPresetsSizes[idx];
}

/**
 * Static "private method" to set or get the the passgenConf_t * passgenConf "member" variable. DO NOT CALL IT DIRECTLY
 * @param method: Selector for (0) create a new instance or returning the one created
 * @return static passgenConf_t * passgenConf
 */
static passgenConf_t * passgenConf(int method)
{
	static passgenConf_t passgenConf;

	if (method == 0) //SET
	{
		passgenConfigRead(&passgenConf);

	}
	return &passgenConf;
}

/**
 * Sets passgenConf_t * passgenConf pointer to the static variable. Use it to create it
 * @return static passgenConf_t * passgenConf
 */
passgenConf_t * setPassgenConf()
{
	return (passgenConf_t *)passgenConf(0);
}

/**
 * Returns the passgenConf_t * passgenConf static variable
 * @return static passgenConf_t * passgenConf
 */
passgenConf_t * getPassgenConf()
{
	return (passgenConf_t *)passgenConf(1);
}

/**
 * Overwrites the String with the letter in Capital
 * @param str The string to transform to uppercase
 * @return The string transformed to uppercase
 */
char * strToUpper(char * str)
{
	char * ptr = str;

	for(int i = 0; i < strlen(str); ++i, ++ptr)
	{
		if (*ptr > 96 && *ptr < 123) *ptr = *ptr - 32;
	}

	return str;
}

/**
 * O* Overwrites the String with lowercase letters
 * @param str The string to transform to lowercase
 * @return The string transformed to lowercase
 */
char *  strToLower(char * str)
{
	char * ptr = str;

	for(int i = 0; i < strlen(str); ++i, ++ptr)
	{
		if (*ptr > 64 && *ptr < 91) *ptr = *ptr + 32;
	}

	return str;
}

/**
 * Interprets the text True or False and returns its boolean value
 * @param strBool The string of the boolean value True or False
 * @return true, false or -1 in case the strBool wasn't be a boolean valid name
 */
bool strBool2Bool(char * strBool)
{
	bool boolVal;
	char cadena[6];
	strcpy(cadena, strBool);
	strToUpper(cadena);
	if (!strcmp("TRUE", cadena)) boolVal = true;
	else if (!strcmp("FALSE", cadena)) boolVal = false;
	else boolVal = -1;
	return boolVal;
}

/**
 * Interprets the text True or False and returns its boolean value
 * @param boolVal The string of the boolean value True or False
 * @return true, false or -1 in case the strBool wasn't be a boolean valid name
 */
char *  bool2StrBool(bool boolVal)
{
	return boolVal ? "True" : "False";
}

/**
 * Returns a string with the updated config file
 */
char * passGenConfigStreamFile(void)
{
	int errnum;
	passgenConf_t * ptPassgenConf = getPassgenConf();
	char * passGenConfigFile;
	int passGenConfigFileSize = 3001; // 3 kB

	if (!(passGenConfigFile = (char *) malloc(passGenConfigFileSize))) {
		errnum = errno;
		ERROR("Error Allocating memory for passGenConfigFileSize: (%i) - %s\n", errnum, strerror(errnum));
		exit(errnum);
	}

	char * ptr = passGenConfigFile;

	ptr += sprintf(ptr, "# ######################\n");
	ptr += sprintf(ptr, "#\n");
	ptr += sprintf(ptr, "# Passgen config file\n");
	ptr += sprintf(ptr, "#\n");
	ptr += sprintf(ptr, "# ######################\n\n");
	ptr += sprintf(ptr, "# -----------------------\n");
	ptr += sprintf(ptr, "# Password Length section\n");
	ptr += sprintf(ptr, "# -----------------------\n");
	ptr += sprintf(ptr, "passwordLength:\n");
	ptr += sprintf(ptr, "{\n");
	ptr += sprintf(ptr, "	preset = \"%s\";\n", ptPassgenConf->passwordLength.preset);
	ptr += sprintf(ptr, "	size = %d;\n", ptPassgenConf->passwordLength.size);
	ptr += sprintf(ptr, "	user = %d;\n", ptPassgenConf->passwordLength.user);
	ptr += sprintf(ptr, "};\n\n");
	ptr += sprintf(ptr, "# ----------------------\n");
	ptr += sprintf(ptr, "# Password Rules section\n");
	ptr += sprintf(ptr, "# ----------------------\n");
	ptr += sprintf(ptr, "passwordRules:\n");
	ptr += sprintf(ptr, "{\n");
	ptr += sprintf(ptr, "	upperCaseChk = %s;\n", bool2StrBool(ptPassgenConf->upperCaseRule.chkBox));
	ptr += sprintf(ptr, "	upperCaseVal = %d;\n", ptPassgenConf->upperCaseRule.val);
	ptr += sprintf(ptr, "	lowerCaseChk = %s;\n", bool2StrBool(ptPassgenConf->lowerCaseRule.chkBox));
	ptr += sprintf(ptr, "	lowerCaseVal = %d;\n", ptPassgenConf->lowerCaseRule.val);
	ptr += sprintf(ptr, "	symbolCaseChk = %s;\n", bool2StrBool(ptPassgenConf->symbolCaseRule.chkBox));
	ptr += sprintf(ptr, "	symbolCaseVal = %d;\n", ptPassgenConf->symbolCaseRule.val);
	ptr += sprintf(ptr, "	numberCaseChk = %s;\n", bool2StrBool(ptPassgenConf->numberCaseRule.chkBox));
	ptr += sprintf(ptr, "	numberCaseVal = %d;\n", ptPassgenConf->numberCaseRule.val);
	ptr += sprintf(ptr, "};\n");

	return passGenConfigFile;
}

/**
 * Writes passGen Configuration kept in ptPassgenConf to zhavam.conf
 * @param passgenHome Tpath to the passgen home
 * @return True if the config has been written, otherwise false
 */
bool writePassgenConfig(char * passgenHome)
{
	if (__DEBUG__) TRACE("Start writePassgenConfig(%s)", passgenHome);

	FILE * fp;
	char * passgenConfigStreamFile = passGenConfigStreamFile();
	int errnum;
	bool writeOk = true;

	if (__DEBUG__) TRACE("passgenHome: %s", passgenHome);

	if ((fp = fopen(passgenHome, "w")))
	{
		if (fprintf(fp, "%s", passgenConfigStreamFile) < 0)
		{
			errnum = errno;
			printStatus(BASIC, "ERROR - Failed to save configuration file to disk. Check the space that is available");
			printStatus(NORMAL, "ERROR: %d -  %s", errnum, strerror(errnum));
			writeOk = false;
		}
		if (fclose(fp))
		{
			errnum = errno;
			printStatus(BASIC, "ERROR - Failed closing configuration file: %s", passgenHome);
			printStatus(NORMAL, "ERROR: %d -  %s", errnum, strerror(errnum));
			writeOk = false;
		}
	}
	else {
		errnum = errno;
		if (__DEBUG__) TRACE("fp: %p", fp);
		printStatus(BASIC, "ERROR - Failed opening for writing the configuration file: %s", passgenHome);
		printStatus(NORMAL, "ERROR: %d - %s", errno, strerror(errno));
		writeOk = false;
	}

	free(passgenConfigStreamFile);

	if (__DEBUG__) TRACE("End writePassgenConfig(%s) %s", passgenHome, writeOk ? "Success" : "Fail");

	return writeOk;
}

/**
 * Sets up Passgen ConfigStruct to the default values
 * @param ptPassgenConf
 */
void setupPassgenConfigStructDefaultValues(passgenConf_t * ptPassgenConf)
{
	strcpy(ptPassgenConf->passwordLength.preset, passwordLengthPresetsNames[LONG]);
	ptPassgenConf->passwordLength.size = passwordLengthPresetsSizes[LONG];
	ptPassgenConf->passwordLength.user = 17;
	ptPassgenConf->upperCaseRule.chkBox = true;
	ptPassgenConf->upperCaseRule.val = 3;
	ptPassgenConf->lowerCaseRule.chkBox = true;
	ptPassgenConf->lowerCaseRule.val = 3;
	ptPassgenConf->numberCaseRule.chkBox = true;
	ptPassgenConf->numberCaseRule.val = 3;
	ptPassgenConf->symbolCaseRule.chkBox = true;
	ptPassgenConf->symbolCaseRule.val = 2;
}

/**
 * Creates the file passgen.conf from scratch
 * first: set up the default values for passgen
 * second: writes these values in a new passgen.conf file
 * @param pgnHome
 * @param ptPassgenConf
 */
void createPassgenConf(char * pgnHome, passgenConf_t * ptPassgenConf)
{
	if (__DEBUG__) TRACE("Start createPassgenConf", "");

	printStatus(BASIC, "%s", "passgen config file does not exist. Creating a new one from scratch with default values");
	setupPassgenConfigStructDefaultValues(ptPassgenConf);
	writePassgenConfig(pgnHome);

	if (__DEBUG__) TRACE("End createPassgenConf", "");

}

/**
 * Loads the configuration from passgen.conf
 * @param pgnHome
 * @param ptPassgenConf
 * @return true if SUCCESS otherwise false
 */
bool configLoad(char * pgnHome, passgenConf_t * ptPassgenConf)
{
	if (__DEBUG__) TRACE("Start configLoad(%s, passgenConf_t * ptPassgenConf)", pgnHome);

	const char * ptr ;
	config_t cfg;

	if (__DEBUG__) TRACE("pgnHome: %s", pgnHome);

	config_init(&cfg);

	/* Read the file. If there is an error, report it and exit. */
	if (!config_read_file(&cfg, pgnHome))
	{
		sprintf(STATUS_MESSAGE, "%s file:%s line:%d error:%s", WARNING02, config_error_file(&cfg),
				config_error_line(&cfg), config_error_text(&cfg));
		config_destroy(&cfg);
		ERROR("%s", STATUS_MESSAGE);
		return false;
	}

	ptr = ptPassgenConf->passwordLength.preset; // I need to use this trick to make config_lookup_string works
	config_lookup_string(&cfg, "passwordLength.preset", (const char **)&(ptr));
	sprintf(ptPassgenConf->passwordLength.preset, "%s", ptr);
	// All the rest are loaded normally
	config_lookup_int(&cfg, "passwordLength.size", (int *)&(ptPassgenConf->passwordLength.size));
	config_lookup_int(&cfg, "passwordLength.user", (int *)&(ptPassgenConf->passwordLength.user));
	config_lookup_bool(&cfg, "passwordRules.upperCaseChk", (int *)&(ptPassgenConf->upperCaseRule.chkBox));
	config_lookup_int(&cfg, "passwordRules.upperCaseVal", (int *)&(ptPassgenConf->upperCaseRule.val));
	config_lookup_bool(&cfg, "passwordRules.lowerCaseChk", (int *)&(ptPassgenConf->lowerCaseRule.chkBox));
	config_lookup_int(&cfg, "passwordRules.lowerCaseVal", (int *)&(ptPassgenConf->lowerCaseRule.val));
	config_lookup_bool(&cfg, "passwordRules.symbolCaseChk", (int *)&(ptPassgenConf->symbolCaseRule.chkBox));
	config_lookup_int(&cfg, "passwordRules.symbolCaseVal", (int *)&(ptPassgenConf->symbolCaseRule.val));
	config_lookup_bool(&cfg, "passwordRules.numberCaseChk", (int *)&(ptPassgenConf->numberCaseRule.chkBox));
	config_lookup_int(&cfg, "passwordRules.numberCaseVal", (int *)&(ptPassgenConf->numberCaseRule.val));

	if (__DEBUG__)
	{
		TRACE("ptr: %s", ptr);
		TRACE("ptPassgenConf->passwordLength.preset: %s", ptPassgenConf->passwordLength.preset);
		TRACE("ptPassgenConf->passwordLength.size: %d", ptPassgenConf->passwordLength.size);
		TRACE("ptPassgenConf->passwordLength.user: %d", ptPassgenConf->passwordLength.user);
		TRACE("ptPassgenConf->upperCaseRule.chkBox: %s", ptPassgenConf->upperCaseRule.chkBox ? "On" : "Off");
		TRACE("ptPassgenConf->lowerCaseRule.chkBox: %s", ptPassgenConf->lowerCaseRule.chkBox ? "On" : "Off");
		TRACE("ptPassgenConf->symbolCaseRule.chkBox: %s", ptPassgenConf->symbolCaseRule.chkBox ? "On" : "Off");
		TRACE("ptPassgenConf->numberCaseRule.chkBox: %s", ptPassgenConf->numberCaseRule.chkBox ? "On" : "Off");
	}

	if (__DEBUG__) TRACE("End configLoad(): %s", "Success");
	return true;
}

/**
 * Prints through the std output the content of the passgen config file
 */
void printPassgenConfig(void)
{
	char * passgenConfigStreamFile = passGenConfigStreamFile();
	printf("%s", passgenConfigStreamFile);
	free(passgenConfigStreamFile);
}

/**
 * Returns the passgen config path
 * If the passgen config file is not found, it creates a new one with the default settings
 * @param ptPassgenConf Pointer to the passgenConf_t global variable with the information of the settings
 * @return The path to the config file
 */
char * passgenPath(passgenConf_t * ptPassgenConf)
{
	struct stat s;
	char home[PGNHOMELEN] = "";
	char * pgnHome;

	if (!(pgnHome = malloc(PGNHOMELEN)))
	{
		int errnum = errno;
		ERROR("Error Allocating memory for passgenPath: (%i) - %s\n", errnum, strerror(errnum));
		exit(errnum);
	}

	//setupPassgenConfigStructDefaultValues(ptPassgenConf);

	sprintf(home, "%s", getenv("HOME"));

	if (__DEBUG__) TRACE("Home:%s", home);

	sprintf(pgnHome, "%.*s/%.*s", (int)strlen(home), home, (int)strlen(PGNDIR), PGNDIR);

	if (__DEBUG__)
	{
		TRACE("pgnHome (1): %s", pgnHome);
	}

	if (stat(pgnHome, &s) == -1) {
		statErrorMngr(errno);
	    if (errno == ENOENT) // does not exist
	    {
	    	if (mkdir(pgnHome, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH) == -1) mkdirErrorMngr(errno);
	    	sprintf(pgnHome, "%.*s/%.*s", (int)strlen(pgnHome), pgnHome, (int)strlen(PGNFILENAME), PGNFILENAME);

	    	if (__DEBUG__)
	    	{
	    		TRACE("pgnHome (does not exist - createPassgenConf(pgnHome, ptPassgenConf)): %s", pgnHome);
	    	}

	    	createPassgenConf(pgnHome, ptPassgenConf);
	    }
	} else if (!S_ISDIR(s.st_mode)) ERROR(ERROR01, pgnHome); // exists but it is not a dir

	sprintf(pgnHome, "%.*s/%.*s", (int)strlen(pgnHome), pgnHome, (int)strlen(PGNFILENAME), PGNFILENAME);

	if (__DEBUG__)
	{
		TRACE("pgnHome (EXISTS): %s", pgnHome);
	}

	return (char *)pgnHome;
}


/**
 * Try to read the config file passgen.conf
 * If this file doesn't exist calls createPassgenConf with the full path to create the file
 * If the file exists loads its content
 * @param ptPassgenConf Pointer to the passgenConf_t global variable with the information of the settings
 */
void passgenConfigRead(passgenConf_t * ptPassgenConf)
{
	char pgnHome[PGNHOMELEN] = "";
	sprintf(pgnHome, "%s", passgenPath(ptPassgenConf));

	if (__DEBUG__) TRACE("pgnHome: %s", pgnHome);

	// Setup PassgenConfigStruct with the default values
	setupPassgenConfigStructDefaultValues(ptPassgenConf);
	// Setup PassgenConfigStruct with the .passgen/passgen.conf stored values
	configLoad(pgnHome, ptPassgenConf);

}

/**
 * Looks up for a specific field of passgenConf_t structure
 * @param passgenConfItem the item of the passgenConf_t that wants to get
 * @return The value of the passgenConfItem
 */
void * lookupPassgenConfig(passgenConfItems_t passgenConfItem)
{
	passgenConf_t * passgenConf =  getPassgenConf();

	switch (passgenConfItem)
	{
	case passwordLengthPreset:
		return passgenConf->passwordLength.preset;
	case passwordLengthSize:
		if (__DEBUG__) TRACE("passgenConf->passwordLength.size: %d", passgenConf->passwordLength.size);
		return &(passgenConf->passwordLength.size);
	case passwordLengthUser:
		return &(passgenConf->passwordLength.user);
	case upperCaseRuleChkBox:
		return &(passgenConf->upperCaseRule.chkBox);
	case upperCaseRuleSize:
		return &(passgenConf->upperCaseRule.val);
	case lowerCaseRuleChkBox:
		return &(passgenConf->lowerCaseRule.chkBox);
	case lowerCaseRuleSize:
		return &(passgenConf->lowerCaseRule.val);
	case numberCaseRuleChkBox:
		return &(passgenConf->numberCaseRule.chkBox);
	case numberCaseRuleSize:
		return &(passgenConf->numberCaseRule.val);
	case symbolCaseRuleChkBox:
		return &(passgenConf->symbolCaseRule.chkBox);
	case symbolCaseRuleSize:
		return &(passgenConf->symbolCaseRule.val);
	}

	if (__DEBUG__) TRACE("lookupPassgenConfig: %d Not found", passgenConfItem);
	return (void *)NULL;
}

/**
 * Returns the length of the password preset from its name
 * @param name The preset name passed
 * @return The length of the password
 */
int passwordLengthPresetNameSize(char * name)
{
	int id = getPasswordLengthPresetsNameIdx(name);
	return passwordLengthPresetIdSize(id);
}

/**
 * Returns the length of the password preset from its id
 * @param id The preset id passed from 0 to 5 	USER, PIN, MEDIUM, LONG, ULTRA, PARANOIC
 * @return The length of the password
 */
int passwordLengthPresetIdSize(preset_idx id)
{
	switch (id)
	{
	case USER:
		return (int) * (int *)lookupPassgenConfig(passwordLengthUser);
	case PIN:
		return PIN_SIZE;
	case MEDIUM:
		return MEDIUM_SIZE;
	case LONG:
		return LONG_SIZE;
	case ULTRA:
		return ULTRA_SIZE;
	case PARANOIC:
		return PARANOIC_SIZE;
	}
	return -1;
}

/**
 * Check if name passed is the one of  USER
 * Returns True if name passed is the USER, otherwise False
 */
bool isUSER(char * name)
{
	if (!strcmp(name, passwordLengthPresetsNames[USER])) return true;
	return false;
}
