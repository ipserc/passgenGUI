/*
 * passgen_gui.c
 *
 *  Created on: 13 feb. 2023
 *      Author: ipserc
 */

#include "passgen_gui.h"

#define __DEBUG__ false

/**
 * Static "private method" to set or get the GtkBuilder * gtkbuilder static variable. DO NOT CALL IT DIRECTLY use getGtkBuilder() to get it
 * @param method Selector for (0) set or get the GtkBuilder
 * @return static GtkBuilder * gtkbuilder
 */
/* private */ static GtkBuilder * gtkbuilder(int method)
{
	static GtkBuilder * gtkbuilder = NULL;

	if (method == 0)	//SET
	{
		/*
		 * To load the GUI from the file ../config/passgenm.glade use this
		 */
		//gtkbuilder = gtk_builder_new_from_file("../config/passgen.glade");
		/*
		 * To load the GUI from passgenm_glade.c use this
		 */
		gtkbuilder = gtk_builder_new_from_string(getGtkSource(), -1);
	}
	return gtkbuilder;
}

/**
 * Sets GtkBuilder * gtkbuilder pointer. Use it to create it
 * @return static GtkBuilder * gtkbuilder
 */
GtkBuilder * setGtkBuilder(void)
{
	return gtkbuilder(0);
}

/**
 * Returns the GtkBuilder * gtkbuilder static variable
 * @return static GtkBuilder * gtkbuilder
 */
GtkBuilder * getGtkBuilder(void)
{
	return gtkbuilder(1);
}

/**
 *
 */
static GtkClipboard * gtkclipboard(int method)
{
	static GtkClipboard * clipboard = NULL;

	if (method == 0)	//SET
	{
		clipboard = gtk_clipboard_get(GDK_SELECTION_CLIPBOARD);
	}

	return clipboard;
}

/**
 *
 */
GtkClipboard * setClipboard(void)
{
	return gtkclipboard(0);
}

/**
 *
 */
GtkClipboard * getClipboard(void)
{
	return gtkclipboard(1);
}

/**
 *
 */
user_data_t * gtkUserData(void)
{
	static user_data_t user_datav;
	user_data_t * gtkUserData = &user_datav;
	return gtkUserData;
}


/**
 * Catches the SIGTERM signal to perform an orderly program exit
 * Used by passgenmGUI only
 * https://www.systutorials.com/catching-the-signal-sent-by-kill-in-c-on-linux/
 * https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
 */
void catchSigterm()
{
    static struct sigaction _sigact;

    memset(&_sigact, 0, sizeof(_sigact));
    // _sigact.sa_sigaction = (void *)gtkClosePassgen;
    _sigact.sa_flags = SA_SIGINFO;

    sigaction(SIGTERM, &_sigact, NULL);
    // sigaction(SIGKILL, &_sigact, NULL); SIGKILL cannot be catched
}

/**
 * Sets the cursor with one of the types defined in http://developer.gimp.org/api/2.0/gdk/gdk-Cursors.html
 * Typically normal cursor or hour glass
 * @param cursorType the type of cursor as in http://developer.gimp.org/api/2.0/gdk/gdk-Cursors.html
 */
void gtkSetCursor(GdkCursorType cursorType)
{
	GdkScreen * screen = gdk_screen_get_default();
	GdkWindow * win = gdk_screen_get_root_window(screen);
	GdkDisplay * display = gdk_display_get_default();
	GdkCursor * cursor = gdk_cursor_new_for_display(display, cursorType); //http://developer.gimp.org/api/2.0/gdk/gdk-Cursors.html
	gdk_window_set_cursor(win, cursor);
	while (gtk_events_pending()) gtk_main_iteration();
}

/**
 * Required tasks for closing passgen
 */
void gtkClosePassgen(void)
{
	if (__DEBUG__) TRACE("gtkClosePassgen", "");
	gtkSetCursor(NORMAL_CURSOR);
	gtk_main_quit();
}

