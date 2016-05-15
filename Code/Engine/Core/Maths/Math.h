#ifndef __MATHS_H
#define __MATHS_H

#include "Vector3.h"

namespace Engine
{
	namespace Math
	{
		class Plane
		{
		public:
			static Plane ComputePlane(Vector3 iA, Vector3 iB, Vector3 iC);
			Vector3 ClosestPointFromPointOnPlane(Vector3 iPointOnPlane)const ;
			Math::Vector3 getPlaneNormal() const;
			float getDistanceFromOrigin() const;
			Plane(Vector3 iNormal,Vector3 iPointOnPlane);	
			Plane(){}
			Vector3 normal;
			float distance;
		};

		class Sphere
		{
		public: 
			bool IntersectSphere(Sphere iOther) const;
			Vector3 centre;
			float radius;
		};

		void ClosestPointFromPointOnLineSegment(Vector3 c,
			Vector3 a,
			Vector3 b,
			float &t,
			Vector3 &d);

		// Returns the squared distance between point c and segment ab
		float SqDistPointSegment(Vector3 a, Vector3 b, Vector3 c);
	}
}

#endif