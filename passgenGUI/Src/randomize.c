/*
 ============================================================================
 Name        : randomize.c
 Author      : Ipserc
 Version     : see VERSION
 Created     : 9 feb. 2023
 Copyright   : GNU General Public License v3.0
 Description : Random number Generator for Naturals, Integers and Reals.
               Includes some functions and predefined tests
 ============================================================================
 */

#include "randomize.h"

#define VERSION "1.0.0 (2023_0209_2222)"

/**
 * Returns the version of randomize
 */
char * getRandomizeVersion(void) {
	return VERSION;
}

/**
 * Prints the version of randomize
 */
void putsRandomizeVersion(void) {
	puts(VERSION);
}

/**
 * Returns a natural random number between zero and max, both included [0, max]
 * @param max The maximum number returned
 * @return The natural random number
 */
int naturalRandomNbr(int max) {
	return rand()%(max+1);
}

/**
 * Returns an integer random number between -max and max, both included [-max, max]
 * @param max The maximum number returned in absolute value
 * @return The integer random number
 */
int integerRandomNbr(int max) {
	int nbr = naturalRandomNbr(max);
	int sgn = naturalRandomNbr(2) == 0 ? -1 : 1;
	return sgn*nbr;
}

/**
 * returns a double random number between -max and max both included [-max, max]
 * @param max The maximum number returned in absolute value
 * @return The integer random number
 */
double doubleRandomNbr(double max) {
	int sgn = naturalRandomNbr(2) == 0 ? -1 : 1;
	return sgn*drand48()*(max);
}

/**
 * Initializes the random number series with somehow difficult seed to repeat
 */
void initRandomSeed(void) {
	srand(time(0));
	// Hash the random seed for integers
	for (int i = 0; i < rand()%100; ++i) {
		srand(time(0));
	}

	// Hash the random seed for floats
	for (int i = 0; i < rand()%100; ++i) {
		srand48(time(0));
	}
}

/**
 * Makes the CPU stay busy for some operations
 */
void randomize(void) {
	for(int i = 0; i < naturalRandomNbr(1000); ++i);
}

/**
 * Checks naturalRandomRange. Does checkIterations and returns the upper and lower number given by naturalRandomNbr
 * @param max The maximum for both sides of the range [-max, max]
 * @param checkIterations The max number of iterations to reach the limit max
 */
void chekNaturalRandomRange(int max, int checkIterations) {
	int rndNbrMax, rndNbrMin, rndNbr;

	rndNbrMax = naturalRandomNbr(max);
	rndNbrMin = rndNbrMax;

	for (int i = 0; i < checkIterations; ++i) {
		rndNbr = naturalRandomNbr(max);
		rndNbrMax = rndNbrMax > rndNbr ? rndNbrMax : rndNbr;
		rndNbrMin = rndNbrMin < rndNbr ? rndNbrMin : rndNbr;
	}
	printf("Random Nbr Max: %i\n", rndNbrMax);
	printf("Random Nbr Min: %i\n", rndNbrMin);
}

/**
 * Checks integerRandomRange. Does checkIterations and returns the upper and lower number given by integerRandomNbr
 * @param max The maximum for both sides of the range [-max, max]
 * @param checkIterations The max number of iterations to reach the limit max
 */
void chekIntegerRandomRange(int max, int checkIterations) {
	int rndNbrMax, rndNbrMin, rndNbr;

	rndNbrMax = integerRandomNbr(max);
	rndNbrMin = rndNbrMax;

	for (int i = 0; i < checkIterations; ++i) {
		rndNbr = integerRandomNbr(max);
		rndNbrMax = rndNbrMax > rndNbr ? rndNbrMax : rndNbr;
		rndNbrMin = rndNbrMin < rndNbr ? rndNbrMin : rndNbr;
	}
	printf("Random Nbr Max: %i\n", rndNbrMax);
	printf("Random Nbr Min: %i\n", rndNbrMin);
}

/**
 * Checks doubleRandomNbr. Does checkIterations and returns the upper and lower number given by doubleRandomNbr
 * @param max The maximum for both sides of the range [-max, max]
 * @param checkIterations The max number of iterations to reach the limit max
 */
void chekDoubleRandomRange(double max, int checkIterations) 	{
	double rndNbrMax, rndNbrMin, rndNbr;

	rndNbrMax = doubleRandomNbr(max);
	rndNbrMin = rndNbrMax;

	for (int i = 0; i < checkIterations; ++i) {
		rndNbr = doubleRandomNbr(max);
		rndNbrMax = rndNbrMax > rndNbr ? rndNbrMax : rndNbr;
		rndNbrMin = rndNbrMin < rndNbr ? rndNbrMin : rndNbr;
	}
	printf("Random Nbr Max: %g\n", rndNbrMax);
	printf("Random Nbr Min: %g\n", rndNbrMin);
}

/**
 * Performs some tests with the randomize functions
 */
void testRandomFunction(void) {
	int max = 12;
	printf("max rnd Nbr: %i\n", max);


	{ //Test section #1
		for (int i = 1; i < 21; ++i) {
			int rndNbr = naturalRandomNbr(max);
			printf("Random Nbr[%i]: %i\n", i , rndNbr);

		}
	}

	{ //Test section #2
		for (int i = 1; i < 21; ++i) {
			double rndNbr = doubleRandomNbr(max);
			printf("Random Nbr[%i]: %g\n", i , rndNbr);

		}
	}

	{ //Test section #3
		double rndNbr;
		int i = 0;
		double limit = max*.78643;

		printf("limit: %g\n", limit);

		for(;;) {
			rndNbr = doubleRandomNbr(max);
			++i;
			if (limit >= 0 && rndNbr > limit) break;
			if (limit < 0 && rndNbr < limit) break;
		}
		printf("Random Nbr[%i]: %g\n", i , rndNbr);
	}

	{ //Test section #4
		int iterations = 55555555;
		chekNaturalRandomRange(max, iterations);
		chekIntegerRandomRange(max, iterations);
		chekDoubleRandomRange(max, iterations);
	}

}
