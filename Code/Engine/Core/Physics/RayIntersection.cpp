#include "RayIntersection.h"


Engine::Physics::HitInfo::HitInfo()
{
	hitPoint = Math::Vector3();
	normal = Math::Vector3();
	distance = BIG_FLOAT;
}



// Intersects ray r = p + td, |d| = 1, with sphere s and, if intersecting,
// returns t value of intersection and intersection point q
bool Engine::Physics::Ray::InstersectSphere(Math::Sphere sphere, HitInfo& iHitInfo) const
{
	Math::Vector3 m = origin - sphere.centre;
	float b = m.dot(direction);
	float c = m.dot(m) - sphere.radius*sphere.radius;

	// Exit if r’s origin outside s (c > 0) and r pointing away from s (b > 0)
	if (c > 0.0f && b > 0.0f)
		return false;

	float discr = b*b - c;
	// A negative discriminant corresponds to ray missing sphere
	if (discr < 0.0f)
		return false;

	// Ray now found to intersect sphere, compute smallest t value of intersection
	iHitInfo.distance = -b - sqrtf(discr);
	// If t is negative, ray started inside sphere so clamp t to zero
	if (iHitInfo.distance < 0.0f)
		iHitInfo.distance = 0.0f;
	iHitInfo.hitPoint = origin + direction * iHitInfo.distance;
	return true;

}

bool Engine::Physics::Ray::IntersectBox(BoundingBox box, HitInfo& iHitInfo) const
{
	// Intersect ray R(t) = p + t*d against AABB a. When intersecting,
	// return intersection distance tmin and point q of intersection

	bool isHit = false;
	float tx1, tx2, txEntry, txExit;
	float ty1, ty2, tyEntry, tyExit;
	float tz1, tz2, tzEntry, tzExit;

	tx1 = tx2 = txEntry = txExit = ty1 = ty2 = tyEntry = tyExit = tz1 = tz2 = tzEntry = tzExit = BIG_FLOAT;

	//Check X-Normal
	if (direction.x != 0.0f)
	{
		tx1 = (-origin.x + box.min.x) / direction.x;
		tx2 = (-origin.x + box.max.x) / direction.x;

		txEntry = tx1 < tx2 ? tx1 : tx2;
		txExit = tx1 > tx2 ? tx1 : tx2;
	}
	else
	{
		if (origin.x > box.max.x || origin.x < box.min.x)
			return false;
	}


	//Check y-Plane
	if (direction.y != 0.0f)
	{
		ty1 = (-origin.y + box.min.y) / direction.y;
		ty2 = (-origin.y + box.max.y) / direction.y;
		tyEntry = ty1 < ty2 ? ty1 : ty2;
		tyExit = ty1 > ty2 ? ty1 : ty2;
	}
	else
	{
		if (origin.y > box.max.y || origin.y < box.min.y)
			return false;
	}

	//Check z-Plane
	if (direction.z != 0.0f)
	{
		tz1 = (-origin.z + box.min.z) / direction.z;
		tz2 = (-origin.z + box.max.z) / direction.z;
		tzEntry = tz1 < tz2 ? tz1 : tz2;
		tzExit = tz1 > tz2 ? tz1 : tz2;
	}
	else
	{
		if (origin.z > box.max.z || origin.z < box.min.z)
			return false;
	}


	float tEntry = (txEntry > (tyEntry > tzEntry ? tyEntry : tzEntry)) ? txEntry : (tyEntry > tzEntry ? tyEntry : tzEntry);
	float tExit = txExit < (tyExit < tzExit ? tyExit : tzExit) ? txExit : (tyExit < tzExit ? tyExit : tzExit);

	if (tEntry < tExit)
	{
		/*t_max = tEntry;*/
		isHit = true;
		//std::cout << "\nBox InterSection Successful";
	}

	//std::cout << "\nBox InterSection UnSuccessful";
	return isHit;
}


bool Engine::Physics::Ray::IntersectPlane(Math::Plane iPlane, HitInfo& iHitInfo) const
{
	float t = (iPlane.distance - iPlane.normal.dot(origin)) / iPlane.normal.dot(direction);
	
	if(t >= 0.0f && t<=1.0f)
	{
		iHitInfo.hitPoint = origin + direction * t;
		iHitInfo.distance = t;
		iHitInfo.normal = Math::Vector3(0, 0, 1);
		return true;
	}
	return false;
}


bool Engine::Physics::Ray::IntersectTriangle(Math::Vector3 vertexA, 
	Math::Vector3 vertexB,
	Math::Vector3 vertexC,
	HitInfo& iHitInfo) const
{

	Math::Vector3 normal = (vertexB - vertexA).Cross(vertexC - vertexA);
	Math::Vector3 faceNormalNormalized = normal.CreateNormalized();
	
	if (direction.dot(faceNormalNormalized) == 0)
		return false;

	float  t = (-(origin - vertexA)).dot(faceNormalNormalized) / direction.dot(faceNormalNormalized);

	if ((origin - vertexA).dot(faceNormalNormalized) == 0)
		return false;

	bool isHit = false;
	if(t <iHitInfo.distance)
	{
		Math::Vector3 p = origin + direction * t;
		iHitInfo.hitPoint = p;
		iHitInfo.normal = faceNormalNormalized;
		iHitInfo.distance = t;
		isHit =  true;
	}

	return isHit;	
}


bool Engine::Physics::Ray::IntersectTriangle(Math::Vector3 vertexA, 
	Math::Vector3 vertexB, 
	Math::Vector3 vertexC, 
	Math::Vector3 rayStartPoint, 
	Math::Vector3 rayEndPoint, 
	HitInfo& iHitInfo)
{
	return true;
}




