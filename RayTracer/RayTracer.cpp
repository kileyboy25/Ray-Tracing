#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "plane.h"
#include "sphere.h"
#include "camera.h"
#include "object.h"
#include "color.h"
#include "ray.h"
#include "vector.h"
#include "triangle.h"
#include "light.h"
#include "illumination.h"
#include "kdtree.h"
#include "BoundingBox.h"
#include "Mesh.h"
#include "ImageGeneration.h"
#include "lightBehavior.h"

//reflection and transmission depth
const int MAX_DEPTH = 8;

//objects
Object *objects[4];
const int objectCount = 4;

//light sources
int lightsources = 1;
Light *lightSources[2];
double La = 1;

//refractive index of air
double ni = 1.0;

//tree for traversal
kdtree* tree = new kdtree();

Color illuminate(Ray r, int depth){
	double mintersection = 99999;
	double intersections[objectCount];
	double dotRV = 0;
	int mincount = 99999;
	vector<double> inter;
	Color finalTemp;

	for (int i = 0; i < objectCount; i++){
		intersections[i] = objects[i]->getIntersection(r);
	}
	for (int count = 0; count<objectCount; count++){
		if (intersections[count]<mintersection&&intersections[count]>0){
			mintersection = intersections[count];
			mincount = count;
		}
	}

	if (mincount == 99999){
		return Color(0.27,0.54,0.83);
	}
	else{
		Vec PoI = r.getOrigin().add(Vec(r.getDirection().getX()*intersections[mincount], r.getDirection().getY()*intersections[mincount]
			, r.getDirection().getZ()*intersections[mincount]));
		double specular = 0;
		double diffuse = 0;
		double ambient = 0;
		double lightRed = 0;
		double lightGreen = 0;
		double lightBlue = 0;
		int inShadow = 0;
		double transparent = 0;
		for (int x = 0; x < lightsources; x++){
			double ke = 0;
			Vec S = lightSources[x]->getPosition().subtract(PoI);
			S = S.normalize();
			ke = sqrt(pow(lightSources[x]->getPosition().getX() - PoI.getX(), 2) +
				pow(lightSources[x]->getPosition().getY() - PoI.getY(), 2) +
				pow(lightSources[x]->getPosition().getZ() - PoI.getZ(), 2));
			Ray shadow = Ray(PoI, S,r.getRefractive());
			for (int y = 0; y < objectCount; y++){
				if (objects[y]->getIntersection(shadow)>0.0001){
					if (objects[y]->getIllumination().getkt()>0.0){
						transparent = objects[y]->getIllumination().getkt();
						inShadow++;
					}
					else{
						inShadow++;
						break;
					}
				}
			}
			Vec N = objects[mincount]->getNormalAt(PoI);
			N = N.normalize();
			double dotNS = S.dotProduct(N);
			if (dotNS > 0){
				Vec R;
				Vec temp = Vec(2 * dotNS*N.getX(), 2 * dotNS*N.getY(), 2 * dotNS*N.getZ());
				R = S.subtract(temp);
				R = R.normalize();
				dotRV = R.dotProduct(r.getDirection());
				if (inShadow == 0){
					if (!insideSphere){
						diffuse += dotNS * objects[mincount]->getIllumination().getkd();
					}
				}
				else{
					if (!insideSphere){
						if (transparent > 0){
							diffuse += dotNS * objects[mincount]->getIllumination().getkd()*transparent / inShadow;
						}
						else{
							diffuse += dotNS * objects[mincount]->getIllumination().getkd() / inShadow;
						}
					}
				}
				if (dotRV > 0){
					if (inShadow == 0){
						if (!insideSphere){
							specular += pow(dotRV, ke * 2) * objects[mincount]->getIllumination().getks();
						}
					}
					else{
						if (!insideSphere){
							if (transparent > 0){
								specular += pow(dotRV, ke * 2) * objects[mincount]->getIllumination().getks()*transparent / inShadow;
							}
							else{
								specular += pow(dotRV, ke * 2) * objects[mincount]->getIllumination().getks() / inShadow;
							}
						}
					}
				}
				lightRed = lightSources[x]->getColor().getRed();
				lightGreen = lightSources[x]->getColor().getGreen();
				lightBlue = lightSources[x]->getColor().getBlue();
			}
		}
		if (inShadow == 0){
			if (!insideSphere){
					ambient = objects[mincount]->getIllumination().getka()*La;
			}
		}
		else{
			if (!insideSphere){
				if (transparent > 0){
					ambient = objects[mincount]->getIllumination().getka()*La *transparent/inShadow;
				}
				else{
					ambient = objects[mincount]->getIllumination().getka()*La*0.5 / inShadow;
				}
			}
		}
		finalTemp = Color((ambient + diffuse)*(objects[mincount]->getColor().getRed()) + specular*lightRed,
			(ambient + diffuse)*(objects[mincount]->getColor().getGreen()) + specular*lightGreen,
			(ambient + diffuse)*(objects[mincount]->getColor().getBlue()) + specular*lightBlue);
		if (mincount > 1){
			int square = ((int)floor(PoI.getX() * 3) + (int)floor(PoI.getZ() * 3));
			if (square % 2 == 0){
				finalTemp = Color((ambient + diffuse)*(objects[mincount]->getIllumination().getilea().getRed()) + specular*lightRed,
					(ambient + diffuse)*(objects[mincount]->getIllumination().getilea().getGreen()) + specular*lightGreen,
					(ambient + diffuse)*(objects[mincount]->getIllumination().getilea().getBlue()) + specular*lightBlue);
			}
			else
			{
				finalTemp = Color((ambient + diffuse)*(objects[mincount]->getIllumination().getileb().getRed()) + specular*lightRed,
					(ambient + diffuse)*(objects[mincount]->getIllumination().getileb().getGreen()) + specular*lightGreen,
					(ambient + diffuse)*(objects[mincount]->getIllumination().getileb().getBlue()) + specular*lightBlue);
			}
		}
		if (depth < MAX_DEPTH){
			if (objects[mincount]->getIllumination().getkr()>0){
				Ray reflected = reflect(r, objects[mincount]->getNormalAt(PoI), PoI);
				finalTemp += illuminate(reflected, depth + 1).product(objects[mincount]->getIllumination().getkr());
			}
			if (objects[mincount]->getIllumination().getkt()>0){
				Ray refracted = transmit(r, objects[mincount]->getNormalAt(PoI), objects[mincount]->getRefractive(),PoI);
				finalTemp += illuminate(refracted, depth + 1).product(objects[mincount]->getIllumination().getkt());
			}
		}
	}
	return finalTemp;
}