/**
 * Passgen File Quit menu callback
 * @param menuConfigQuit
 * @param user_data
 */
void gtkPassgenFileQuit(GtkImageMenuItem * fileQuit, gpointer user_data)
{
	if (__DEBUG__) TRACE("gtkPassgenFileQuit signal:%s", ((user_data_t *)user_data)->signal);
	gtkClosePassgen();
}

/**
 *
 */
void gtkWidgetSetEditable(GtkWidget * gtkWidget, gboolean editable)
{
	if (editable)
	{
		gtk_widget_set_sensitive(	(GtkWidget *) gtkWidget,
									(GtkStateType) GTK_STATE_INSENSITIVE);
	}
	else
	{
		gtk_widget_set_sensitive(	(GtkWidget *) gtkWidget,
									(GtkStateType) GTK_STATE_NORMAL);
	}
}

/* ***********************************************************
 * gtk Generic Porpouse Functions
 *********************************************************** */

/**
 * Reads the status and values of the Password Rules Set Frame from the GUI and put them inside the passgenConf system variable
 */
void passgenGtkSettings2PassgenConf(void)
{
	if (__DEBUG__) TRACE("START of passgenGtkSettings2PassgenConf()", "");

	passgenConf_t * ptPassgenConf = getPassgenConf();

	/* Password Length Preset*/
	GtkComboBoxText * gtkComboBoxTextPasswordLengthPreset = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(getGtkBuilder(), "gtkComboBoxText_PasswordLengthPreset"));
	int presetIdx = gtk_combo_box_get_active((GtkComboBox *) gtkComboBoxTextPasswordLengthPreset);
	sprintf(ptPassgenConf->passwordLength.preset, "%s",  getPasswordLengthPresetsName(presetIdx));

	/* Password Length Size */
	if (presetIdx == USER) ptPassgenConf->passwordLength.user = gtkEntryPasswordLengthSizeGet();
	else ptPassgenConf->passwordLength.size = gtkEntryPasswordLengthSizeGet(); // Can be done with this getPasswordLengthPresetsSize(presetIdx);

	if (__DEBUG__)
	{
		TRACE("presetIdx: %d", presetIdx);
		TRACE("preset: %s", getPasswordLengthPresetsName(presetIdx));
		TRACE("ptPassgenConf->passwordLength.user: %d", ptPassgenConf->passwordLength.user);
		TRACE("ptPassgenConf->passwordLength.size: %d", ptPassgenConf->passwordLength.size);
	}

	/* Password Rules Set */
	/* *** UPPER CASE *** */
	ptPassgenConf->upperCaseRule.chkBox = gtkCheckButtonPasswordRulesSetUpperGetActive();
	ptPassgenConf->upperCaseRule.val = gtkEntryPasswordRulesSetUpperGetVal();

	/* *** LOWER CASE *** */
	ptPassgenConf->lowerCaseRule.chkBox = gtkCheckButtonPasswordRulesSetLowerGetActive();
	ptPassgenConf->lowerCaseRule.val = gtkEntryPasswordRulesSetLowerGetVal();

	/* ***  NUMBER   *** */
	ptPassgenConf->numberCaseRule.chkBox = gtkCheckButtonPasswordRulesSetNumberGetActive();
	ptPassgenConf->numberCaseRule.val = gtkEntryPasswordRulesSetNumberGetVal();

	/* ***  SYMBOL   *** */
	ptPassgenConf->symbolCaseRule.chkBox = gtkCheckButtonPasswordRulesSetSymbolGetActive();
	ptPassgenConf->symbolCaseRule.val = gtkEntryPasswordRulesSetSymbolGetVal();

	if (__DEBUG__) TRACE("END of passgenGtkSettings2PassgenConf()", "");
}

/**
 * Does the required work to generate the password from the GUI
 */
