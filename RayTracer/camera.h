#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"

#include <math.h>
class Camera{
private:
    Vec look_at, position, up;
	Vec cameraN, cameraU, cameraV;
public:
    Camera();
    Camera(Vec, Vec, Vec);
    Vec getLookat();
    Vec getPosition();
	Vec getCameraN();
	Vec getCameraU();
	Vec getCameraV();
};

Camera::Camera(){
    position = Vec(0,0,0);
    look_at = Vec(0,0,1);
}

Camera::Camera(Vec p, Vec l, Vec u){
    position = p;
    look_at = l;
	up = u;
}

Vec Camera::getCameraN(){
	cameraN = position.subtract(look_at).normalize();
	return cameraN;
}

Vec Camera::getCameraU(){
	cameraU = cameraN.crossProduct(up).normalize();
	return cameraU;
}

Vec Camera::getCameraV(){
	cameraV = cameraU.crossProduct(cameraN).normalize();
	return cameraV;
}

Vec Camera::getLookat(){
    return look_at;
}

Vec Camera::getPosition(){
    return position;
}

#endif // CAMERA_H