double randGen()
{
	double hi = 1.0;
	double lo = -1.0;
	double randNum = 0.0;

	randNum = (double)rand() / (double)RAND_MAX;
	return lo + randNum * (hi - lo);

	return randNum;
}

int main()
{
    int thisone;
    int dpi = 72;
    int pixelHeight = 480;
    int pixelWidth = 480;
    double aspect = pixelWidth/pixelHeight;
    double worldWidth = 2;
    double worldHeight = worldWidth/aspect;

    Vec up(0,1,0);
    int n = pixelHeight*pixelWidth;

    Camera camera(Vec(0,0,-1),Vec(0,0,1));
    Vec CameraN = camera.getPosition().subtract(camera.getLookat());
    CameraN = CameraN.normalize();
    Vec CameraU = CameraN.crossProduct(up);
    CameraU = CameraU.normalize();
    Vec CameraV = CameraU.crossProduct(CameraN);
    CameraV = CameraV.normalize();
    RGB *pixels = new RGB[n];

	//light
	Light pointLight(Vec(-3, 4, -5), Color(1, 1, 1));
	Light pointLight1(Vec(0, 3, 0), Color(1, 1, 1));
	lightSources[0] = &pointLight;
	lightSources[1] = &pointLight1;
	int phong = 0;
	Sphere sphere(Vec(0, 0.03, 1.59), 0.69, Color(0.9, 0.9, 0.9), Illumination(0.1, 0.7, 0.3, 0, 0.7), 1.05);
	Sphere sphere1(Vec(0.95, -0.33, 3), 1, Color(0.1, 1, 0.1), Illumination(0.1, 0.7, 0.3, 0.7, 0.0), 1.45);
	Triangle triangle1(Vec(-1.30, -1.2, -0.21), Vec(2.99, -1.2, -0.21), Vec(2.99, -1.2, 9.79), Color(1, 0, 0), Illumination(0.5, 0.7, 0.3, 0.0, 0.0, Color(1, 0, 0), Color(0.94, 0.87, 0.38)), 1.33);
	Triangle triangle2(Vec(-1.30, -1.2, -0.21), Vec(2.99, -1.2, 9.79), Vec(-1.30, -1.2, 9.79), Color(1, 0, 0), Illumination(0.5, 0.7, 0.3, 0.0, 0.0, Color(1, 0, 0), Color(0.94, 0.87, 0.38)), 1.33);
	Plane plane(Vec(-1, 0, 0), Vec(4, 4, 5), Color(0, 0, 1), Illumination(0.5, 0.7, 0.3, 0.0, 0.0, Color(1, 0, 0), Color(0.94, 0.87, 0.38)));
		
	objects[0] = &sphere;
	objects[1] = &sphere1;
	objects[2] = &triangle1;
	objects[3] = &triangle2;
	vector<Object*> obj;
	obj.push_back(&sphere);
	obj.push_back(&sphere1);
	obj.push_back(&triangle1);
	obj.push_back(&triangle2);
	
	double dx = worldWidth / pixelWidth;
	double dy = worldHeight / pixelHeight;
	double d = 1.0;
	//projection plane
	Vec planeCenter(camera.getPosition().getX() - CameraN.getX()*d,
					camera.getPosition().getY() - CameraN.getY()*d,
					camera.getPosition().getZ() - CameraN.getZ()*d);
	Vec planeStart(planeCenter.getX() - CameraU.getX()*worldWidth / 2 - CameraV.getX()*worldHeight / 2,
				planeCenter.getY() - CameraU.getY()*worldWidth / 2 - CameraV.getY()*worldHeight / 2,
				planeCenter.getZ() - CameraU.getZ()*worldWidth / 2 - CameraV.getZ()*worldHeight / 2);

	for (int i = 0; i < pixelWidth; i++){
		for (int j = 0; j < pixelHeight; j++){
			Vec origin = camera.getPosition();
			Vec planePoint(planeStart.getX() + CameraU.getX()*(i + 0.5)*dx + CameraV.getX()*(j + 0.5)*dy,
						planeStart.getY() + CameraU.getY()*(i + 0.5)*dx + CameraV.getY()*(j + 0.5)*dy,
						planeStart.getZ() + CameraU.getZ()*(i + 0.5)*dx + CameraV.getZ()*(j + 0.5)*dy);
			Vec dir = planePoint.subtract(origin);
			dir = dir.normalize();
			Ray r(origin, dir, ni);
			double intersections[objectCount];
			vector<double> inter;
			int mincount = 99999;
			double mintersection = 99999;

			thisone = j*pixelWidth + i;
			insideSphere = false;

			Color finalTemp = illuminate(r, 0);
			pixels[thisone].r = finalTemp.getRed();
			pixels[thisone].g = finalTemp.getGreen();
			pixels[thisone].b = finalTemp.getBlue();
		}
	}
	createBMP("Output.bmp", pixelWidth, pixelHeight, dpi, pixels);
	ifstream file;
	file.open("Output.bmp");
	return 0;
}
