#pragma once
#include <chrono>

#include<random>
#include<functional>
#include "Thevenin.h"

/***
* A class representing a R-2R DAC 
*/
class R2R
{
private:
	unsigned char nbits;
	unsigned long maxval;
	double tolerance;
	double Rbase;
	double V;
	double Rt;
	double* Rp;
	double* Rs;

public:
	R2R(const unsigned char nb, const double v, const double rb, const double tol);
	~R2R();

	Thevenin compute(const unsigned long value);
	void generate_instance();

};

