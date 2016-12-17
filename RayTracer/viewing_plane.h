#ifndef VIEWING_PLANE_H
#define VIEWING_PLANE_H
#include "vector.h"
#include "camera.h"
class ViewingPlane
{
public:
	ViewingPlane ();
	ViewingPlane ( Camera, double, double, double );
	Vec getPlanePoint ( Camera, int, int, double, double );
	Vec getPlaneStart ();
private:
	Vec planeStart, planeCenter;
};

ViewingPlane::ViewingPlane ( Camera camera, double d, double worldWidth, double worldHeight )
{
	planeCenter = Vec ( camera.getPosition ().getX () - camera.getCameraN ().getX ()*d,
						camera.getPosition ().getY () - camera.getCameraN ().getY ()*d,
						camera.getPosition ().getZ () - camera.getCameraN ().getZ ()*d );
	planeStart = Vec ( planeCenter.getX () - camera.getCameraU ().getX ()*worldWidth / 2 - camera.getCameraV ().getX ()*worldHeight / 2,
					   planeCenter.getY () - camera.getCameraU ().getY ()*worldWidth / 2 - camera.getCameraV ().getY ()*worldHeight / 2,
					   planeCenter.getZ () - camera.getCameraU ().getZ ()*worldWidth / 2 - camera.getCameraV ().getZ ()*worldHeight / 2 );
}

Vec ViewingPlane::getPlaneStart ()
{
	return planeStart;
}

Vec ViewingPlane::getPlanePoint ( Camera camera, int i, int j, double dx, double dy )
{
	double x = i + 0.5;
	double y = j + 0.5;
	Vec temp ( getPlaneStart ().getX () + camera.getCameraU ().getX ()*x*dx + camera.getCameraV ().getX ()*y*dy,
			   getPlaneStart ().getY () + camera.getCameraU ().getY ()*x*dx + camera.getCameraV ().getY ()*y*dy,
			   getPlaneStart ().getZ () + camera.getCameraU ().getZ ()*x*dx + camera.getCameraV ().getZ ()*y*dy );
	return temp;
}

#endif