#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include "object.h"
#include "color.h"
#include "ray.h";
#include "illumination.h"

#include <math.h>

class Triangle : public Object{
private:
	Vec A, B, C;
	Color color;
	double n;
public:
	Triangle();
	Triangle(Vec,Vec,Vec,Color, Illumination, double);
	Vec getA();
	Vec getB();
	Vec getC();
	Color getColor();
	double getIntersection(Ray);
	Vec getNormalAt(Vec);
	double getRefractive();
	BoundingBox getBbox();
	Vec midPoint();
};

Triangle::Triangle(){
	A = Vec(0,0,0);
	B = Vec(0,0,0);
	C = Vec(0,0,0);
	color = Color();
}

Triangle::Triangle(Vec a,Vec b,Vec c,Color col, Illumination i,double ni){
	A = a;
	B = b;
	C = c;
	color = col;
	n = ni;
	Object::setIllumination(i);
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

Color Triangle::getColor(){
	return color;
}

double Triangle::getIntersection(Ray r){
	Vec e1 = B.subtract(A);
	Vec e2 = C.subtract(A);
	Vec P = r.getDirection().crossProduct(e2);
	float det = e1.dotProduct(P);
	//parallel
	if (det == 0){
		return -1;
	}
	Vec T = r.getOrigin().subtract(A);
	Vec Q = T.crossProduct(e1);
	float u = T.dotProduct(P) / det;
	//outside the triangle
	if (u > 1 || u < 0){
		return -1;
	}
	float v = Q.dotProduct(r.getDirection()) / det;
	//outside the triangle
	if (v > 1 || v < 0|| u+v>1){
		return -1;
	}
	float t = Q.dotProduct(e2) / det;
	if (t < 0){
		return -1;
	}
	else{
		return t;
	}
}

Vec Triangle::getNormalAt(Vec v){
	Vec e1 = B.subtract(A);
	Vec e2 = C.subtract(A);
	return e2.crossProduct(e1);
}

double Triangle::getRefractive(){
	return n;
}

BoundingBox Triangle::getBbox(){
	double xmin, ymin, zmin, xmax, ymax, zmax;
	xmin = A.getX();
	if (xmin > B.getX()){
		xmin = B.getX();
	}
	if (xmin > C.getX()){
		xmin = C.getX();
	}
	ymin = A.getY();
	if (ymin > B.getY()){
		ymin = B.getY();
	}
	if (ymin > C.getY()){
		ymin = C.getY();
	}
	zmin = A.getZ();
	if (zmin > B.getZ()){
		zmin = B.getZ();
	}
	if (zmin > C.getZ()){
		zmin = C.getZ();
	}
	xmax = A.getX();
	if (xmax < B.getX()){
		xmax = B.getX();
	}
	if (xmax < C.getX()){
		xmax = C.getX();
	}
	ymax = A.getY();
	if (ymax < B.getY()){
		ymax = B.getY();
	}
	if (ymax < C.getY()){
		ymax = C.getY();
	}
	zmax = A.getZ();
	if (zmax < B.getZ()){
		zmax = B.getZ();
	}
	if (zmax < C.getZ()){
		zmax = C.getZ();
	}
	return BoundingBox(Vec(xmin,ymin,zmin),Vec(xmax,ymax,zmax));
}

Vec Triangle::midPoint(){
	return Vec((A.getX() + B.getX() + C.getX()) / 3, (A.getY() + B.getY() + C.getY()) / 3, (A.getZ() + B.getZ() + C.getZ()) / 3);
}

#endif //Triangle