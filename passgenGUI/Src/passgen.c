/*
 ============================================================================
 Name        : passgen.c
 Author      : Ipserc
 Version     : see VERSION
 Created     : 9 feb. 2023
 Copyright   : GNU General Public License v3.0
 Description : Password generator based in rules given by the user
 Long Description
	passgen allows you to generate passwords according to certain rules
	that are, a length, a set of characters and number of them.

	The available character sets are uppercase letters, lowercase letters,
	digits 0 through 9, and a set of symbols. Different games can be selected,
	but at least one must be active.

	You can indicate the minimum number of each type of characters that you
	want to use. For symbols this number is exact.

	passgen has a rules checker that informs if the rules that have been
	defined are apt to generate passwords.
 ============================================================================
 */

#include "passgen.h"

//------------------------------------------
//          PROGRAM FACTS SECTION
//------------------------------------------
#define VERSION		"1.0.2 (2023_0329_2215)"
#define AUTHOR		"ipserc"
#define CONTACT 	"https://github.com/ipserc"
#define CREATION	"2023/02/09"
#define COMPILATION	"2023/03/29"
#define PROGRAM		"passgen"
#define MODULE		__FILE__
#define LICENSE		"GNU General Public License v3.0"

#define __DEBUG__ 	false

/**
 * Returns a string with Program - Version - Compilation info
 * @return a string with Program - Version - Compilation info
 */
char * factsString(char * factsString)
{
	sprintf(factsString, "Program:%s - Version:%s - Compilation:%s", PROGRAM, VERSION, COMPILATION);
	return factsString;
}

/**
 * Prints the program facts
 */
void printfacts()
{
	puts("------------------------------------------");
	puts("              PROGRAM FACTS               ");
	puts("------------------------------------------");
	printf("Version......:%s\n", VERSION);
	printf("Author.......:%s\n", AUTHOR);
	printf("Contact......:%s\n", CONTACT);
	printf("Creation Date:%s\n", CREATION);
	printf("Update Date..:%s\n", COMPILATION);
	printf("Program Name.:%s\n", PROGRAM);
	printf("Module Name..:%s\n", MODULE);
	printf("License......:%s\n", LICENSE);
	puts("--------     END PROGRAM FACTS    --------");
}

/**
 * Gets the version of genpass
 */
char * genpassVersion(void)
{
	return VERSION;
}

/**
 * Gets the PROGRAM name of genpass
 */
char * genpassProgramName(void)
{
	return PROGRAM;
}


/**
 * Prints the version of genpass
 */
void putsGenpassVersion(void)
{
	puts(VERSION);
}

//------------------------------------------
//       END OF PROGRAM FACTS SECTION
//------------------------------------------

/**
 * Takes a string with a set of characters and returns a new string with the characters in different order
 * @param array The initial set of characters
 * @return A new string with set of characters in a different order
 */
char * shuffleCharacterSet(const char * array)
{
	int i, j, k;
	char tmp;
	char * newArray = malloc(strlen(array)+1);

	sprintf(newArray, "%s", array);

	if (__DEBUG__)
	{
		TRACE("array_LEN.....: %d", strlen(array));
		TRACE("newArray_LEN..: %d", strlen(array));
		TRACE("array.........: %s", array);
		TRACE("newArray......: %s", newArray);
	}

	for (i = 0; i < 7*strlen(array); ++i)
	{
		do
		{
			j = rand() % strlen(array);
			k = rand() % strlen(array);
		}
		while(j == k);
		tmp = (char)*(newArray+k);
		*(newArray+k) = (char)*(newArray+j);
		*(newArray+j) = tmp;
	}
	*(newArray+strlen(array)) = (char)0;
	if (__DEBUG__) TRACE("FINAL newArray: %s", newArray);

	return newArray;
}

/**
 * Returns the boolean value as a string
 * @param value The boolean to decode
 * @return The boolean value as a string
 */
char * boolToString(bool value)
{
	return value == true ? "TRUE" : "FALSE";
}