void gtkPasswordGenerate(void)
{
	if (__DEBUG__) TRACE("START of gtkPasswordGenerate()", "");

	gtkEntryPasswordTextClear();
	gtkTextViewStatusClear();

	if (__DEBUG__) TRACE("About to generate the new password", "");

	char * newPass = passgenConf2Rules();
	if (__DEBUG__) TRACE("newPass Address %p", newPass);

	gtkEntryPasswordTextSet(genPass(newPass));

	free(newPass);

	if (__DEBUG__) TRACE("END of gtkPasswordGenerate()", "");
}

/**
 * Checks the given rules to generate the password and reports on the errors detected
 */
gboolean _gtkCheckPasswordRules(void)
{
	int sumActiveEntryPasswordRules = gtkSumActiveEntryPasswordRules();

	if (__DEBUG__)
	{
		TRACE("PASS_LEN: %d", PASS_LEN);
		TRACE("gtkSumActiveEntryPasswordRules: %d", sumActiveEntryPasswordRules);
	}

	if (PASS_LEN < sumActiveEntryPasswordRules)
	{
		printStatus(BASIC, "The given rules cannot be applied to the password. The number of characters to be set by the rules exceeds the size of the password");
		return false;
	}
	printStatus(BASIC, "The rules given can be applied to the password generation");
	return true;
}

/**
 * Shortcut for passgen.c checkPasswordRules()
 * Modify the used method here  to propagate it for all the source code
 */
gboolean gtkCheckPasswordRules(void)
{
	return checkPasswordRules();
}

/**
 * Shortcut for passgen.c checkGrpChrLimit
 * Modify the used method here  to propagate it for all the source code
 */
gboolean gtkCheckGrpChrLimit(int charSetGroup, int value)
{
	return checkGrpChrLimit(charSetGroup, value);
}

/**
 * Puts the values defined in the GUI to generate the password in the variables used by the password generation engine
 */
void passgenConfRulesValuesSet(void)
{
	if (__DEBUG__)
	{
		TRACE("START passgenConfRulesValuesSet(void)", "");
		TRACE("CALL initGrpChrLimit()", "");
	}
	initGrpChrLimit();

	if (__DEBUG__) TRACE("CALL initExcludedGroups()", "");
	initExcludedGroups();

	if (__DEBUG__) TRACE("CALL passgenGtkSettings2PassgenConf()", "");
	passgenGtkSettings2PassgenConf();

	if (__DEBUG__) TRACE("CALL setPassgenConfCaseRule2Values()", "");
	setPassgenConfCaseRule2Values();

	if (__DEBUG__) TRACE("CONTINUE gtkCheckRules(void)", "");

	if(__DEBUG__)
	{
		traceGrpChrExcluded();
		TRACE("END passgenConfRulesValuesSet(void)", "");
	}
}

/**
 *
 */
gboolean gtkCheckRules(void)
{
	int value;
	int statusLevelBackup = statusLevel;
	gboolean checkRulesOk = true;

	if (__DEBUG__) TRACE("START gtkCheckRules(void)", "");

	statusLevel = HIGH;

	gtkEntryPasswordTextClear();
	gtkTextViewStatusClear();
	passgenGtkSettings2PassgenConf();
	passgenConfRulesValuesSet();
	printExcludedGroups();

	if (PASS_LEN <= 0)
	{
		printStatus(BASIC, "ERROR - Wrong password size. Password size MUST be greater than 1. The current password size is %d", PASS_LEN);
		printStatus(BASIC, "To be able generate a password, correct this error ");
		return false;
	}

	checkRulesOk = gtkCheckPasswordRules();

	if (!checkRulesOk)
	{
		printStatus(BASIC, "You should review the Passwords Rules to fix the following:");
		for (int charSetGroup = UPPER; charSetGroup < LAST_SET; ++charSetGroup)
		{
			value = gtkGetActiveEntryPasswordRuleValue(charSetGroup);

			// value == 0 means CarSetGroup not active
			if (value == 0) continue;

			if (__DEBUG__) TRACE("Group Char %s Value: %d", decodeGroupType(charSetGroup), value);

			if (!gtkCheckGrpChrLimit(charSetGroup, value) && value > ceil(PASS_LEN / 4.0))
				printStatus(BASIC, "ATENTION - Review this Rule to fix the problem");

		}
	}

	statusLevel = statusLevelBackup;

	return checkRulesOk;
}

