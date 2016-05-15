#include "Math.h"

Engine::Math::Plane::Plane(Vector3 iNormal, Vector3 iPointOnPlane)
{
	normal = iNormal;
	float a = iNormal.x;
	float b = iNormal.y;
	float c = iNormal.z;
	distance = a*iPointOnPlane.x + b*iPointOnPlane.y + c * iPointOnPlane.z;	
}

Engine::Math::Vector3 Engine::Math::Plane::ClosestPointFromPointOnPlane(Vector3 iPointOnPlane)const
{
	float t = (normal.dot(iPointOnPlane) - distance) / normal.dot(normal);
	return (iPointOnPlane -  (normal*t));
}



Engine::Math::Vector3 Engine::Math::Plane::getPlaneNormal() const
{
	return normal;
}


float Engine::Math::Plane::getDistanceFromOrigin() const
{
	return distance;
}

Engine::Math::Plane Engine::Math::Plane::ComputePlane(Vector3 iA, Vector3 iB, Vector3 iC)
{
	Plane p;
	p.normal = (iB - iA).Cross(iC - iA).CreateNormalized();
	p.distance = p.normal.dot(iA);
	return p;
}


bool Engine::Math::Sphere::IntersectSphere(Sphere iOther) const
{
	Vector3 d = centre - iOther.centre;
	float dist2 = d.dot(d);   
	// Spheres intersect if squared distance is less than squared sum of radii
	float radiusSum = radius + iOther.radius;
	return dist2 <= radiusSum * radiusSum;
}


// Given segment ab and point c, computes closest point d on ab.
// Also returns t for the position of d, d(t) = a + t*(b - a)
void Engine::Math::ClosestPointFromPointOnLineSegment(Vector3 c,
	Vector3 a,
	Vector3 b,
	float &t,
	Vector3 &d)
{
	Vector3 ab = b - a;
	// Project c onto ab, computing parameterized position d(t) = a + t*(b – a)
	t = (c - a).dot(ab) / ab.dot(ab);
	// If outside segment, clamp t (and therefore d) to the closest endpoint
	if (t < 0.0f) t = 0.0f;
	if (t > 1.0f) t = 1.0f;
	// Compute projected position from the clamped t
	d = a + ab * t;
}

// Returns the squared distance between point c and segment ab
float Engine::Math::SqDistPointSegment(Vector3 a, Vector3 b, Vector3 c)
{
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 bc = c - b;
	float e = ac.dot(ab);
	// Handle cases where c projects outside ab
	if (e <= 0.0f) 
		return ac.dot(ac);
	float f = ab.dot(ab);
	if (e >= f) 
		return bc.dot(bc);
	// Handle cases where c projects onto ab
	return ac.dot(ac) - e * e / f;
}









