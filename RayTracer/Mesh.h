#ifndef MESH_H
#define MESH_H

#include "vector.h"

class Mesh
{
public:
	Vec V;


	Mesh( double a, double b, double c )
	{
		V = Vec( a, b, c );
	}
};

#endif