/*
 * passgen_params.c
 *
 *  Created on: 22 feb. 2023
 *      Author: ipserc
 */


#include "passgen_params.h"

/**
 * Prints the usage on screen
 */
void passgenHelp(void)
{
	puts("Usage: passgen [OPTION]... ");
	puts("Easy passwords generator.\n");
	puts("Abstract");
	puts("passgen generates passwords of length given by the user.");
	puts("The passwords will follow some rules based in sets of characters.");
	puts("The sets of characters are Upper Case, Lower Case, Numbers and Symbols.");
	puts("The rules induces to use at least the numbre of characters given for");
	puts("Upper Case, Lower Case, Numbers. For Symbols the number of characters is");
	puts("exact as the number given");
	puts("At least ONE set of characters must be active.\n");
	puts("Options");
	puts("Do not use any option to display the graphical interface.");
	puts("	-g, --nogui	no GUI, Command Line Interface mode.");
	puts("	-h, --help	shows this help.");
	puts("	-c, --config	dumps the configuration on the screen.");
	puts("	-V, --version	prints passgen version.");
	puts("passgen on Github at https://github.com/ipserc/passgen");
	puts("You can report any bug at passgen's Github homepage");
}

/**
 * options
 * --nogui		-g	no GUI, Command Line Interface mode
 * --loop		-l	loop mode. Press ctrl-c to quit
 * --help		-h	help
 * --config		-c	dumps the configuration on the screen.
 * --buffer		-b	writes pcm buffer (forces the no GUI mode)
 * --version	-V	prints passgen version.
 */
/**
 * Static "private method" to create or get the psgParams_t * psgParams static variable. DO NOT CALL IT DIRECTLY
 * @param method Selector for (0) create a new instance or returning the one created
 * @return A pointer to static psgParams_t psgParams
 */
/* private */static psgParams_t * psgParams(int method)
{
	static psgParams_t psgParams;

	if (method == 0)	//SET
	{
		psgParams.nogui 	= false;
		psgParams.help 		= false;
		psgParams.config	= false;
		psgParams.buffer	= false;
		psgParams.version	= false;
	}
	return (psgParams_t *)&psgParams;
}

/**
 * Sets psgParams_t psgParams pointer. Use it to create it
 * @return A pointer to static psgParams_t psgParams
 */
psgParams_t * setPsgParams(void)
{
	return psgParams(0);
}

/**
 * Returns a pointer to static psgParams_t psgParams static variable
 * @return A pointer to static psgParams_t psgParams
 */
psgParams_t * getPsgParams(void)
{
	return psgParams(1);
}

/**
 * Reads the params passed from the command line
 * @param argc
 * @param argv[]
 * @return The psgParams_t structure filled up
 */
psgParams_t * readPsgParams(int argc, char * argv[])
{
	static struct option long_options[] =
	{
		{"nogui",	no_argument,	0,	'g'},
		{"help",  	no_argument,	0,	'h'},
		{"config",	no_argument,	0,	'c'},
		{"version",	no_argument,	0,	'V'},
		{0, 0, 0, 0}
	};
	int c, option_index = 0;
	psgParams_t * psgParams = setPsgParams();
	while ((c = getopt_long (argc, argv, "ghcV", long_options, &option_index)) != -1)
	{
		switch (c)
		{
		  case 'h':
			  psgParams->help = true;
			  break;
		  case 'c':
			  psgParams->config = true;
			  break;
		  case 'V':
		  	  psgParams->version = true;
		  	  break;
		  case 'g':
			  psgParams->nogui = true;
			  break;
		}
	}
	return psgParams;
}


