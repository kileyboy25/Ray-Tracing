#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

class BoundingBox{
private:
	Vec min, max;
public:
	BoundingBox();
	BoundingBox(Vec,Vec);
	Vec getMin();
	Vec getMax();
	BoundingBox expand(BoundingBox);
};

BoundingBox::BoundingBox(){
	min = Vec();
	max = Vec();
}

BoundingBox::BoundingBox(Vec minValue, Vec maxValue){
	min = minValue;
	max = maxValue;
}

Vec BoundingBox::getMin(){
	return min;
}

Vec BoundingBox::getMax(){
	return max;
}

BoundingBox BoundingBox::expand(BoundingBox b){
	double xmin, ymin, zmin, xmax, ymax, zmax;
	if (min.getX() < b.getMin().getX()){
		xmin = min.getX();
	}
	else{
		xmin = b.getMin().getX();
	}
	if (min.getY() < b.getMin().getY()){
		ymin = min.getY();
	}
	else{
		ymin = b.getMin().getY();
	}
	if (min.getZ() < b.getMin().getZ()) {
		zmin = min.getZ();
	}
	else{
		zmin = b.getMin().getZ();
	}

	if (max.getX() > b.getMax().getX()){
		xmax = max.getX();
	}
	else{
		xmax = b.getMax().getX();
	}
	if (max.getY() > b.getMax().getY()){
		ymax = max.getY();
	}
	else{
		ymax = b.getMax().getY();
	}
	if (max.getZ() > b.getMax().getZ()) {
		zmax = max.getZ();
	}
	else{
		zmax = b.getMax().getZ();
	}
	return BoundingBox(Vec(xmin,ymin,zmin),Vec(xmax,ymax,zmax));
}

#endif