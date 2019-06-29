/* Copyright (c) 2019-2020 The Dexergi Developers */
/**
 * @file       paramgen.cpp
 *
 * @brief      Parameter generation utility for Zerocoin.
 *
 * @author     Ian Miers, Christina Garman and Matthew Green
 * @date       June 2013
 *
 * @copyright  Copyright 2013 Ian Miers, Christina Garman and Matthew Green
 * @license    This project is released under the MIT license.
 **/
// Copyright (c) 2017-2018 The PIVX developers

#include <string>
#include <iostream>
#include <fstream>
//#include <curses.h>
#include <exception>
#include "Zerocoin.h"

#define DEFAULT_MODULUS_SIZE    3072
#define MIN_MODULUS_SIZE        1026

using namespace std;
using namespace libzerocoin;

void
PrintWarning()
{
	cout << "Zerocoin parameter generation utility" << endl;
	cout << "-------------------------------------" << endl << endl;
	cout << "This utility generates an l-bit modulus N as the product of" << endl;
	cout << "two safe primes p, q. The values p and q are not stored." << endl;
	cout << "Call this program with no arguments to see usage options." << endl;
	cout << endl;
	cout << "SECURITY WARNING: ZEROCOIN PARAMETERS MUST BE GENERATED BY" << endl;
	cout << "A TRUSTED PARTY WHO DOES NOT STORE THE FACTORS. WHILE WE MAKE" << endl;
	cout << "A BEST EFFORT TO DESTROY THIS INFORMATION WE DO NOT TAKE" << endl;
	cout << "SPECIAL PRECAUTIONS TO ENSURE THAT THEY ARE DESTROYED." << endl;
	cout << endl;
	cout << "USE THIS UTILITY AT YOUR OWN RISK" << endl << endl;
}

void usage()
{
	printf("Usage:\n");
	printf(" -b <numbits>\n");
	printf(" -o <output file>\n");

	exit (8);
}

int main(int argc, char **argv)
{
	static CBigNum resultModulus(0);
	uint32_t numBits = DEFAULT_MODULUS_SIZE;
	ofstream outfile;
	char* outfileName;
	bool writeToFile = false;

	while ((argc > 1) && (argv[1][0] == '-'))
	{
		switch (argv[1][1])
		{
		case 'b':
			numBits = atoi(argv[2]);
			++argv;
			--argc;
			break;

		case 'o':
			outfileName = argv[2];
			writeToFile = true;
			break;

		case 'h':
			usage();
			break;

		default:
			printf("Wrong Argument: %s\n", argv[1]);
			usage();
			break;
		}

		++argv;
		--argc;
	}

	if (numBits < MIN_MODULUS_SIZE) {
		cout << "Modulus is below minimum length (" << MIN_MODULUS_SIZE << ") bits" << endl;
		return(0);
	}

	PrintWarning();

	cout << "Modulus size set to " << numBits << " bits." << endl;
	cout << "Generating parameters. This may take a few minutes..." << endl;

	// Generate two safe primes "p" and "q"
	CBigNum *p, *q;
	p = new CBigNum(0);
	q = new CBigNum(0);
	*p = CBigNum::generatePrime(numBits / 2, true);
	*q = CBigNum::generatePrime(numBits / 2, true);

	// Multiply to compute N
	resultModulus = (*p) * (*q);

	// Wipe out the factors
	delete p;
	delete q;

	// Convert to a hexidecimal string
	std::string resultHex = resultModulus.ToString(16);

	cout << endl << "N = " << endl << resultHex << endl;

	if (writeToFile) {
		try {
			outfile.open (outfileName);
			outfile << resultHex;
			outfile.close();
			cout << endl << "Result has been written to file '" << outfileName << "'." << endl;
		} catch (std::runtime_error &e) {
			cout << "Unable to write to file:" << e.what() << endl;
		}
	}
}
