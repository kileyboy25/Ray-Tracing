#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"

#include <math.h>
class Camera
{
private:
	Vec look_at, position, up;
	Vec cameraN, cameraU, cameraV;
public:
	// Constructor calculates camera u,v and n based on the look_at, position
	// and up set in the constructor.
	Camera ();
	Camera ( Vec, Vec, Vec );
	// Accessors
	Vec getLookat ();
	Vec getPosition ();
	Vec getCameraN ();
	Vec getCameraU ();
	Vec getCameraV ();
};

Camera::Camera ()
{
	position = Vec ( 0, 0, 0 );
	look_at = Vec ( 0, 0, 1 );
	up = Vec ( 0, 1, 0 );
	cameraN = position.subtract ( look_at ).normalize ();
	cameraU = cameraN.crossProduct ( up ).normalize ();
	cameraV = cameraU.crossProduct ( cameraN ).normalize ();
}

Camera::Camera ( Vec p, Vec l, Vec u )
{
	position = p;
	look_at = l;
	up = u;
	cameraN = position.subtract ( look_at ).normalize ();
	cameraU = cameraN.crossProduct ( up ).normalize ();
	cameraV = cameraU.crossProduct ( cameraN ).normalize ();
}

Vec Camera::getCameraN ()
{
	return cameraN;
}

Vec Camera::getCameraU ()
{
	return cameraU;
}

Vec Camera::getCameraV ()
{
	return cameraV;
}

Vec Camera::getLookat ()
{
	return look_at;
}

Vec Camera::getPosition ()
{
	return position;
}

#endif // CAMERA_H