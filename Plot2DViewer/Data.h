#define _USE_MATH_DEFINES
#include <cmath>

double					// Исходные значения параметров L, R, B, T
	L=-2*M_PI,
	R=2*M_PI,
	B=-1.5,
	T=1.5;

double fi(double t)
{
	return cos(2*t);
}

double r(double t)
{
	return 2*t;
}