/* ************************************************************************
 * GRPCHRS_LIMIT SECTION - PASSWORD RULES
 ************************************************************************ */

/**
 * Initializes at zero the GRPCHRS_LIMIT array for each group of characters
 */
void initGrpChrLimit(void)
{
	for(int charGroup = 0; charGroup < GROUPS_NBR; ++charGroup)
		GRPCHRS_LIMIT[charGroup] = 0;
}

/**
 * Returns the sum of the limits of all characters group from it value given from the GRPCHRS_LIMIT array
 * @return the sum of the limits of all characters group
 */
int sumGrpChrLimit(void)
{
	int sum = 0;
	for(int charGroup = UPPER_CASE_GROUP; charGroup < GROUPS_NBR; ++charGroup)
	{
		if(__DEBUG__) TRACE("GRPCHRS_LIMIT[%s]: %d", decodeGroupType(charGroup), GRPCHRS_LIMIT[charGroup]);
		sum += GRPCHRS_LIMIT[charGroup];
	}

	if(__DEBUG__) TRACE("sumGrpChrLimit(): %d", sum);

	return sum;
}

/**
 * Returns the limit for a specific character group taken from the GRPCHRS_LIMIT array
 * @param charGroup The id of the character group
 * @return The limit for the character group
 */
int getGrpChrLimit(int charGroup)
{
	return GRPCHRS_LIMIT[charGroup];
}

/**
 * Indicates if a specific character group is excluded for contribute in the password generation. The value is taken from the EXCLUDED_GRPS array
 * @param charGroup The id of the character group
 * @return True if the character group is excluded, False otherwise
 */
bool isGrpChrExcluded(int charGroup)
{
	bool excluded = false;
	for(int i = 0; i < GROUPS_NBR-1; ++i)
	{
		if (charGroup == EXCLUDED_GRPS[i])
		{
			excluded = true;
			break;
		}
	}
	return excluded;
}

/**
 * Shows the excluded flag of the character groups. Only for debugging proposes
 */
void traceGrpChrExcluded(void)
{
	if(!__DEBUG__) return;

	TRACE("START traceGrpChrExcluded(void)", "");

	char estado[20];
	for(int i = 0; i < GROUPS_NBR-1; ++i)
	{
		switch (EXCLUDED_GRPS[i])
		{
		case -1:
			sprintf(estado, "Uninitialized");
			break;
		default:
			sprintf(estado, "Excluded");
			break;
		}
		TRACE("EXCLUDED_GRPS[%d]: %s : %s", i, decodeGroupType(EXCLUDED_GRPS[i]), estado);
	}
	TRACE("END traceGrpChrExcluded(void)", "");
}

/**
 * Calculates the sum of all the limits of the character groups that are not excluded
 * @return the total sum of the characters limit
 */
int sumActiveGrpChrLimit(void)
{
	if (__DEBUG__) TRACE("START sumActiveGrpChrLimit(void)", "");

	int sum = 0;

	for(int charGroup = UPPER_CASE_GROUP; charGroup < GROUPS_NBR; ++charGroup)
	{
		if (__DEBUG__) TRACE("isGrpChrExcluded(%s): %s", decodeGroupType(charGroup), isGrpChrExcluded(charGroup) ? "True" : "False");
		if (__DEBUG__) TRACE("getGrpChrLimit(%s): %d", decodeGroupType(charGroup), getGrpChrLimit(charGroup));
		sum += isGrpChrExcluded(charGroup) ? 0 : getGrpChrLimit(charGroup);
	}

	if (__DEBUG__) TRACE("END sumActiveGrpChrLimit(void)", "");

	return sum;
}

/**
 * Calculates the sum of all the limits of the character groups that are not excluded except the character group passed as argument
 * @param charGroup The characters group that is not going to be part of the sum
 * @return the sum of the characters limit different than the parameter charGroup
 */
