#pragma once
class Thevenin
{
private:
	double V;
	double R;
public:	
	Thevenin() :V(0), R(0) {};
	Thevenin(const Thevenin& t) :V(t.V), R(t.R) {};
	Thevenin(const double v, const double r) : V(v), R(r) {};
	double getV() { return V; };
	double getR() { return R; };

	Thevenin parallel(const Thevenin& t2);
	Thevenin series(const Thevenin& t2);

};

