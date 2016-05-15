#include "BoundingBox.h"

bool Engine::Physics::BoundingBox::CheckCollisionWithOther(BoundingBox iOther) const
{
	if (max.x < iOther.min.x || min.x > iOther.max.x) return 0;
	if (max.y < iOther.min.y || min.y > iOther.max.y) return 0;
	if (max.z < iOther.min.z || min.z > iOther.max.z) return 0;

	return true;
}


// Computes the square distance between a point p and an AABB b
float Engine::Physics::BoundingBox::SquareDistancePoint(Math::Vector3 iPoint)
{
	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++) {
		// For each axis count any excess distance outside box extents
		float v = iPoint[i];
		if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
	}
	return sqDist;
}

void Engine::Physics::BoundingBox::ClosestPtPointAABB(Math::Vector3 p, Math::Vector3& q)
{
	// For each coordinate axis, if the point coordinate value is
	// outside box, clamp it to the box, else keep it as is

	for (int i = 0; i < 3; i++)
	{
		float v = p[i];
		if (v < min[i]) v = min[i]; // v = max(v, b.min[i])
		if (v > max[i]) v = max[i]; // v = min(v, b.max[i])
		q[i] = v;
	}
}


float Engine::Physics::BoundingBox::SqDistPointAABB(Math::Vector3 iPoint)
{
	// Computes the square distance between a point p and an AABB b
	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++) {
		// For each axis count any excess distance outside box extents
		float v = iPoint[i];
		if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
	}
	return sqDist;
}

