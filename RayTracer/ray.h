#ifndef RAY_H
#define RAY_H

#include "object.h"
#include "vector.h"

#include <math.h>
class Ray
{
private:
	Vec origin;
	Vec direction;
	double n;
public:
	Ray ();
	Ray ( Vec, Vec, double );
	Vec getOrigin ();
	Vec getDirection ();
	double getRefractive ();
};

Ray::Ray ()
{
	origin = Vec ();
	direction = Vec ( 0, 0, 1 );
}

Ray::Ray ( Vec o, Vec d, double r )
{
	origin = o;
	direction = d;
	n = r;
}

Vec Ray::getDirection ()
{
	return direction;
}

Vec Ray::getOrigin ()
{
	return origin;
}

double Ray::getRefractive ()
{
	return n;
}

#endif // RAY_H

