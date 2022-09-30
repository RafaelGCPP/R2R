// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "Thevenin.h"
#include "R2R.h"

int main()
{
	R2R DAC(8,5,1000,0.05);

	int nbits = 8, maxval = 1 << nbits;

	for (int i = 0; i < maxval; i++) {

		std::cout << DAC.compute(i) << std::endl;
	}
}
