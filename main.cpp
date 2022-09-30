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
	double tolerance = 1. / 100.;
	R2R DAC(nbits, voltage, resistance, tolerance);

	double v_avg[maxval], v_var[maxval], v_dev[maxval], v_min[maxval], v_max[maxval];
	int runs = 10000;

	for (int i = 0; i < maxval; i++) {
		v_avg[i] = 0;
		v_var[i] = 0;
		v_min[i] = voltage;
		v_max[i] = 0;
	}

	for (int k = 0; k < runs; k++) {

#pragma omp parallel for
		for (int i = 0; i < maxval; i++) {
			double v_avg_old = v_avg[i];
			double v_var_old = v_var[i];

			double v = DAC.compute(i).getV();
			v_avg[i] = (v_avg_old * k + v) / (k + 1.);
			v_var[i] = ((v_var_old * k) + (v - v_avg_old) * (v - v_avg[i])) / (k + 1.);
			v_dev[i] = sqrt(v_var[i]);
			v_min[i] = fmin(v_min[i], v);
			v_max[i] = fmax(v_max[i], v);
		}
		DAC.generate_instance();
	}
	/*std::cout << v_avg[1] << "," << v_dev[1] << "," << (v_dev[1] / v_avg[1]) << std::endl;
	std::cout << v_min[1] << "," << v_max[1] << ",";
	std::cout << (v_max[1] - v_min[1]) << std::endl;*/

	for (int i = 0; i < maxval; i++) {
		std::cout << i << ", ";
		std::cout << v_avg[i] <<", " ;
		std::cout << v_dev[i] << ", ";
		std::cout << v_min[i] << ", ";
		std::cout << v_max[i] << std::endl;
	}

}
