#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "vector.h"
#include "color.h"
#include "ray.h"
#include "illumination.h"

#include <math.h>

class Sphere:public Object{
private:
    Vec center;
    double radius;
    Color color;
	double n;
public:
    Sphere();
    Sphere(Vec,double, Color, Illumination,double);
    Vec getCenter();
    double getRadius();
    double getIntersection(Ray);
    Color getColor();
	Vec getNormalAt(Vec);
	double getRefractive();
	BoundingBox getBbox();
	Vec midPoint();
};

Sphere::Sphere(){
    center = Vec(0,0,0);
    radius = 0;
    color = Color();
}

Sphere::Sphere(Vec s, double r, Color c, Illumination i,double ni){
    center = s;
    radius = r;
    color = c;
	n = ni;
	Object::setIllumination(i);
}

Vec Sphere::getCenter(){
    return center;
}

double Sphere::getRadius(){
    return radius;
}

double Sphere::getIntersection(Ray r){
    double A = pow(r.getDirection().getX(),2)+pow(r.getDirection().getY(),2)+pow(r.getDirection().getZ(),2);
    double B = 2*(r.getDirection().getX()*(r.getOrigin().getX()-center.getX())+r.getDirection().getY()*(r.getOrigin().getY()-center.getY())+r.getDirection().getZ()*(r.getOrigin().getZ()-center.getZ()));
    double C = pow(r.getOrigin().getX()-center.getX(),2)+pow(r.getOrigin().getY()-center.getY(),2)+pow(r.getOrigin().getZ()-center.getZ(),2)-pow(radius,2);
    if(pow(B,2)-4*A*C<0){
        return -1;
    }else{
        double s1 = (-1*B + sqrt(pow(B,2)-4*A*C))/2;
        double s2 = (-1*B - sqrt(pow(B,2)-4*A*C))/2;
		if (s2>0.00001){
			return s2;
		}
		if (s1 > 0.00001){
			return s1;
		}
        if(s1<s2){
            return s1;
        }else{
            return s2;
        }
    }
}

BoundingBox Sphere::getBbox(){
	return BoundingBox(Vec(center.getX() - radius, center.getY() - radius, center.getZ() - radius), Vec(center.getX() + radius, center.getY() + radius, center.getZ() + radius));
}

Color Sphere::getColor(){
    return color;
}

Vec Sphere::getNormalAt(Vec v){
	return Vec(v.getX() - center.getX(), v.getY() - center.getY(), v.getZ() - center.getZ());
}

double Sphere::getRefractive(){
	return n;
}

Vec Sphere::midPoint(){
	return center;
}

#endif // SPHERE_H

