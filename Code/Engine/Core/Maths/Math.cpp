#include "Math.h"

Engine::Math::ParametricPlane::ParametricPlane(Vector3 iNormal, Vector3 iPointOnPlane)
{
	normal = iNormal;
	float a = iNormal.x;
	float b = iNormal.y;
	float c = iNormal.z;
	distance = a*iPointOnPlane.x + b*iPointOnPlane.y + c * iPointOnPlane.z;	
}


Engine::Math::Vector3 Engine::Math::ParametricPlane::getPlaneNormal() const
{
	return normal;
}


float Engine::Math::ParametricPlane::getDistanceFromOrigin() const
{
	return distance;
}