/* ***********************************************************
 * gtkTextView_Trace
 *********************************************************** */

/**
 * gtk_text_tag_table_new () https://www.manpagez.com/html/gtk/gtk-3.12.2/GtkTextTagTable.php#gtk-text-tag-table-new
 * gtk_text_buffer_new () https://www.manpagez.com/html/gtk/gtk-3.12.2/GtkTextBuffer.php#gtk-text-buffer-new
 * gtk_text_view_set_buffer () https://www.manpagez.com/html/gtk/gtk-3.12.2/GtkTextView.php#gtk-text-view-set-buffer
 */

/* ***********************************************************
 * gtk Init Passgen
 * gtk Signals Connect
 *********************************************************** */

/**
 * Does the required actions to initialize passgen from the GUI
 */
void gtkInitPassgen(void)
{
	if (__DEBUG__) TRACE("statusLevel: %s", getCurrentStatusName());

	gtkMenuItemStatusLevelSetLabel(statusLevel);

	setClipboard();

	gtkComboBoxTextPasswordLengthPresetInit();
	gtkEntryPasswordLengthInit();

	gtkCheckButtonPasswordRulesSetUpperInit();
	gtkEntryPasswordRulesSetUpperInit();

	gtkCheckButtonPasswordRulesSetLowerInit();
	gtkEntryPasswordRulesSetLowerInit();

	gtkCheckButtonPasswordRulesSetSymbolInit();
	gtkEntryPasswordRulesSetSymbolInit();

	gtkCheckButtonPasswordRulesSetNumberInit();
	gtkEntryPasswordRulesSetNumberInit();

	gtkEntryPasswordTextInit();

	gtkTextViewStatusClear();
}

/**
 * GTK Signals Connect function
 */
