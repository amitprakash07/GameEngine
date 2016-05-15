#ifndef __RAY_INTERSECTION_H
#define __RAY_INTERSECTION_H

#include "../Maths/Vector3.h"
#include "../Maths/Math.h"
#include "BoundingBox.h"

#define BIG_FLOAT 1.0e30f

namespace Engine
{
	namespace Physics
	{
		class HitInfo
		{
		public:
			Math::Vector3 hitPoint;
			Math::Vector3 normal;
			float distance;	
			HitInfo();
			
		};

		class Ray
		{
		public:
			bool IntersectTriangle(Math::Vector3 a,
				Math::Vector3 b, 
				Math::Vector3 c,
				HitInfo& iHitInfo)const;
			bool IntersectTriangle(
				Math::Vector3 vertexA,
				Math::Vector3 vertexB,
				Math::Vector3 vertexC,
				Math::Vector3 rayStartPoint,
				Math::Vector3 rayEndPoint,
				HitInfo& iHitInfo
			);
			bool IntersectBox(BoundingBox, HitInfo &iHitInfo) const;
			bool IntersectPlane(Math::Plane, HitInfo &iHitInfo) const;
			bool InstersectSphere(Math::Sphere, HitInfo &iHitInfo) const;
			Math::Vector3 origin;
			Math::Vector3 direction;
		};	
	}
}


#endif
