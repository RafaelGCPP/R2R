// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include "Thevenin.h"
#include "R2R.h"

int main()
{
	const int nbits = 8, maxval = 1 << nbits;
	double voltage = 5;
	double resistance = 1000;
	double tolerance = 10. / 100.;
	R2R DAC(nbits, voltage, resistance, tolerance);

	double v_avg[maxval], v_var[maxval];
	int runs = 10000;

	for (int i = 0; i < maxval; i++) {
		v_avg[i] = 0;
		v_var[i] = 0;
	}

	for (int k = 0; k < runs; k++) {

#pragma omp parallel for
		for (int i = 0; i < maxval; i++) {
			double v_avg_old = v_avg[i];
			double v_var_old = v_var[i];

			double v = DAC.compute(i).getV();
			v_avg[i] = (v_avg_old * k + v) / (k + 1.);
			v_var[i] = ((v_var_old * k) + (v - v_avg_old) * (v - v_avg[i])) / (k + 1.);
		}
		DAC.generate_instance();
	}
	std::cout << v_avg[1] << "," << sqrt(v_var[1]) << std::endl;

}