void gtkSignalsConnect(void)
{
	GtkWidget * passgenmMainWindow = GTK_WIDGET(gtk_builder_get_object(getGtkBuilder(), "gtkDialog_passgen"));
	g_signal_connect(G_OBJECT(passgenmMainWindow), "destroy", G_CALLBACK(gtkClosePassgen), (gpointer)NULL);

	GtkWidget * fileQuit = GTK_WIDGET(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_FileQuit"));
	sprintf(gtkUserData()->signal, "%s", "activate");
	g_signal_connect(G_OBJECT(fileQuit), "activate", G_CALLBACK(gtkPassgenFileQuit), (gpointer)gtkUserData());

	GtkWidget * gtkComboBoxTextPasswordLengthPreset = GTK_WIDGET(gtk_builder_get_object(getGtkBuilder(), "gtkComboBoxText_PasswordLengthPreset"));
	g_signal_connect(G_OBJECT(gtkComboBoxTextPasswordLengthPreset), "changed", G_CALLBACK(gtkComboBoxTextPasswordLengthPresetChanged), (gpointer)NULL);

	GtkCheckButton * gtkCheckButtonPasswordRulesSetUpper = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), "gtkCheckButton_PasswordRulesSet_Upper"));
	g_signal_connect(G_OBJECT(gtkCheckButtonPasswordRulesSetUpper), "toggled", G_CALLBACK(gtkCheckButtonPasswordRulesSetUpperToggled), (gpointer)NULL);

	GtkCheckButton * gtkCheckButtonPasswordRulesSetLower = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), "gtkCheckButton_PasswordRulesSet_Lower"));
	g_signal_connect(G_OBJECT(gtkCheckButtonPasswordRulesSetLower), "toggled", G_CALLBACK(gtkCheckButtonPasswordRulesSetLowerToggled), (gpointer)NULL);

	GtkCheckButton * gtkCheckButtonPasswordRulesSetSymbol = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), "gtkCheckButton_PasswordRulesSet_Symbol"));
	g_signal_connect(G_OBJECT(gtkCheckButtonPasswordRulesSetSymbol), "toggled", G_CALLBACK(gtkCheckButtonPasswordRulesSetSymbolToggled), (gpointer)NULL);

	GtkCheckButton * gtkCheckButtonPasswordRulesSetNumber = GTK_CHECK_BUTTON(gtk_builder_get_object(getGtkBuilder(), "gtkCheckButton_PasswordRulesSet_Number"));
	g_signal_connect(G_OBJECT(gtkCheckButtonPasswordRulesSetNumber), "toggled", G_CALLBACK(gtkCheckButtonPasswordRulesSetNumberToggled), (gpointer)NULL);

	GtkButton * gtkButtonPasswordCopy = GTK_BUTTON(gtk_builder_get_object(getGtkBuilder(), "gtkButton_Password_Copy"));
	g_signal_connect(G_OBJECT(gtkButtonPasswordCopy), "clicked", G_CALLBACK(gtkEntryPasswordTextCopy), (gpointer)NULL);

	GtkButton * gtkButtonPasswordGenerate = GTK_BUTTON(gtk_builder_get_object(getGtkBuilder(), "gtkButton_Generate"));
	g_signal_connect(G_OBJECT(gtkButtonPasswordGenerate), "clicked", G_CALLBACK(gtkPasswordGenerate), (gpointer)NULL);

	GtkButton * gtkButtonCheckRules = GTK_BUTTON(gtk_builder_get_object(getGtkBuilder(), "gtkButton_CheckRules"));
	g_signal_connect(G_OBJECT(gtkButtonCheckRules), "clicked", G_CALLBACK(gtkCheckRules), (gpointer)NULL);

	GtkMenuItem * gtkMenuItemFileLoad = GTK_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_FileLoad"));
	g_signal_connect(G_OBJECT(gtkMenuItemFileLoad), "activate", G_CALLBACK(gtkMenuItemFileLoadActivate), (gpointer)NULL);

	GtkMenuItem * gtkMenuItemFileSave = GTK_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_FileSave"));
	g_signal_connect(G_OBJECT(gtkMenuItemFileSave), "activate", G_CALLBACK(gtkMenuItemFileSaveActivate), (gpointer)NULL);

	GtkMenuItem * gtkMenuItemEditCopy = GTK_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_EditCopy"));
	g_signal_connect(G_OBJECT(gtkMenuItemEditCopy), "activate", G_CALLBACK(gtkEntryPasswordTextCopy), (gpointer)NULL);

	GtkMenuItem * gtkMenuItemStatusLevelBasic = GTK_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_StatusLevel_Basic"));
	g_signal_connect(G_OBJECT(gtkMenuItemStatusLevelBasic), "activate", G_CALLBACK(gtkMenuItemStatusLevelBasicActivate), (gpointer)NULL);

	GtkMenuItem * gtkMenuItemStatusLevelNormal = GTK_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_StatusLevel_Normal"));
	g_signal_connect(G_OBJECT(gtkMenuItemStatusLevelNormal), "activate", G_CALLBACK(gtkMenuItemStatusLevelNormalActivate), (gpointer)NULL);

	GtkMenuItem * gtkMenuItemStatusLevelHigh = GTK_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_StatusLevel_High"));
	g_signal_connect(G_OBJECT(gtkMenuItemStatusLevelHigh), "activate", G_CALLBACK(gtkMenuItemStatusLevelHighActivate), (gpointer)NULL);

	GtkMenuItem * gtkMenuItemHelpAbout = GTK_MENU_ITEM(gtk_builder_get_object(getGtkBuilder(), "gtkMenuItem_HelpAbout"));
	g_signal_connect(G_OBJECT(gtkMenuItemHelpAbout), "activate", G_CALLBACK(gtkMenuItemHelpAboutShow), (gpointer)NULL);
}