int sumRestActiveGrpChrLimit(int charGroup)
{
	if (__DEBUG__) TRACE("START sumRestActiveGrpChrLimit(%s)", decodeGroupType(charGroup));

	int totalSum = sumActiveGrpChrLimit();

	if (__DEBUG__) TRACE("isGrpChrExcluded(%s): %s", decodeGroupType(charGroup), isGrpChrExcluded(charGroup) ? "True" : "False");

	totalSum -= isGrpChrExcluded(charGroup) ? 0 : getGrpChrLimit(charGroup);

	if (__DEBUG__) TRACE("END sumRestActiveGrpChrLimit(%s)", decodeGroupType(charGroup));

	return totalSum;
}

/**
 * Pone la varuable global GRPCHRS_LIMIT[charGroup] al valor que se le pasa.
 * Devuelve false si el conjunto de caracteres NO está activo o
 */
bool setGrpChrLimit(int charGroup, int value)
{
	if (__DEBUG__) TRACE("START setGrpChrLimit(%s, %d)", decodeGroupType(charGroup), value);

	GRPCHRS_LIMIT[charGroup] = value;

	if (!checkGrpChrLimit(charGroup, value) )
	{
		if (__DEBUG__) TRACE("END PREMATURE setGrpChrLimit(%s, %d)", decodeGroupType(charGroup), value);
		return false;
	}

	if (__DEBUG__) TRACE("isGrpChrExcluded(%s): %s", decodeGroupType(charGroup), isGrpChrExcluded(charGroup) ? "true" : "false");

	if (!isGrpChrExcluded(charGroup))
		printStatus(HIGH, "Character group %s: Limit set to %i", decodeGroupType(charGroup), value );

	if (__DEBUG__) TRACE("END setGrpChrLimit(%s, %d)", decodeGroupType(charGroup), value);

	return true;
}

/**
  * Check the validity of the limit to the number of characters in the character set
  * Returns false if the character set is excluded, if the value is less than 1
  * or if the sum with the rest of the values exceeds the length of the password to be generated and
  * the number of characters is greater than 1/4 of the length of the password
  * @param charGroup The id of the character set to be checked
  * @param value The value of the characters limit of the charGroup
  * @return True if the check match the rules, false otherwise
  */
bool checkGrpChrLimit(int charGroup, int value)
{
	if (__DEBUG__)
	{
		TRACE("START checkGrpChrLimit(%s, %d)", decodeGroupType(charGroup), value);
		TRACE("PASS_LEN: %d", PASS_LEN);
	}

	if (isGrpChrExcluded(charGroup))
	{
		if (__DEBUG__) TRACE("END PREMATURO checkGrpChrLimit(%s, %d)", decodeGroupType(charGroup), value);
		return false;
	}

	if (value < 1 )
	{
		printStatus(BASIC, "Character group %s: Illegal value for a limit", decodeGroupType(charGroup));
		return false;
	}
	if (value + sumRestActiveGrpChrLimit(charGroup) > PASS_LEN && value > ceil(PASS_LEN / 4.0))
	{
		printStatus(BASIC, "Character group %s: Value %i will exceed the limit", decodeGroupType(charGroup), value );
		return false;
	}

	if (__DEBUG__) TRACE("END checkGrpChrLimit(%s, %d)", decodeGroupType(charGroup), value);

	return true;
}

/**
 * Does all the checks required for the passwored rules defined
 */
bool checkPasswordRules(void)
{
	if (__DEBUG__) TRACE("START checkPasswordRules(void)", "");

	int ActiveGrpChrLimit = sumActiveGrpChrLimit();

	if (__DEBUG__)
	{
		TRACE("PASS_LEN: %d", PASS_LEN);
		TRACE("ActiveGrpChrLimit(): %d", ActiveGrpChrLimit);
	}

	if (PASS_LEN < ActiveGrpChrLimit)
	{
		printStatus(BASIC, "The given rules cannot be applied to the password. The number of characters to be set by the rules exceeds the size of the password");
		return false;
	}
	printStatus(BASIC, "The rules given can be applied to the password generation");
	return true;
}

/* ************************************************************************
 * CHAR GROUP COUNTER SECTION
 ************************************************************************ */

/**
 * Reset the counter of characters used for each character set
 */
