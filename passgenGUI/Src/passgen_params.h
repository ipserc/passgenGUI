/*
 * passgen_params.h
 *
 *  Created on: 22 feb. 2023
 *      Author: ipserc
 */

#ifndef SRC_PASSGEN_PARAMS_H_
#define SRC_PASSGEN_PARAMS_H_

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

/**
 * options
 * --nogui		-g	no GUI, command line mode
 * --help		-h	help
 * --config		-c	dumps the configuration on the screen.
 * --version	-V	prints zhavam version.
 */

typedef struct
{
	bool nogui;
	bool help;
	bool config;
	bool version;
	bool buffer;
} psgParams_t;

/* PROTOTYPES */
/* passgen_params.c */
void passgenHelp(void);
psgParams_t *setPsgParams(void);
psgParams_t *getPsgParams(void);
psgParams_t *readPsgParams(int argc, char *argv[]);

#endif /* SRC_PASSGEN_PARAMS_H_ */
