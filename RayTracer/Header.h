#ifndef HEADER_H
#define HEADER_H

#include "vector.h"
#include "object.h"
#include "color.h"
#include "ray.h";

class Triangle : public Object{
private:
	Vec A, B, C;
	Color color;
public:
	Triangle();
	Triangle(Vec, Vec, Vec, color);
	Vec getA();
	Vec getB();
	Vec getC();
	Color getColor();
	double getIntersection(Ray);
};

Triangle::Triangle(){
	A = Vec(0, 0, 0);
	B = Vec(0, 0, 0);
	C = Vec(0, 0, 0);
	color = Color();
}

Triangle::Triangle(Vec a, Vec b, Vec c, Color c){
	A = a;
	B = b;
	C = c;
	color = c;
}

Vec Triangle::getA(){
	return A;
}

Vec Triangle::getB(){
	return B;
}

Vec Triangle::getC(){
	return C;
}

Color Sphere::getColor(){
	return color;
}

double Triangle::getIntersection(Ray r){
	return 0;
}
#endif //Triangle