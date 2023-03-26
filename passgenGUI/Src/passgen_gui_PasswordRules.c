/*
 * passgen_gui_PasswordRules.c
 *
 *  Created on: 21 feb. 2023
 *      Author: ipserc
 */

#include "passgen_gui_PasswordRules.h"

#define __DEBUG__ false

/* ***********************************************************
 * gtkEntry_PasswordRules_XXXXX
 *********************************************************** */

/**
 * Sets the Editable property for the gtkEntry control
 * @param gtkEntryName The name of the gtkEntry control
 * @param editable The editable attribute True or False
 */
void gtkEntryPasswordRulesSetEditable(char * gtkEntryName, gboolean editable)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), gtkEntryName));
	gtkWidgetSetEditable((GtkWidget *) gtkEntryPasswordRules, editable);
}

/**
 * Initializes the gtkEntryName for gtkEntryPasswordRules section and sets the editable attribute
 * @param gtkEntryName the gtkEntry control name of the set of characters
 * @param val The value of the limit for the set of characters
 * @param chkBox The state of the checkbox to set teh editable attribute
 */
void gtkEntryPasswordRulesInit(char * gtkEntryName, int val, bool chkBox)
{
	char strVal[3];

	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), gtkEntryName));

	sprintf(strVal, "%d", val);
	gtk_entry_set_text((GtkEntry *) gtkEntryPasswordRules, strVal);

	if (__DEBUG__) TRACE("gtkEntryPasswordRulesInit chkBox: %s", chkBox ? "True" : "False");
	gtkWidgetSetEditable((GtkWidget *) gtkEntryPasswordRules, chkBox);
}

/* ***********************************************************
 * gtkCheckButton_PasswordRules_XXXXX
 *********************************************************** */

/**
 * Returns the Active state for the gtkCheckButtonName passed
 * @param gtkCheckButtonName The name of the gtkCheckButton
 * @return The state as boolena, True if actve, False otherwise
 */
gboolean gtkCheckButtonPasswordRulesGetActive(char * gtkCheckButtonName)
{
	GtkCheckButton * gtkCheckButtonPasswordRules = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), gtkCheckButtonName));
	return gtk_toggle_button_get_active((GtkToggleButton *) gtkCheckButtonPasswordRules);
}

/**
 * Sets the status active to a gtkCheckButton selected by its name
 * @param gtkCheckButtonName The name of the gtkCheckButton
 */
void gtkCheckButtonPasswordRulesSetActive(char * gtkCheckButtonName)
{
	GtkCheckButton * gtkCheckButtonPasswordRules = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), gtkCheckButtonName));
	gtk_toggle_button_set_active((GtkToggleButton *) gtkCheckButtonPasswordRules, true);
}

/**
 * Manage the signal Toggled for gtkCheckButtonName and gtkEntryName contorls
 * Calls gtkWidgetSetEditable and gtkCheckButtonPasswordRulesGetActive
 * @param gtkCheckButtonName The gtkCheckButton control Name
 * @param gtkEntryName The gtkEntry control name
 */
void gtkCheckButtonPasswordRulesToggled(char * gtkCheckButtonName, char * gtkEntryName)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), gtkEntryName));
	if (__DEBUG__) TRACE("gtkCheckButtonPasswordRulesToggled Active: %s", gtkCheckButtonPasswordRulesGetActive(gtkCheckButtonName) ? "True" : "False");
	gtkWidgetSetEditable((GtkWidget *) gtkEntryPasswordRules, gtkCheckButtonPasswordRulesGetActive(gtkCheckButtonName));
}

/**
 * Initializes the gtkCheckButton by its name to the state of chkBox
 * @param gtkCheckButtonName The gtkCheckButton control name
 * @param chkBox The chkBox state True for active, False for dismiss
 */
void gtkCheckButtonPasswordRulesInit(char * gtkCheckButtonName, bool chkBox)
{
	GtkCheckButton * gtkCheckButtonPasswordRules = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), gtkCheckButtonName));
	if (__DEBUG__) TRACE("gtkCheckButtonPasswordRulesInit chkBox: %s", chkBox ? "True" : "False");
	gtk_toggle_button_set_active((GtkToggleButton *) gtkCheckButtonPasswordRules, chkBox);
}

/**
 * Check if the checkButtonSet is the last active of the Button Password Rules
 * @param checkButtonSet The id of te set, can be UPPER, LOWER, NUMBER or SYMBOL
 * @return True if the checkButtonSet is the last button active
 */
