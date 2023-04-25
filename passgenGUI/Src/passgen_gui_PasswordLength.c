/*
 * passgen_gui_PasswordLength.c
 *
 *  Created on: 21 feb. 2023
 *      Author: ipserc
 */

#include "passgen_gui_PasswordLength.h"

#define __DEBUG__ false

/**
 * It is only a test
 */
void ptrTest(void)
{
	int test = 4;
	void * ptrTest = &test;
	if (__DEBUG__) TRACE("test    : %d", test);
	if (__DEBUG__) TRACE("*ptrTest: %d", (int)*(int *)ptrTest);
	*(int *)ptrTest = 8;
	if (__DEBUG__) TRACE("test    : %d", test);
	if (__DEBUG__) TRACE("*ptrTest: %d", (int)*(int *)ptrTest);
}

/* ***********************************************************
 * gtkEntry_PasswordLengthSize
 *********************************************************** */

/**
 * Returns the value of the password length size
 * @return The password length size
 */
int gtkEntryPasswordLengthSizeGet(void)
{
	GtkEntry * gtkEntryPasswordLengthSize = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordLengthSize"));
	return atoi(gtk_entry_get_text(gtkEntryPasswordLengthSize));
}

/**
 * Enables or disables the attribute editable of gtkEntry_PasswordLengthSize
 * @param editable The value true or false of the editable attribute
 */
void gtkEntryPasswordLengthSizeEditable(gboolean editable)
{
	GtkEntry * gtkEntryPasswordLengthSize = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordLengthSize"));
	gtkWidgetSetEditable((GtkWidget *) gtkEntryPasswordLengthSize, editable);
}

/**
 * Updates gtkEntry_PasswordLengthSize with the value passed
 * @param value The text that to set in gtkEntry_PasswordLengthSize
 */
void gtkEntryPasswordLengthSizeUpdate(const gchar * value)
{
	GtkEntry * gtkEntryPasswordLengthSize = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordLengthSize"));

	if (__DEBUG__)
	{
		TRACE("gtk_entry_get_value_as_int: %s", gtk_entry_get_text((GtkEntry *) gtkEntryPasswordLengthSize));
		TRACE("lookupPassgenConfig(passwordLengthSize): %s", value);
	}

	gtk_entry_set_text((GtkEntry *) gtkEntryPasswordLengthSize, (const gchar *) value);
}

/**
 * Initializes gtkEntry_PasswordLengthSize with the value of the password preset
 */
void gtkEntryPasswordLengthInit(void)
{
	int Size;
	char strSize[4];

	GtkEntry * gtkEntryPasswordLengthSize = GTK_ENTRY(gtk_builder_get_object(getGtkBuilder(), "gtkEntry_PasswordLengthSize"));
	Size = passwordLengthPresetIdSize(passwordLengthPreset);

	if (__DEBUG__) TRACE("Entry Size:%d", Size);

	sprintf(strSize, "%d", Size);
	gtk_entry_set_text(	(GtkEntry *) gtkEntryPasswordLengthSize, (const gchar *) strSize );
}

/* ***********************************************************
 * gtkComboBoxText_PasswordLengthPreset
 *********************************************************** */

/**
 * Executes the actions required when the gtkComboBoxText_PasswordLengthPreset changes its value
 * Calls gtkEntryPasswordLengthSizeEditable, passwordLengthPresetIdSize and gtkEntryPasswordLengthSizeUpdate
 */
void gtkComboBoxTextPasswordLengthPresetChanged(void)
{
	int presetSize;
	char strPresetSize[4];

	GtkComboBoxText * gtkComboBoxTextPasswordLengthPreset = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(getGtkBuilder(), "gtkComboBoxText_PasswordLengthPreset"));

	preset_idx presetId = gtk_combo_box_get_active((GtkComboBox *)gtkComboBoxTextPasswordLengthPreset);
	if (presetId == USER) gtkEntryPasswordLengthSizeEditable(true);
	else gtkEntryPasswordLengthSizeEditable(false);

	presetSize = passwordLengthPresetIdSize(presetId);
	sprintf(strPresetSize, "%d", presetSize);
	gtkEntryPasswordLengthSizeUpdate((const gchar *) strPresetSize);
}

/**
 * Initializes the gtkComboBoxText_PasswordLength with the values from getPasswordLengthPresetsName
 */
void gtkComboBoxTextPasswordLengthPresetInit(void)
{
	char id[2]; // The const gchar* id of gtk_combo_box_text_append. No more than 9 presets, please!!!!
	passgenConf_t * ptPassgenConf = getPassgenConf();

	GtkComboBoxText * gtkComboBoxTextPasswordLengthPreset = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(getGtkBuilder(), "gtkComboBoxText_PasswordLengthPreset"));

	// gtkComboBoxTextPasswordLength
	gtk_combo_box_text_remove_all((GtkComboBoxText *) gtkComboBoxTextPasswordLengthPreset);
	for(int passLenIdx = USER; passLenIdx < LAST_PRESET; ++passLenIdx)
	{
		if (__DEBUG__) TRACE("gtkComboBoxTextPasswordLengthPresetInit(%d):%s", passLenIdx, getPasswordLengthPresetsName(passLenIdx));

		sprintf(id, "%d", passLenIdx);
		gtk_combo_box_text_append(	(GtkComboBoxText *) gtkComboBoxTextPasswordLengthPreset,
									(const gchar*) id,
									(const gchar*) getPasswordLengthPresetsName(passLenIdx));
	}

	if (__DEBUG__) TRACE("getPasswordLengthPresetsNameIdx(%s):%d", ptPassgenConf->passwordLength.preset, getPasswordLengthPresetsNameIdx(ptPassgenConf->passwordLength.preset));

	gtk_combo_box_set_active(	(GtkComboBox *) gtkComboBoxTextPasswordLengthPreset,
								getPasswordLengthPresetsNameIdx(ptPassgenConf->passwordLength.preset));
								//getPasswordLengthPresetsNameIdx((char *) lookupPassgenConfig(passwordLengthPreset))); Another valid way to get it

	preset_idx presetId = gtk_combo_box_get_active((GtkComboBox *) gtkComboBoxTextPasswordLengthPreset);
	if (presetId == USER) gtkEntryPasswordLengthSizeEditable(true);
	else gtkEntryPasswordLengthSizeEditable(false);
}
