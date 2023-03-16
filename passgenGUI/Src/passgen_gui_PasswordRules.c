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
 * Sets the Editable property for "gtkEntry_PasswordRulesr"
 */
void gtkEntryPasswordRulesSetEditable(char * gtkEntryName, gboolean editable)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), gtkEntryName));
	gtkWidgetSetEditable((GtkWidget *) gtkEntryPasswordRules, editable);
}

/**
 *
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
 * Returns the Active state for gtkCheckButton_PasswordRulesSet_Upper"
 */
gboolean gtkCheckButtonPasswordRulesGetActive(char * gtkCheckButtonName)
{
	GtkCheckButton * gtkCheckButtonPasswordRules = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), gtkCheckButtonName));
	return gtk_toggle_button_get_active((GtkToggleButton *) gtkCheckButtonPasswordRules);
}

/**
 *
 */
void gtkCheckButtonPasswordRulesSetActive(char * gtkCheckButtonName)
{
	GtkCheckButton * gtkCheckButtonPasswordRules = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), gtkCheckButtonName));
	gtk_toggle_button_set_active((GtkToggleButton *) gtkCheckButtonPasswordRules, true);
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Upper
 * It does the necessary actions
 */
void gtkCheckButtonPasswordRulesToggled(char * gtkCheckButtonName, char * gtkEntryName)
{
	GtkEntry * gtkEntryPasswordRules = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), gtkEntryName));
	if (__DEBUG__) TRACE("gtkCheckButtonPasswordRulesToggled Active: %s", gtkCheckButtonPasswordRulesGetActive(gtkCheckButtonName) ? "True" : "False");
	gtkWidgetSetEditable((GtkWidget *) gtkEntryPasswordRules, gtkCheckButtonPasswordRulesGetActive(gtkCheckButtonName));
}

/**
 *
 */
void gtkCheckButtonPasswordRulesInit(char * gtkCheckButtonName, bool chkBox)
{
	GtkCheckButton * gtkCheckButtonPasswordRules = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), gtkCheckButtonName));
	if (__DEBUG__) TRACE("gtkCheckButtonPasswordRulesInit chkBox: %s", chkBox ? "True" : "False");
	gtk_toggle_button_set_active((GtkToggleButton *) gtkCheckButtonPasswordRules, chkBox);
}

/**
 *
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
 * Sets the Editable property for "gtkEntry_PasswordRulesSet_Number"
 */
void gtkEntryPasswordRulesSetNumberSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Number", editable);
}

/**
 *
 */
void gtkEntryPasswordRulesSetNumberInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Number", ptPassgenConf->numberCaseRule.val, ptPassgenConf->numberCaseRule.chkBox);
}

/**
 *
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
 * Returns the Active state for gtkCheckButton_PasswordRulesSet_Number"
 */
gboolean gtkCheckButtonPasswordRulesSetNumberGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Number");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Number
 * It does the necessary actions
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
 *
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
 */
void gtkEntryPasswordRulesSetSymbolSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Symbol", editable);
}

/**
 *
 */
void gtkEntryPasswordRulesSetSymbolInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Symbol", ptPassgenConf->symbolCaseRule.val, ptPassgenConf->symbolCaseRule.chkBox);
}

/**
 *
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
 */
gboolean gtkCheckButtonPasswordRulesSetSymbolGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Symbol");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Symbol
 * It does the necessary actions
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
 *
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
 */
void gtkEntryPasswordRulesSetLowerSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Lower", editable);
}

/**
 *
 */
void gtkEntryPasswordRulesSetLowerInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Lower", ptPassgenConf->lowerCaseRule.val, ptPassgenConf->lowerCaseRule.chkBox);
}

/**
 *
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
 */
gboolean gtkCheckButtonPasswordRulesSetLowerGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Lower");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Lower
 * It does the necessary actions
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
 *
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
 */
void gtkEntryPasswordRulesSetUpperSetEditable(gboolean editable)
{
	gtkEntryPasswordRulesSetEditable("gtkEntry_PasswordRulesSet_Upper", editable);
}

/**
 *
 */
void gtkEntryPasswordRulesSetUpperInit(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	gtkEntryPasswordRulesInit("gtkEntry_PasswordRulesSet_Upper", ptPassgenConf->upperCaseRule.val, ptPassgenConf->upperCaseRule.chkBox);
}

/**
 *
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
 */
gboolean gtkCheckButtonPasswordRulesSetUpperGetActive(void)
{
	return gtkCheckButtonPasswordRulesGetActive("gtkCheckButton_PasswordRulesSet_Upper");
}

/**
 * Manage the signal Toggled for gtkCheckButton_PasswordRulesSet_Upper
 * It does the necessary actions
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
 *
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
 *
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
 *
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
 *
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
 *
 */
int gtkSumRestActiveEntryPasswordRules(int charSetGroup)
{
	int totalSum = gtkSumActiveEntryPasswordRules();
	totalSum -= gtkGetActiveEntryPasswordRuleValue(charSetGroup);
	if (__DEBUG__) TRACE("totalSum - %s: %d", decodeGroupType(charSetGroup), totalSum);
	return totalSum;
}


