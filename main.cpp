// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "Thevenin.h"
#include "R2R.h"

int main()
{
	int nbits = 8, maxval = 1 << nbits;
	double voltage = 5;
	double resistance = 1000;
	double tolerance = 5. / 100.;
	R2R DAC(nbits,voltage,resistance,tolerance);

	for (int i = 0; i < maxval; i++) {

		std::cout << DAC.compute(i).getV() << std::endl;
	}
}
