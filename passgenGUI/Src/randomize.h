/*
 * randomize.h
 *
 *  Created on: 9 feb. 2023
 *      Author: ipserc
 *      Version: randomizeVersion
 */

#ifndef RANDOMIZE_H_
#define RANDOMIZE_H_

#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include <string.h>
#include <stdbool.h>

/* PROTOTYPES */
/* randomize.c */
char *getRandomizeVersion(void);
void putsRandomizeVersion(void);
int naturalRandomNbr(int max);
int integerRandomNbr(int max);
double doubleRandomNbr(double max);
void initRandomSeed(void);
void randomize(void);
void chekNaturalRandomRange(int max, int checkIterations);
void chekIntegerRandomRange(int max, int checkIterations);
void chekDoubleRandomRange(double max, int checkIterations);
void testRandomFunction(void);

#endif /* RANDOMIZE_H_ */
