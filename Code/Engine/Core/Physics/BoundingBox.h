#ifndef __BOUNDING_BOX_H
#define __BOUNDING_BOX_H
#include "../Maths/Vector3.h"


namespace Engine
{
	namespace Physics
	{
		class BoundingBox
		{
		public:
			bool CheckCollisionWithOther(BoundingBox iOther) const;
			// Computes the square distance between a point p and an AABB b
			float SquareDistancePoint(Engine::Math::Vector3 iPoint);
			// Given point p, return the point q on or in AABB b that is closest to p
			void ClosestPtPointAABB(Math::Vector3 p, Math::Vector3 &q);	
			float SqDistPointAABB(Math::Vector3 iPoint);		
			Engine::Math::Vector3 min;
			Engine::Math::Vector3 max;
		};
	}

}




#endif