gboolean gtkCheckButtonPasswordRulesLast(int checkButtonSet)
{
	int FIRST = 0;
	gboolean CheckButtonPasswordRulesLast = TRUE;


	for (characterSets_t set = FIRST; set < LAST_SET; ++set)
	{
		if (set == checkButtonSet) continue;
		else
		{
			switch (set)
			{
			case UPPER:
				CheckButtonPasswordRulesLast &= !gtkCheckButtonPasswordRulesSetUpperGetActive();
				break;
			case LOWER:
				CheckButtonPasswordRulesLast &= !gtkCheckButtonPasswordRulesSetLowerGetActive();
				break;
			case NUMBER:
				CheckButtonPasswordRulesLast &= !gtkCheckButtonPasswordRulesSetNumberGetActive();
				break;
			case SYMBOL:
				CheckButtonPasswordRulesLast &= !gtkCheckButtonPasswordRulesSetSymbolGetActive();
				break;
			}
		}
	}
	return CheckButtonPasswordRulesLast;
}

/* ***********************************************************
 * gtkEntry_PasswordRulesSet_Number
 *********************************************************** */

/**
 * Sets the editable property for "gtkEntry_PasswordRulesSet_Number"
 * @param editable The editable property
 */
void gtkEntryPasswordRulesSetNumberSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Number", editable);
}

/**
 * Sets the value and the check from ptPassgenConf to gtkEntry_PasswordRulesSet_Number
 * Calls gtkEntryPasswordRulesInit
 */
void gtkEntryPasswordRulesSetNumberInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Number", ptPassgenConf->numberCaseRule.val, ptPassgenConf->numberCaseRule.chkBox);
}

/**
 * Returns the value of the limit from gtkEntry_PasswordRulesSet_Number
 * @return The value of the limit
 */
int gtkEntryPasswordRulesSetNumberGetVal(void)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordRulesSet_Number"));
	return atoi(gtk_entry_get_text(gtkEntryPasswordRules));
}

/* ***********************************************************
 * gtkCheckButton_PasswordRulesSet_Number
 *********************************************************** */

/**
 * Returns the Active state for gtkCheckButton_PasswordRulesSet_Number
 * @return True if the CheckButton of Number is Active, otherwise False
 */
gboolean gtkCheckButtonPasswordRulesSetNumberGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Number");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Number
 * It calls gtkCheckButtonPasswordRulesLast, gtkCheckButtonPasswordRulesGetActive, gtkCheckButtonPasswordRulesToggled
 * If it is the las active checkbox, prevents deactivating
 * Prints Status message for status level NORMAL
 */
void gtkCheckButtonPasswordRulesSetNumberToggled(void)
{
	if (gtkCheckButtonPasswordRulesLast(NUMBER))
	{
		if (!gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Number"))
		{
			printStatus(NORMAL, "%s", "Warning: At least One of the Check Buttom for Password Rules Set must be Active. Numbers Check is kept active");
			if (__DEBUG__) TRACE(status, "");
			gtkCheckButtonPasswordRulesSetActive("gtkCheckButton_PasswordRulesSet_Number");
		}
		return;
	}
	gtkCheckButtonPasswordRulesToggled("gtkCheckButton_PasswordRulesSet_Number", "gtkEntry_PasswordRulesSet_Number");
}

/**
 * Sets the check from ptPassgenConf to gtkEntry_PasswordRulesSet_Number
 * Calls gtkCheckButtonPasswordRulesInit
 */
void gtkCheckButtonPasswordRulesSetNumberInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkCheckButtonPasswordRulesInit("gtkCheckButton_PasswordRulesSet_Number", ptPassgenConf->numberCaseRule.chkBox);
}

/* ***********************************************************
 * gtkEntry_PasswordRulesSet_Symbol
 *********************************************************** */

/**
 * Sets the Editable property for "gtkEntry_PasswordRulesSet_Symbol"
 * @param editable The editable property
 */
void gtkEntryPasswordRulesSetSymbolSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Symbol", editable);
}

/**
 * Sets the value and the check from ptPassgenConf to gtkEntry_PasswordRulesSet_Symbol
 * Calls gtkEntryPasswordRulesInit
 */
void gtkEntryPasswordRulesSetSymbolInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Symbol", ptPassgenConf->symbolCaseRule.val, ptPassgenConf->symbolCaseRule.chkBox);
}

/**
 * Returns the value of the limit from gtkEntry_PasswordRulesSet_Symbol
 * @return The value of the limit
 */
int gtkEntryPasswordRulesSetSymbolGetVal(void)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordRulesSet_Symbol"));
	return atoi(gtk_entry_get_text(gtkEntryPasswordRules));
}

/* ***********************************************************
 * gtkCheckButton_PasswordRulesSet_Symbol
 *********************************************************** */

/**
 * Returns the Active state for gtkCheckButton_PasswordRulesSet_Symbol"
 * @return True if the CheckButton of Number is Active, otherwise False
 */
