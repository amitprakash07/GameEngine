#include "Math.h"

float getPlaneDistanceFromOrigin(
	Engine::Math::Vector3 iNormal, Engine::Math::Vector3 iPointOnPlane)
{
	float a = iNormal.x;
	float b = iNormal.y;
	float c = iNormal.z;
	float d = a*iPointOnPlane.x + b*iPointOnPlane.y + c * iPointOnPlane.z;
	return -d;
}