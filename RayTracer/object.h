#ifndef OBJECT_H
#define OBJECT_H

#include "ray.h"
#include "vector.h"
#include "color.h"
#include "illumination.h"
#include "BoundingBox.h"

#include <math.h>
class Object
{
private:
	Illumination illumination;
public:
	Object();
	Object( Illumination );
	virtual double getIntersection( Ray r )
	{
		return 0;
	}
	virtual Color getColor()
	{
		return Color();
	}
	virtual Vec getNormalAt( Vec v )
	{
		return v;
	}
	virtual BoundingBox getBbox()
	{
		return BoundingBox();
	}
	virtual Vec midPoint()
	{
		return Vec();
	}
	Illumination getIllumination()
	{
		return illumination;
	}
	void setIllumination( Illumination i )
	{
		illumination = i;
	}
	virtual double getRefractive()
	{
		return 0;
	}
};

Object::Object()
{
	illumination = Illumination();
}

Object::Object( Illumination i )
{
	illumination = i;
}
#endif // OBJECT_H