gboolean gtkCheckButtonPasswordRulesSetSymbolGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Symbol");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Symbol
 * It calls gtkCheckButtonPasswordRulesLast, gtkCheckButtonPasswordRulesGetActive, gtkCheckButtonPasswordRulesToggled
 * If it is the las active checkbox, prevents deactivating
 * Prints Status message for status level NORMAL
 */
void gtkCheckButtonPasswordRulesSetSymbolToggled(void)
{
	if (gtkCheckButtonPasswordRulesLast(SYMBOL))
	{
		if (!gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Symbol"))
		{
			printStatus(NORMAL, "%s", "Warning: At least One of the Check Buttom for Password Rules Set must be Active. Symbols Check is kept active");
			if (__DEBUG__) TRACE(status, "");
			gtkCheckButtonPasswordRulesSetActive("gtkCheckButton_PasswordRulesSet_Symbol");
		}
		return;
	}
	gtkCheckButtonPasswordRulesToggled("gtkCheckButton_PasswordRulesSet_Symbol", "gtkEntry_PasswordRulesSet_Symbol");
}

/**
 * Sets the check from ptPassgenConf to gtkCheckButton_PasswordRulesSet_Symbol
 * Calls gtkCheckButtonPasswordRulesInit
 */
void gtkCheckButtonPasswordRulesSetSymbolInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkCheckButtonPasswordRulesInit("gtkCheckButton_PasswordRulesSet_Symbol", ptPassgenConf->symbolCaseRule.chkBox);
}

/* ***********************************************************
 * gtkEntry_PasswordRulesSet_Lower
 *********************************************************** */

/**
 * Sets the Editable property for "gtkEntry_PasswordRulesSet_Lower"
 * @param editable The editable property
 */
void gtkEntryPasswordRulesSetLowerSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Lower", editable);
}

/**
 * Sets the value and the check from ptPassgenConf to gtkEntry_PasswordRulesSet_Lower
 * Calls gtkEntryPasswordRulesInit
 */
void gtkEntryPasswordRulesSetLowerInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Lower", ptPassgenConf->lowerCaseRule.val, ptPassgenConf->lowerCaseRule.chkBox);
}

/**
 * Returns the value of the limit from gtkEntry_PasswordRulesSet_Lower
 * @return The value of the limit
 */
int gtkEntryPasswordRulesSetLowerGetVal(void)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordRulesSet_Lower"));
	return atoi(gtk_entry_get_text(gtkEntryPasswordRules));
}

/* ***********************************************************
 * gtkCheckButton_PasswordRulesSet_Lower
 *********************************************************** */

/**
 * Returns the Active state for gtkCheckButton_PasswordRulesSet_Lower"
 * @return True if the CheckButton of Number is Active, otherwise False
 */
gboolean gtkCheckButtonPasswordRulesSetLowerGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Lower");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Lower
 * It calls gtkCheckButtonPasswordRulesLast, gtkCheckButtonPasswordRulesGetActive, gtkCheckButtonPasswordRulesToggled
 * If it is the las active checkbox, prevents deactivating
 * Prints Status message for status level NORMAL
 */
void gtkCheckButtonPasswordRulesSetLowerToggled(void)
{
	if (gtkCheckButtonPasswordRulesLast(LOWER))
	{
		if (!gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Lower"))
		{
			printStatus(NORMAL, "%s", "Warning: At least One of the Check Buttom for Password Rules Set must be Active. Lower case Check is kept active");
			if (__DEBUG__) TRACE(status, "");
			gtkCheckButtonPasswordRulesSetActive("gtkCheckButton_PasswordRulesSet_Lower");
		}
		return;
	}
	gtkCheckButtonPasswordRulesToggled("gtkCheckButton_PasswordRulesSet_Lower", "gtkEntry_PasswordRulesSet_Lower");
}

/**
 * Sets the check from ptPassgenConf to gtkCheckButton_PasswordRulesSet_Lower
 * Calls gtkCheckButtonPasswordRulesInit
 */
void gtkCheckButtonPasswordRulesSetLowerInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkCheckButtonPasswordRulesInit("gtkCheckButton_PasswordRulesSet_Lower", ptPassgenConf->lowerCaseRule.chkBox);
}

/* ***********************************************************
 * gtkEntry_PasswordRulesSet_Upper
 *********************************************************** */

/**
 * Sets the Editable property for "gtkEntry_PasswordRulesSet_Upper"
 * @param editable The editable property
 */
void gtkEntryPasswordRulesSetUpperSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Upper", editable);
}

/**
 * Sets the value and the check from ptPassgenConf to gtkEntry_PasswordRulesSet_Upper
 * Calls gtkEntryPasswordRulesInit
 */
void gtkEntryPasswordRulesSetUpperInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Upper", ptPassgenConf->upperCaseRule.val, ptPassgenConf->upperCaseRule.chkBox);
}

