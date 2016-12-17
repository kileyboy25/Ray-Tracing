#ifndef COLOR_H
#define COLOR_H

#include <math.h>

class Color
{
private:
	double red, green, blue;
public:
	Color ();
	Color ( double, double, double );
	// Accessors and Mutators
	double getRed ();
	double getBlue ();
	double getGreen ();
	void setRed ( double );
	void setGreen ( double );
	void setBlue ( double );
	Color product ( double );
	Color operator+=( Color );
};

Color::Color ()
{
	red = 0;
	green = 0;
	blue = 0;
}

Color::Color ( double r, double g, double b )
{
	red = r;
	green = g;
	blue = b;
}
double Color::getRed ()
{
	return red;
}
double Color::getBlue ()
{
	return blue;
}
double Color::getGreen ()
{
	return green;
}
Color Color::product ( double c )
{
	return Color ( red*c, green*c, blue*c );
}
Color Color::operator+=( Color c )
{
	red += c.getRed ();
	green += c.getGreen ();
	blue += c.getBlue ();
	return *this;
}
void Color::setRed ( double r )
{
	red = r;
}
void Color::setGreen ( double g )
{
	green = g;
}
void Color::setBlue ( double b )
{
	blue = b;
}


#endif // COLOR_H