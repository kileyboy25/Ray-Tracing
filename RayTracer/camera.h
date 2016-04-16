#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"

#include <math.h>
class Camera{
private:
    Vec look_at, position;
public:
    Camera();
    Camera(Vec, Vec);
    Vec getLookat();
    Vec getPosition();
};

Camera::Camera(){
    position = Vec(0,0,0);
    look_at = Vec(0,0,1);
}

Camera::Camera(Vec p, Vec l){
    position = p;
    look_at = l;
}

Vec Camera::getLookat(){
    return look_at;
}

Vec Camera::getPosition(){
    return position;
}

#endif // CAMERA_H