void resetCharGroupCounter(void)
{
	NBR_SYMBL = 0;
	NBR_UPPER = 0;
	NBR_LOWER = 0;
	NBR_NUMBR = 0;
}

/* ************************************************************************
 * CHAR GROUP SECTION
 ************************************************************************ */
/**
 * Returns a random character from the set indicated from the parameter setOfChars
 * @param setOfChars The set of characters used to select one of them
 * @return The character selected randomly from the chacaters set
 */
char getCharFrom(char * setOfChars)
{
	int idx = naturalRandomNbr(strlen(setOfChars)-1);
	if (__DEBUG__)
	{
		TRACE("setOfChars: %s", setOfChars);
		TRACE("idx: %i - getCharFrom: %c - ", idx, (char) setOfChars[idx]);
	}
	return (char) setOfChars[idx];
}

/**
 * Private function that indicates if the character set has reached the limit of its characters
 * @param charGroup Set of characters to evaluate
 * @return True if the limit has been reached, False otherwise
 */
/* private */ static bool _hasCharsRequired(int charGroup)
{
	switch (charGroup)
	{
	case UPPER_CASE_GROUP:
		if (inExcludedGroups(UPPER_CASE_GROUP)) return true;
		if (NBR_UPPER >= getGrpChrLimit(UPPER_CASE_GROUP)) return true;
		break;
	case LOWER_CASE_GROUP:
		if (inExcludedGroups(LOWER_CASE_GROUP)) return true;
		if (NBR_LOWER >= getGrpChrLimit(LOWER_CASE_GROUP)) return true;
		break;
	case NUMBR_CASE_GROUP:
		if (inExcludedGroups(NUMBR_CASE_GROUP)) return true;
		if (NBR_NUMBR >= getGrpChrLimit(NUMBR_CASE_GROUP)) return true;
		break;
	case SYMBL_CASE_GROUP:
		if (inExcludedGroups(SYMBL_CASE_GROUP)) return true;
		if (NBR_SYMBL >= getGrpChrLimit(SYMBL_CASE_GROUP)) return true;
		break;
	}
	return false;
}

/**
 * Indicates if the character set has reached the limit of its characters
 * Prints a status message for status level HIGH
 * @param charGroup Set of characters to evaluate
 * @return True if the limit has been reached, False otherwise
 */
bool hasCharsRequired(int charGroup)
{
	bool hasCharsRequired = _hasCharsRequired(charGroup);
	printStatus(HIGH, "Character group %s has chars required %s", decodeGroupType(charGroup), boolToString(hasCharsRequired));
	return hasCharsRequired;
}

/* ************************************************************************
 * EXCLUDED GROUP SECTION
 ************************************************************************ */

/**
 * Initializes the excluded groups array to NONE_GROUP mark. This array keeps the sets of characters which have been marked as excluded
 */
void initExcludedGroups(void)
{
	for (int i = UPPER_CASE_GROUP; i < GROUPS_NBR-1; ++i)
		EXCLUDED_GRPS[i] = NONE_GROUP;
}

/**
 * Appends a set of characters to the excluded array. A maximum of three sets can be appended
 * Prints a status message for status level HIGH
 * @param charGroup Te set of characters to be excluded
 * @return True if success, False if the set of characters couldn't be appended
 */
bool appendExcludedGroups(int charGroup)
{
	for (int i = 0; i < GROUPS_NBR-1; ++i)
	{
		if (EXCLUDED_GRPS[i] == charGroup)
		{
			printStatus(HIGH, "Character group %s is excluded", decodeGroupType(charGroup));
			return FAIL; // Do not include the same groupNbr more than once*
		}
		if (EXCLUDED_GRPS[i] == NONE_GROUP)
		{
			EXCLUDED_GRPS[i] = charGroup;
			printStatus(HIGH, "Character group %s excluded for password generation", decodeGroupType(charGroup));
			return SUCCESS;
		}
	}
	printStatus(HIGH, "Character group %s not excluded. The maximum of excluded groups has been reached", decodeGroupType(charGroup));
	return FAIL;
}

