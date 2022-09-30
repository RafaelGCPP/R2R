#pragma once

class R2R
{
private:
	unsigned char nbits;
	unsigned long maxval;
	double precision;
	double Rbase;
	double V;
	double Rt;
	double* Rp;
	double* Rs;

	void generate_instance();
public:
	R2R(const unsigned char nb, const double v, const double rb, const double p);
	~R2R();

	double compute(const unsigned long value);

};

