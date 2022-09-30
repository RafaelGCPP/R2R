#include "R2R.h"
#include "Thevenin.h"
#include<random>
#include<functional>

void R2R::generate_instance()
{
	std::default_random_engine generator;
	std::uniform_real_distribution<double> distribution(-precision, precision);
	auto p = std::bind(distribution, generator);

	for (unsigned char j = 0; j < nbits; j++) {

		Rp[j] = 2 * Rbase * (1 + p());
		Rs[j] = Rbase * (1 + p());
	}
	Rt = 2 * Rbase * (1 + p());
}

R2R::R2R(const unsigned char nb, const double v = 1, const double rb = 1, const double p = 0)
	:nbits(nb), V(v), Rbase(rb), precision(p)
{
	Rp = new double[nbits];
	Rs = new double[nbits];
	generate_instance();
}

R2R::~R2R()
{
	delete[] Rs;
	delete[] Rp;
}

double R2R::compute(const unsigned long value)
{
	int k = value;
	Thevenin t(0, Rt);
	for (unsigned char j = 0; j < nbits; j++) {
		t = t.parallel(Thevenin(V * (k & 1), 2 * Rp[j]));
		t = t.series(Thevenin(0, Rs[j]));
		k >>= 1;
	}

	return t.getV();
}