/**
 * Checks if the set of characters is excluded or not
 * Prints a status message for status level HIGH
 * @param charGroup The set of characters to be checked
 * @return True if the set of characters is marked as excluded, otherwise False
 */
bool inExcludedGroups(int charGroup)
{
	for (int i = 0; i < GROUPS_NBR-1; ++i)
	{
		if (charGroup == EXCLUDED_GRPS[i])
		{
			printStatus(HIGH, "Character group %s found in 'excluded groups'", decodeGroupType(charGroup));
			return true;
		}
	}
	printStatus(HIGH, "Character group %s not found in 'excluded groups'", decodeGroupType(charGroup));
	return false;
}

/**
 * Checks if the only set of characters selected is the one of symbols
 * @return True if only symbols is selected, False otherwise
 */
bool onlySymbols(void)
{
	bool excludedUpper = false;
	bool excludedLower = false;
	bool excludedNumbr = false;
	bool onlySymbols;
	for (int charGroup = 0; charGroup < GROUPS_NBR; ++charGroup)
	{
		switch (charGroup)
		{
		case UPPER_CASE_GROUP:
			excludedUpper = inExcludedGroups(charGroup);
			break;
		case LOWER_CASE_GROUP:
			excludedLower = inExcludedGroups(charGroup);
			break;
		case NUMBR_CASE_GROUP:
			excludedNumbr = inExcludedGroups(charGroup);
			break;
		}
	}
	onlySymbols = excludedUpper && excludedLower && excludedNumbr;
	printStatus(HIGH, "Only Symbols is %s", boolToString(onlySymbols));
	return onlySymbols;
}

/**
 * Prints a status message indicating the sets of characters excluded. Status level BASIC
 */
void printExcludedGroups(void)
{
	for (int i = 0; i < GROUPS_NBR-1; ++i)
	{
		if (EXCLUDED_GRPS[i] != NONE_GROUP) printStatus(BASIC, "%s is excluded\n", decodeGroupType(EXCLUDED_GRPS[i]));
	}

}

/* ************************************************************************
 * GROUP SECTION
 ************************************************************************ */

/**
 * Selects a set of charates randomly from a group limited by nbrItemsGroup and not using the excluded sets
 * @param nbrItemsGroup the number of sets to use. The sets are from 0 to 3, UPPER_CASE_GROUP, LOWER_CASE_GROUP, NUMBR_CASE_GROUP and SYMBL_CASE_GROUP
 * return Th id of the set of characters selected
 */
int randomGroupSelector(int nbrItemsGroup)
{
	int charGroup = 0;

	if (nbrItemsGroup > GROUPS_NBR-1) nbrItemsGroup = GROUPS_NBR-1;
	do
	{
		charGroup = naturalRandomNbr(nbrItemsGroup);
	}
	while (inExcludedGroups(charGroup));
	return charGroup;
}

/**
 * Decodes the id of a set of charaters to a name in human language
 * @param charGroup The id of the set of charaters to decode
 * @return The string with the name of the set of characters
 */
char * decodeGroupType(int charGroup)
{
	switch (charGroup)
	{
	case UPPER_CASE_GROUP:
		return "'Upper Case'";
		break;
	case LOWER_CASE_GROUP:
		return "'Lower Case'";
		break;
	case NUMBR_CASE_GROUP:
		return "'Numbers'";
		break;
	case SYMBL_CASE_GROUP:
		return "'Symbols'";
		break;
	default:
		return "'Unknown Group'";
		break;
	}
	return "'Unknown Weird Group'";
}

/* ************************************************************************
 * PASSWORD SECTION
 ************************************************************************ */

/**
 * Password generator engine
 * @param passContainer The string to stores the password
 * @return The string with the password generated
 */
