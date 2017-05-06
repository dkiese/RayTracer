/* Triangle intersect algorithm taken from http://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm*/

#include "Object.h"


void Object::setMaterial(Material * mat){
    m = mat;   
}

Triangle::Triangle(Point v1,Point v2, Point v3, Point no){
    p1 = v1;
    p2 = v2;
    p3 = v3;
    
    n = no;
    isLight = false;
}

Sphere::Sphere(Point p, double r){
    center = p;
    radius = r;
    
    isLight = false;
}
#define EPS 1E-6

#define EPSILON 0.000001

Point Triangle::getIntersection(Ray r){

	// RETURN THE POINT OF INTERSECTION FOR THIS TRIANGLE.

	//double n = (p1-p3).cross(p2-p3);
	
	double t = (((r.p - p1)*-1)*n)/(r.v*n);
	if(t < 0)
	{
		return Point::Infinite();
	}
	Point q = r.p + r.v*t;
	
	if( (((p1-q).cross(p2-q)*n) > 0) && (((p2-q).cross(p3-q)*n) > 0) && (((p3-q).cross(p1-q)*n) > 0) )
	{
		return q;
	}
	
    return Point::Infinite();
}

Point Triangle::getNormal(Point p){
    Point one = p1-p2;
    Point two = p1-p3;
    Point ret = one.cross(two);
    ret.normalize();
    return ret;
}

Point Sphere::getNormal(Point p){
    Point ret = (p-center);
    ret.normalize();
    return ret;
}

Point Sphere::getIntersection(Ray r){

	// RETURN THE POINT OF INTERSECTION FOR THIS SPHERE.
	//Point P0 = r.p
	//Point V = r.v
	// c = center
	// r = radius
	//t^2 + bt + c = 0
	
	double B = (r.v*2)*(r.p-center);
	Point c1 = r.p - center;
	double c2 = c1.length();
	c2 = c2*c2;
	double C = c2 - (radius*radius);
	double T = 0;

	if( ((B*B) - 4*C) >= 0 )
	{

		double t1 = (-B + sqrt((B*B)-4*C))/2;
		double t2 = (-B - sqrt((B*B)-4*C))/2;
		if(t1 > 0 && t2 > 0)
		{
			if(t1 > t2)
				T = t2;
			else 
				T = t1;
		}
		else{
			if(t1 > 0)
				T = t1;
			if(t2 > 0)
				T = t2;
		}
	
		Point X = r.p + (r.v*T);
		return X;

	}

    return Point::Infinite();  
}

