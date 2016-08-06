#include"viewing_plane.h"

using namespace std;

ViewingPlane::ViewingPlane(){
	planeCenter = Vec();
	planeStart = Vec();
}

ViewingPlane::ViewingPlane(Camera camera, double d, double worldWidth, double worldHeight){
	planeCenter = Vec(camera.getPosition().getX() - camera.getCameraN().getX()*d,
		camera.getPosition().getY() - camera.getCameraN().getY()*d,
		camera.getPosition().getZ() - camera.getCameraN().getZ()*d);
	planeStart = Vec(planeCenter.getX() - camera.getCameraU().getX()*worldWidth / 2 - camera.getCameraV().getX()*worldHeight / 2,
		planeCenter.getY() - camera.getCameraU().getY()*worldWidth / 2 - camera.getCameraV().getY()*worldHeight / 2,
		planeCenter.getZ() - camera.getCameraU().getZ()*worldWidth / 2 - camera.getCameraV().getZ()*worldHeight / 2);
}

Vec ViewingPlane::getPlaneStart(){
	return planeStart;
}

Vec ViewingPlane::getPlanePoint(Camera camera, int i, int j, double dx, double dy){
	Vec temp(this->getPlaneStart().getX() + camera.getCameraU().getX()*(i + 0.5)*dx + camera.getCameraV().getX()*(j + 0.5)*dy,
		this->getPlaneStart().getY() + camera.getCameraU().getY()*(i + 0.5)*dx + camera.getCameraV().getY()*(j + 0.5)*dy,
		this->getPlaneStart().getZ() + camera.getCameraU().getZ()*(i + 0.5)*dx + camera.getCameraV().getZ()*(j + 0.5)*dy);
	return temp;
}