char * genPass(char * passContainer)
{
	bool allTheLex;
	bool allReqChars;
	int i;
	int iterations = 0;

	if (__DEBUG__) TRACE("passContainer Size: %d\n", PASS_LEN);

	if (PASS_LEN <= 0)
	{
		printStatus(BASIC, "ATTENTION - No password was generated because invalid password size");
		return (char *)passContainer;
	}

	/*
	 * Shuffles the sets of characters to increase the entropy
	 */
	char * UPPER_CASE_SHUFFLED = shuffleCharacterSet(UPPER_CASE);
	char * LOWER_CASE_SHUFFLED = shuffleCharacterSet(LOWER_CASE);
	char * NUMBR_CASE_SHUFFLED = shuffleCharacterSet(NUMBR_CASE);
	char * SYMBL_CASE_SHUFFLED = shuffleCharacterSet(SYMBL_CASE);

	if (__DEBUG__)
	{
		TRACE("UPPER_CASE_SHUFFLED %s", UPPER_CASE_SHUFFLED);
		TRACE("LOWER_CASE_SHUFFLED %s", LOWER_CASE_SHUFFLED);
		TRACE("NUMBR_CASE_SHUFFLED %s", NUMBR_CASE_SHUFFLED);
		TRACE("SYMBL_CASE_SHUFFLED %s", SYMBL_CASE_SHUFFLED);
	}

	do
	{
		// Initialize
		int charGroup = NONE_GROUP;
		bool hasUpper = inExcludedGroups(UPPER_CASE_GROUP);
		bool hasLower = inExcludedGroups(LOWER_CASE_GROUP);
		bool hasNumbr = inExcludedGroups(NUMBR_CASE_GROUP);
		bool hasSymbl = inExcludedGroups(SYMBL_CASE_GROUP);
		resetCharGroupCounter();

		char * ptr = passContainer;

		if (__DEBUG__) TRACE("ptr address: %p\n", ptr);

		for (i = 0; i < PASS_LEN; ++i)
		{
			randomize();
			charGroup = randomGroupSelector(GROUPS_NBR-1);
			if (__DEBUG__) TRACE("1st charGroup:%s - ", decodeGroupType(charGroup));
			switch (charGroup)
			{
			case UPPER_CASE_GROUP:
				hasUpper = true;
				++NBR_UPPER;
				*ptr++ = getCharFrom(UPPER_CASE_SHUFFLED);
				break;
			case LOWER_CASE_GROUP:
				hasLower = true;
				++NBR_LOWER;
				*ptr++ = getCharFrom(LOWER_CASE_SHUFFLED);
				break;
			case NUMBR_CASE_GROUP:
				++NBR_NUMBR;
				hasNumbr = true;
				*ptr++ = getCharFrom(NUMBR_CASE_SHUFFLED);
				break;
			case SYMBL_CASE_GROUP:
				if (hasCharsRequired(SYMBL_CASE_GROUP) && !onlySymbols())
				{
					charGroup = randomGroupSelector(GROUPS_NBR-2);
					if (__DEBUG__) TRACE("2nd charGroup:%s - ", decodeGroupType(charGroup));
					switch (charGroup)
					{
					case UPPER_CASE_GROUP:
						hasUpper = true;
						++NBR_UPPER;
						*ptr++ = getCharFrom(UPPER_CASE_SHUFFLED);
						break;
					case LOWER_CASE_GROUP:
						hasLower = true;
						++NBR_LOWER;
						*ptr++ = getCharFrom(LOWER_CASE_SHUFFLED);
						break;
					case NUMBR_CASE_GROUP:
						hasNumbr = true;
						++NBR_NUMBR;
						*ptr++ = getCharFrom(NUMBR_CASE_SHUFFLED);
						break;
					}
				}
				else {
					hasSymbl = true;
					++NBR_SYMBL;
					*ptr++ = getCharFrom(SYMBL_CASE_SHUFFLED);
				}
				break;
			}
			if (__DEBUG__) TRACE("charGroup: %s - ptr address: %p\n", decodeGroupType(charGroup), ptr);
		}
		if (++iterations > 199)
		{
			allReqChars = true;
			allTheLex = true;
			printStatus(BASIC, "The New Password generated doesn't follow the given rules");
		}
		else
		{
			allTheLex = hasUpper && hasLower && hasNumbr && hasSymbl;
			allReqChars = true;
			for (charGroup = UPPER_CASE_GROUP; charGroup < GROUPS_NBR; ++charGroup)
			{
				if (__DEBUG__) TRACE("charGroup: %s - hasCharsRequired: %i\n", decodeGroupType(charGroup), hasCharsRequired(charGroup));
				allReqChars = allReqChars && hasCharsRequired(charGroup);
			}
		}
	} while (!allTheLex || !allReqChars);

	printStatus(BASIC, "New Password generated in %i iteration%s", iterations, iterations == 1 ? "" : "s" );

	/*
	 * Cleans up the house
	 */
	free(UPPER_CASE_SHUFFLED);
	free(LOWER_CASE_SHUFFLED);
	free(NUMBR_CASE_SHUFFLED);
	free(SYMBL_CASE_SHUFFLED);

	return (char *)(passContainer);
}

