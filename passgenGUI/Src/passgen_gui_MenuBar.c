/*
 * passgen_gui_MenuBar.c
 *
 *  Created on: 12 mar. 2023
 *      Author: ipserc
 */

#include "passgen_gui_MenuBar.h"

#define __DEBUG__ false

/* ***********************************************************
 * gtkMenuBar_passgen
 *********************************************************** */

/**
 *
 */
void gtkMenuItemFileLoadActivate(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();
	passgenConfigRead(ptPassgenConf);

	if (__DEBUG__) printPassgenConfig();

	gtkInitPassgen();
}

/**
 *
 */
void gtkMenuItemFileSaveActivate(void)
{
	passgenConf_t * ptPassgenConf = getPassgenConf();

	if (!gtkCheckRules())
	{
		printStatus(BASIC, "ERROR - There are errors in the configuration data. Configuration saving operation has been aborted");
		return;
	}

	//createPassgenConf(char * pgnHome, passgenConf_t * ptPassgenConf)
	if (writePassgenConfig(passgenPath(ptPassgenConf)))
	{
		printStatus(BASIC, "%s Configuration File saved successfully", genpassProgramName());
	}
}

/**
 *
 */
void gtkMenuItemStatusLevelSetLabel(int level)
{
	char labeltextHead[20] = "Status Info";
	char labelText[40];

	GtkFrame * gtkFrameStatusInfo = GTK_FRAME(gtk_builder_get_object(getGtkBuilder(), "gtkFrame_StatusInfo"));

	switch (level)
	{
		case BASIC:
			sprintf(labelText, "%s %s", labeltextHead, "Basic");
			break;
		case NORMAL:
			sprintf(labelText, "%s %s", labeltextHead, "Normal");
			break;
		case HIGH:
			sprintf(labelText, "%s %s", labeltextHead, "High");
			break;
	}

	gtk_frame_set_label(gtkFrameStatusInfo, labelText);
	statusLevel = level;
}

/**
 *
 */
void gtkMenuItemStatusLevelBasicActivate(void)
{
	gtkMenuItemStatusLevelSetLabel(BASIC);
}

/**
 *
 */
void gtkMenuItemStatusLevelNormalActivate(void)
{
	gtkMenuItemStatusLevelSetLabel(NORMAL);
}

/**
 *
 */
void gtkMenuItemStatusLevelHighActivate(void)
{
	gtkMenuItemStatusLevelSetLabel(HIGH);
}

/**
 * Creates a group and join the GtkRadioMenuItem in it
 * Not required. Implemented in Glade
 */
void gtkMenuItemStatusGroupSet(void)
{
	GtkRadioMenuItem * gtkMenuItemStatusLevelBasic = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_StatusLevel_Basic"));
	gtk_radio_menu_item_join_group(gtkMenuItemStatusLevelBasic, (GtkRadioMenuItem *)NULL);

	GtkRadioMenuItem * gtkMenuItemStatusLevelNormal = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_StatusLevel_Normal"));
	gtk_radio_menu_item_join_group(gtkMenuItemStatusLevelNormal, gtkMenuItemStatusLevelBasic);

	GtkRadioMenuItem * gtkMenuItemStatusLevelHigh = GTK_RADIO_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_StatusLevel_High"));
	gtk_radio_menu_item_join_group(gtkMenuItemStatusLevelHigh, gtkMenuItemStatusLevelNormal);
}
