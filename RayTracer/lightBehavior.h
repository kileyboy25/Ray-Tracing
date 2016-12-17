#ifndef LIGHTBEHAVIOR_H
#define LIGHTBEHAVIOR_H

#include "ray.h"
#include "vector.h"

//inside object
bool insideSphere = false;

Ray reflect ( Ray r, Vec normal, Vec POI )
{
	double dotRS = 2 * r.getDirection ().dotProduct ( normal );
	Vec dir = r.getDirection ().subtract ( normal.multiply ( dotRS ) );
	dir = dir.normalize ();
	return Ray ( POI, dir, r.getRefractive () );
}

Ray transmit ( Ray r, Vec normal, double nt, Vec PoI )
{
	double ratio;
	if ( insideSphere )
	{
		ratio = nt / r.getRefractive ();
	}
	else
	{
		ratio = nt / r.getRefractive ();
	}
	normal = normal.normalize ();
	double dotND = r.getDirection ().multiply ( -1 ).dotProduct ( normal );
	double dotNi = r.getDirection ().multiply ( -1 ).dotProduct ( normal );
	if ( dotND < 0 )
	{
		insideSphere = false;
		normal = normal.multiply ( -1 );
		normal.normalize ();
	}
	else
	{
		insideSphere = true;
	}
	dotND = r.getDirection ().multiply ( -1 ).dotProduct ( normal );
	double pown = pow ( ratio, 2 );
	double tir = 1 - pown*( 1 - pow ( dotND, 2 ) );
	if ( tir < 0 )
	{
		double dotRS = 2 * r.getDirection ().dotProduct ( normal );
		Vec dir = r.getDirection ().subtract ( normal.multiply ( dotRS ) );
		dir = dir.normalize ();
		insideSphere = false;
		return Ray ( PoI, dir, r.getRefractive () );
	}
	else
	{
		Vec second = normal.multiply ( ratio*dotND - sqrt ( tir ) );
		Vec first = r.getDirection ().multiply ( -1 * pown );
		Vec dir = second.subtract ( first );
		dir = dir.normalize ();
		if ( dotNi < 0 )
		{
			nt = r.getRefractive ();
		}
		return Ray ( PoI, dir, nt );
	}
}


#endif