/**
 * Sets the settings stored in the global variable ptPassgenConf to the spare global variables used in genpass, and other functions
 * The global spare variables are PASS_LEN, XCLUDED_GRPS[], GRPCHRS_LIMIT[]
 * This variables should be removed in following versions
 */
void setPassgenConfCaseRule2Values(void)
{
	if (__DEBUG__) TRACE("START of setPassgenConfCaseRule2Values()", "");

	passgenConf_t * ptPassgenConf = getPassgenConf();

	if (!strcmp(ptPassgenConf->passwordLength.preset, getPasswordLengthPresetsName(USER)))
		PASS_LEN = ptPassgenConf->passwordLength.user;
	else
		PASS_LEN = ptPassgenConf->passwordLength.size;

	if (!ptPassgenConf->upperCaseRule.chkBox)
	{
		appendExcludedGroups(UPPER_CASE_GROUP);
	}
	setGrpChrLimit(UPPER_CASE_GROUP, ptPassgenConf->upperCaseRule.val);

	if (!ptPassgenConf->lowerCaseRule.chkBox)
	{
		appendExcludedGroups(LOWER_CASE_GROUP);
	}
	setGrpChrLimit(LOWER_CASE_GROUP, ptPassgenConf->lowerCaseRule.val);

	if (!ptPassgenConf->numberCaseRule.chkBox)
	{
		appendExcludedGroups(NUMBR_CASE_GROUP);
	}
	setGrpChrLimit(NUMBR_CASE_GROUP, ptPassgenConf->numberCaseRule.val);

	if (!ptPassgenConf->symbolCaseRule.chkBox)
	{
		appendExcludedGroups(SYMBL_CASE_GROUP);
	}
	setGrpChrLimit(SYMBL_CASE_GROUP, ptPassgenConf->symbolCaseRule.val);

	if (__DEBUG__) TRACE("END of setPassgenConfCaseRule2Values()", "");
}

/**
* Allocates memory for the password and applies the settings stored in passgen configuration
* @return The password storage. You should freed after use.
 */
char * passgenConf2Rules(void)
{
	char * newPass;
	passgenConf_t * ptPassgenConf = getPassgenConf();
	int errnum;

	if (__DEBUG__) TRACE("START of passgenConf2Rules", "");

	initGrpChrLimit();
	initExcludedGroups();
	setPassgenConfCaseRule2Values();
	printExcludedGroups();

	if (PASS_LEN < 1)
	{
		printStatus(BASIC, "ERROR - The password length must a positive number greater the zero. The current length is: %d", PASS_LEN);
		newPass = malloc(1);
		*newPass = '\0';
		return newPass;
	}

	if (!strcmp(ptPassgenConf->passwordLength.preset, getPasswordLengthPresetsName(USER)))
		PASS_LEN = ptPassgenConf->passwordLength.user;
	else
		PASS_LEN = ptPassgenConf->passwordLength.size;

	if (!(newPass = (char *) malloc(PASS_LEN+1))) {
		errnum = errno;
		ERROR("Error Allocating memory for newPass: (%i) - %s\n", errnum, strerror(errnum));
		exit(errnum);
	}

	if (!memset(newPass, 0, PASS_LEN+1)) {
		errnum = errno;
		ERROR("Error Setting memory for newPass: (%i) - %s\n", errnum, strerror(errnum));
		exit(errnum);
	}

	if (__DEBUG__) TRACE("newPass initialized: %s", newPass);

	if (__DEBUG__)
	{
		TRACE("newPass Address %p", newPass);
		TRACE("END of passgenConf2Rules", "");
	}
	return newPass;
}