/**
 * Returns the value of the limit from gtkEntry_PasswordRulesSet_Upper
 * @return The value of the limit
 */
int gtkEntryPasswordRulesSetUpperGetVal(void)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordRulesSet_Upper"));
	return atoi(gtk_entry_get_text(gtkEntryPasswordRules));
}

/* ***********************************************************
 * gtkCheckButton_PasswordRulesSet_Upper
 *********************************************************** */

/**
 * Returns the Active state for gtkCheckButton_PasswordRulesSet_Upper"
 * @return True if the CheckButton of Number is Active, otherwise False
 */
gboolean gtkCheckButtonPasswordRulesSetUpperGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Upper");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Upper
 * It calls gtkCheckButtonPasswordRulesLast, gtkCheckButtonPasswordRulesGetActive, gtkCheckButtonPasswordRulesToggled
 * If it is the las active checkbox, prevents deactivating
 * Prints Status message for status level NORMAL
 */
void gtkCheckButtonPasswordRulesSetUpperToggled(void)
{
	if (gtkCheckButtonPasswordRulesLast(UPPER))
	{
		if (!gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Upper"))
		{
			printStatus(NORMAL, "Warning: At least One of the Check Buttom for Password Rules Set must be Active. Upper case Check is kept active");
			if (__DEBUG__) TRACE(status, "");
			gtkCheckButtonPasswordRulesSetActive("gtkCheckButton_PasswordRulesSet_Upper");
		}
		return;
	}
	gtkCheckButtonPasswordRulesToggled("gtkCheckButton_PasswordRulesSet_Upper", "gtkEntry_PasswordRulesSet_Upper");
}

/**
 * Sets the check from ptPassgenConf to gtkCheckButton_PasswordRulesSet_Upper
 * Calls gtkCheckButtonPasswordRulesInit
 */
void gtkCheckButtonPasswordRulesSetUpperInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkCheckButtonPasswordRulesInit("gtkCheckButton_PasswordRulesSet_Upper", ptPassgenConf->upperCaseRule.chkBox);
}

/* ***********************************************************
 * Generic Functions
 *********************************************************** */

/**
 * Returns the sum of all the limits of the characters sets, whether activated or not
 * @returns The sum of all the limits of the characters sets
 */
int gtkSumEntryPasswordRules(void)
{
	int sum = 	gtkEntryPasswordRulesSetUpperGetVal() +
				gtkEntryPasswordRulesSetLowerGetVal() +
				gtkEntryPasswordRulesSetNumberGetVal() +
				gtkEntryPasswordRulesSetSymbolGetVal();

	return sum;
}

/**
 * Returns the value of the limit of the charSetGroup characters set if is activated
 * @returns The value of the limit of the charSetGroup characters set if is activated, otherwise 0
 */
int gtkGetActiveEntryPasswordRuleValue(int charSetGroup)
{
	int value = 0;
	switch (charSetGroup)
	{
	case UPPER:
		if (gtkCheckButtonPasswordRulesSetUpperGetActive())
			value = gtkEntryPasswordRulesSetUpperGetVal();
		break;
	case LOWER:
		if (gtkCheckButtonPasswordRulesSetLowerGetActive())
			value = gtkEntryPasswordRulesSetLowerGetVal();
		break;
	case NUMBER:
		if (gtkCheckButtonPasswordRulesSetNumberGetActive())
			value = gtkEntryPasswordRulesSetNumberGetVal();
		break;
	case SYMBOL:
		if (gtkCheckButtonPasswordRulesSetSymbolGetActive())
			value = gtkEntryPasswordRulesSetSymbolGetVal();
		break;
	}
	return value;
}

/**
 * Returns the sum of all the limits of the activated characters sets
 * @returns The sum of the limits of the activated characters sets
 */
int gtkSumActiveEntryPasswordRules(void)
{
	int sum = 0;

	for (int charSetGroup = UPPER; charSetGroup < LAST_SET; ++charSetGroup)
	{
		sum += gtkGetActiveEntryPasswordRuleValue(charSetGroup);
	}

	return sum;
}

/**
 * Returns the sum of the limits of the activated characters sets different from charSetGroup
 * @param charSetGroup The characters set's id to skip in the sum
 * @returns The sum of the limits of the activated characters sets different from charSetGroup
 */
int gtkSumRestActiveEntryPasswordRules(int charSetGroup)
{
	int totalSum = gtkSumActiveEntryPasswordRules();
	totalSum -= gtkGetActiveEntryPasswordRuleValue(charSetGroup);
	if (__DEBUG__) TRACE("totalSum - %s: %d", decodeGroupType(charSetGroup), totalSum);
	return totalSum;
}


