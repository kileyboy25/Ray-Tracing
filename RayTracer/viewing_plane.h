#ifndef VIEWINGPLANE_H
#define VIEWINGPLANE_H
#include "vector.h"
#include "camera.h"
class ViewingPlane{
public:
	ViewingPlane();
	ViewingPlane(Camera,double,double,double);
	Vec getPlanePoint(Camera,int,int,double,double);
	Vec getPlaneStart();
private:
	Vec planeStart, planeCenter;
};
#endif