/**
 * Runs passgen in Graphic User Interface mode (GUI)
 */
void passgenGUI(void)
{
	GtkWidget * passgenMainWindow;

	// initializes the GtkBuilder static var
	/* ONE AND ONLY ONE TO RULE THE ONLY ONE */
	setGtkBuilder();

	// Get main window pointer from UI
	passgenMainWindow = GTK_WIDGET(gtk_builder_get_object(getGtkBuilder(), "gtkDialog_passgen"));
	gtkInitPassgen();
	//gtkMenuItemStatusGroupSet(); Not required. Implemented in Glade

	// Connect signals
	gtkSignalsConnect();
	gtk_builder_connect_signals(getGtkBuilder(), NULL);

	/* Show window. All other widgets are automatically shown by GtkBuilder */
	gtk_widget_show(passgenMainWindow);
	gtkSetCursor(NORMAL_CURSOR);

	// Sets the version of passgen in the about dialog
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(gtk_builder_get_object(getGtkBuilder(), "gtkAboutDialog_passgen")), VERSION);

	catchSigterm();

	gtk_main();
}

/**
 * Runs passgen in Command Line Interface mode (CLI)
 */
int passgenCLI(void)
{
	/* INITIALIZATION */
	char * newPass;

	/* SETTING RULES TO PLAY */
	newPass = passgenConf2Rules();

	if (__DEBUG__) TRACE("newPass: %s", newPass);
	if (__DEBUG__) TRACE("newPass Address %p", newPass);

	/* GENERATE PASSWORD */
	checkPasswordRules();
	if (genPass(newPass))
	{
		printf("> > > > > > > Your new password is: %s\n", (char *)newPass);
	}
	else
	{
		puts("Something went wrong generating the password");
	}

	free(newPass);

	return EXIT_SUCCESS;
}

/* ************************************************************************
 * MAIN PROGRAM
 ************************************************************************ */
/**
 * main function
 * @param argc
 * @param argv[]
 */
int main(int argc, char * argv[])
{
	// initializes the ptPassgenConf static var
	/* ONE AND ONLY ONE TO RULE THE ONLY ONE */
	passgenConf_t * ptPassgenConf = setPassgenConf();
	statusLevel = BASIC;

	initRandomSeed();

	sprintf(ptPassgenConf->appName, "%s", basename(argv[0]));
	if (__DEBUG__ ) printPassgenConfig();
	/* ***************************************************** */
	/* 				COMMAND  LINE  INTERFACE				 */
	/* ***************************************************** */
	if (argc > 1)
	{
		userInterface = CLI;
		psgParams_t * psgParams = readPsgParams(argc, argv);

		if (psgParams->help)
		{
			passgenHelp();
			return EXIT_SUCCESS;
		}

		if (psgParams->config)
		{
			printPassgenConfig();
			return EXIT_SUCCESS;
		}

		if (psgParams->version)
		{
			printf("passgen Version:%s Compilation:%s\n", VERSION, COMPILATION);
			return EXIT_SUCCESS;
		}

		if (psgParams->nogui)
		{
			printfacts();
			return passgenCLI();
		}
		if (__DEBUG__) TRACE("%s", "option not recognized");
		return EXIT_SUCCESS;
	}
	/* ***************************************************** */
	/* 				GRAPHICAL USER INTERFACE				 */
	/* ***************************************************** */
	if (__DEBUG__) printfacts();
	printStatus(BASIC, "%s Version: %s", PROGRAM, VERSION);
	gtk_init(&argc, &argv);
	userInterface = GUI;
	passgenGUI();
	return EXIT_SUCCESS;
}
