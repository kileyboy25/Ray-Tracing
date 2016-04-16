#ifndef PLANE_H
#define PLANE_H

#include "object.h"
#include "color.h"
#include "illumination.h"

class Plane:public Object{
private:
	Vec normal;
	Vec point;
	Color color;
public:
	Plane();
	Plane(Vec,Vec);
	Plane(Vec, Vec, Color,Illumination);
	Vec getPlaneNormal(); 
	Color getColor();
	Vec getNormalAt(Vec);
	double getIntersection(Ray);
};

Plane::Plane() {
	normal = Vec(1, 0, 0);
	point = Vec();
	color = Color(0.5, 0.5, 0.5);
}

Plane::Plane(Vec normalValue, Vec pointValue) {
	normal = normalValue;
	point = pointValue;
}

Plane::Plane(Vec normalValue, Vec pointValue, Color colorValue, Illumination i) {
	normal = normalValue;
	point = pointValue;
	color = colorValue;
	__super::setIllumination(i);
}

Vec Plane::getPlaneNormal() 
{ 
	return normal;
}


double Plane::getIntersection(Ray r){
	Vec ray_direction = r.getDirection();

	double a = normal.dotProduct(r.getDirection());
	double distance = -1*(normal.getX()*point.getX() + normal.getY()*point.getY() + normal.getZ()*point.getZ());
	double omega = -1 * (normal.getX()*r.getOrigin().getX() + normal.getY()*r.getOrigin().getY() + normal.getZ()*r.getOrigin().getZ() + distance) / (normal.getX()*ray_direction.getX() + normal.getY()*ray_direction.getY() + normal.getZ()*ray_direction.getZ());
	
	if (omega == 0) {
		// ray is parallel to the plane
		return -1;
	}
	else if (omega>0){
		return omega;
	}
	else{
		return -1;
	}
}

Vec Plane::getNormalAt(Vec point) {
	return normal;
}

Color Plane::getColor() 
{ 
	return color;
}

#endif