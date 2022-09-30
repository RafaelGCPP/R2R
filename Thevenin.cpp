#include "Thevenin.h"

/***
* Computes the Thevenin equivalent of two Thevenin equivalent networks in parallel.
*/
Thevenin Thevenin::parallel(const Thevenin& t2)
{
    double v = (t2.R * V + R * t2.V) / (R + t2.R);
    double r = 1 / ((1 / R) + (1 / t2.R));
    return Thevenin(v,r);
}

/***
* Computes the Thevenin equivalent of two Thevenin equivalent networks in series.
*/
Thevenin Thevenin::series(const Thevenin& t2)
{
    return Thevenin(V+t2.V, R+t2.R);
}
