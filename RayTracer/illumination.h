#ifndef ILLUMINATION_H
#define ILLUMINATION_H

#include <math.h>

class Illumination
{
private:
	double ka, kd, ks, kr, kt;
	Color c1, c2;
public:
	Illumination();
	Illumination( double, double, double, double, double );
	Illumination( double, double, double, double, double, Color, Color );
	// Accessors and Mutators
	double getka();
	double getkd();
	double getks();
	Color getilea();
	Color getileb();
	double getkr();
	double getkt();
};

Illumination::Illumination()
{
	ka = 0;
	ks = 0;
	kd = 0;
}

Illumination::Illumination( double Ka, double Ks, double Kd, double Kr, double Kt )
{
	ka = Ka;
	ks = Ks;
	kd = Kd;
	kr = Kr;
	kt = Kt;
}

Illumination::Illumination( double Ka, double Ks, double Kd, double Kr, double Kt, Color a, Color b )
{
	ka = Ka;
	ks = Ks;
	kd = Kd;
	kr = Kr;
	kt = Kt;
	c1 = a;
	c2 = b;
}

Color Illumination::getilea()
{
	return c1;
}

Color Illumination::getileb()
{
	return c2;
}

double Illumination::getka()
{
	return ka;
}

double Illumination::getks()
{
	return ks;
}

double Illumination::getkd()
{
	return kd;
}

double Illumination::getkr()
{
	return kr;
}

double Illumination::getkt()
{
	return kt;
}

#endif // !ILLUMINATION_H