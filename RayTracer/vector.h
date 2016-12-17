#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vec
{
private:
	double x, y, z;
public:
	Vec();

	Vec( double, double, double );

	double getX();
	double getY();
	double getZ();

	double dotProduct( Vec );
	Vec multiply( double );
	Vec normalize();
	Vec crossProduct( Vec );
	Vec subtract( Vec );
	Vec add( Vec );
	double magnitude();
};

Vec::Vec()
{
	x = 0;
	y = 0;
	z = 0;
}
Vec::Vec( double i, double j, double k )
{
	x = i;
	y = j;
	z = k;
}

double Vec::getX()
{
	return x;
}

double Vec::getY()
{
	return y;
}

double Vec::getZ()
{
	return z;
}

Vec Vec::crossProduct( Vec v )
{
	return Vec( y*v.getZ() - z*v.getY(), z*v.getX() - x*v.getZ(), x*v.getY() - y*v.getX() );
}

double Vec::dotProduct( Vec v )
{
	return x*v.getX() + y*v.getY() + z*v.getZ();
}

Vec Vec::normalize()
{
	double sq = sqrt( x*x + y*y + z*z );
	return Vec( x / sq, y / sq, z / sq );
}

Vec Vec::subtract( Vec v )
{
	return Vec( x - v.getX(), y - v.getY(), z - v.getZ() );
}

Vec Vec::add( Vec v )
{
	return Vec( x + v.getX(), y + v.getY(), z + v.getZ() );
}

Vec Vec::multiply( double a )
{
	return Vec( x*a, y*a, z*a );
}

double Vec::magnitude()
{
	return sqrt( x*x + y*y + z*z );
}

#endif // VECTOR_H

