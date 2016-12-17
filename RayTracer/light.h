#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "color.h"

#include <math.h>

class Light
{
private:
	Vec position;
	Color color;
public:
	Light ();
	Light ( Vec, Color );
	// Accessors
	Vec getPosition ();
	Color getColor ();
};

Light::Light ()
{
	position = Vec ( 0, 0, 0 );
	color = Color ( 0, 0, 1 );
}

Light::Light ( Vec p, Color c )
{
	position = p;
	color = c;
}

Color Light::getColor ()
{
	return color;
}

Vec Light::getPosition ()
{
	return position;
}

#endif