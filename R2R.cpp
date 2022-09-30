#include "R2R.h"

/***
* Generates an R2R instance based on the base resistance and tolerance
*/
void R2R::generate_instance()
{



	//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	//std::default_random_engine rd(seed);

	std::random_device rd;
	std::uniform_real_distribution<double> tol_dist(-tolerance, tolerance);

	
	for (unsigned char j = 0; j < nbits; j++) {

		Rp[j] = 2 * Rbase * (1 + tol_dist(rd));
		Rs[j] = Rbase * (1 + tol_dist(rd));
	}
	Rt = 2 * Rbase * (1 + tol_dist(rd));
}

/***
* Constructor and destructor for the class
*/
R2R::R2R(const unsigned char nb, const double v = 1, const double rb = 1, const double tol = 0)
	:nbits(nb), V(v), Rbase(rb), tolerance(tol) 
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

/***
* Evaluates the network output Thevenin equivalent for some input value
* considering the logic level defined by V
*/
Thevenin R2R::compute(const unsigned long value)
{
	int k = value;
	Thevenin t(0, Rt);
	for (unsigned char j = 0; j < nbits; j++) {
		t = t.parallel(Thevenin(V * (k & 1), 2 * Rp[j]));
		t = t.series(Thevenin(0, Rs[j]));
		k >>= 1;
	}

	return t;
}
