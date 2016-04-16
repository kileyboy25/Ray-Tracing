#ifndef KDTREE_H
#define KDTREE_H

#include "vector.h"
#include "object.h"
#include "BoundingBox.h"

class kdtree{
public:
	kdtree* front;
	kdtree* rear;
	int noObjects;
	vector<Object*> objects;
	Plane faces[6];
	BoundingBox bbox;
	Plane splitter;
	bool leaf;
public:
	kdtree();
	vector<Object*> getObjects();
	void setObjects(vector<Object*>);
	void build(vector<Object*>, int);
	vector<Object*> traverse(kdtree*, Ray);
	//void createFaces();
};

kdtree::kdtree(){
	noObjects = 0;
}

vector<Object *> kdtree::getObjects(){
	return objects;
}

void kdtree::setObjects(vector<Object*> o){
	objects = o;
}

void kdtree::build(vector<Object*> objs, int depth){
	this->setObjects(objs);
	this->front = new kdtree();
	this->rear = new kdtree();
	this->bbox = BoundingBox();

	if (objs.size() == 0){
		this->leaf = true;
	}
	if (objs.size() == 1){
		this->leaf = true;
		this->bbox = objs[0]->getBbox();
		this->front = new kdtree();
		this->rear = new kdtree();
		this->front->objects = vector<Object*>();
		this->rear->objects = vector<Object*>();
		this->faces[0] = Plane(Vec(-1, 0, 0), this->bbox.getMin());
		this->faces[1] = Plane(Vec(0, -1, 0), this->bbox.getMin());
		this->faces[2] = Plane(Vec(0, 0, -1), this->bbox.getMin());
		this->faces[3] = Plane(Vec(1, 0, 0), this->bbox.getMax());
		this->faces[4] = Plane(Vec(0, 1, 0), this->bbox.getMax());
		this->faces[5] = Plane(Vec(0, 0, 1), this->bbox.getMax());
	}

	this->bbox = objs[0]->getBbox();
	for (int i = 1; i < objs.size(); i++){
		this->bbox = this->bbox.expand(objs[i]->getBbox());
	}

	Vec midpt = Vec();
	for (int i = 0; i < objs.size(); i++){
		midpt = midpt.add(objs[i]->midPoint().multiply((double)1 / (double)objs.size()));
	}
	//this->createFaces();
	this->faces[0] = Plane(Vec(-1, 0, 0), this->bbox.getMin());
	this->faces[1] = Plane(Vec(0, -1, 0), this->bbox.getMin());
	this->faces[2] = Plane(Vec(0, 0, -1), this->bbox.getMin());
	this->faces[3] = Plane(Vec(1, 0, 0), this->bbox.getMax());
	this->faces[4] = Plane(Vec(0, 1, 0), this->bbox.getMax());
	this->faces[5] = Plane(Vec(0, 0, 1), this->bbox.getMax());
	vector<Object*> front_objs;
	vector<Object*> rear_objs;
	int axis;
	if (depth < 4){
		axis = depth;
	}
	else if (depth % 2 == 0 && depth % 3 != 0){
		axis = 2;
	}
	else if (depth % 3 == 0){
		axis = 3;
	}
	else{
		axis = 1;
	}

	bool split_plane = false;
	for (int i = 0; i < objs.size(); i++){
		switch (axis)
		{
		case 1:
			if (!split_plane){
				this->splitter = Plane(Vec(1, 0, 0), midpt);
				split_plane = true;
			}
			midpt.getX() >= objs[i]->midPoint().getX() ? rear_objs.push_back(objs[i]) : front_objs.push_back(objs[i]);
			break;
		case 2:
			if (!split_plane){
				this->splitter = Plane(Vec(0, 1, 0), midpt);
				split_plane = true;
			}
			midpt.getY() >= objs[i]->midPoint().getY() ? rear_objs.push_back(objs[i]) : front_objs.push_back(objs[i]);
			break;
		case 3:
			if (!split_plane){
				this->splitter = Plane(Vec(0, 0, 1), midpt);
				split_plane = true;
			}
			midpt.getZ() >= objs[i]->midPoint().getZ() ? rear_objs.push_back(objs[i]) : front_objs.push_back(objs[i]);
			break;
		}
	}

	if (front_objs.size() == 0 && rear_objs.size() > 0) front_objs = rear_objs;
	if (rear_objs.size() == 0 && front_objs.size() > 0) rear_objs = front_objs;

	//terminating condition
	int matches = 0;
	for (int i = 0; i < front_objs.size(); i++){
		for (int j = 0; j < rear_objs.size(); j++){
			if (front_objs[i] == rear_objs[j]){
				matches++;
			}
		}
	}

	if ((float)matches / front_objs.size() < 0.5 && (float)matches / rear_objs.size() < 0.5){
		this->leaf = false;
		this->front->build(front_objs, depth + 1);
		this->rear->build(rear_objs, depth + 1);
	}
	else{
		this->front = new kdtree();
		this->rear = new kdtree();
		this->front->objects = vector<Object*>();
		this->rear->objects = vector<Object*>();
		this->leaf = true;
	}
	
}

vector<Object*> kdtree::traverse(kdtree* tree, Ray r){
	double minintersection = 99999;
	double a = 99999;
	double b = 99999;
	for (int i = 0; i < 6; i++){
		if (tree->faces[i].getIntersection(r) >0){
			double inter = tree->faces[i].getIntersection(r);
			Vec PoF = r.getOrigin().add(Vec(r.getDirection().getX()*inter, r.getDirection().getY()*inter
				, r.getDirection().getZ()*inter));
			if (PoF.getX() >= tree->bbox.getMin().getX() && PoF.getX() <= tree->bbox.getMax().getX() &&
				PoF.getY() >= tree->bbox.getMin().getY() && PoF.getY() <= tree->bbox.getMax().getY() &&
				PoF.getZ() >= tree->bbox.getMin().getZ() && PoF.getZ() <= tree->bbox.getMax().getZ()){
				if (a == 99999){
					a = inter;
				}
				else{
					b = inter;
				}
			}
		}
	}
	double s = tree->splitter.getIntersection(r);

	if (a == 99999 && b == 99999){
		return vector<Object*>();
	}
	while (!tree->leaf){
		if (s == -1){
			return traverse(tree->rear, r);
		}
		if (a <= s){
			if (b < s){
				return traverse(tree->rear, r);
			}
			else{
				vector<Object*> first = traverse(tree->front, r);
				vector<Object*> second = traverse(tree->rear, r);
				first.insert(first.end(), second.begin(), second.end());
				return first;
			}
		}
		else{
			if (b > s){
				return traverse(tree->front, r);
			}
			else{
				vector<Object*> first = traverse(tree->front, r);
				vector<Object*> second = traverse(tree->rear, r);
				first.insert(first.end(), second.begin(), second.end());
				return first;
			}
		}
	}
	if (tree->leaf){
		return tree->objects;
	}
}

//
//void kdtree::createFaces(){
//	faces.push_back(Plane(Vec(1, 0, 0), bbox.getMin()));
//	faces.push_back(Plane(Vec(0, 1, 0), bbox.getMin()));
//	faces.push_back(Plane(Vec(0, 0, 1), bbox.getMin()));
//	faces.push_back(Plane(Vec(1, 0, 0), bbox.getMin()));
//	faces.push_back(Plane(Vec(0, 1, 0), bbox.getMin()));
//	faces.push_back(Plane(Vec(0, 0, 1), bbox.getMin()));
//}

#endif