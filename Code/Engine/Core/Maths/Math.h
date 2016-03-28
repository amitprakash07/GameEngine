#ifndef __MATHS_H
#define __MATHS_H

#include "Vector3.h"


namespace Engine
{
	namespace Math
	{
		class ParametricPlane
		{
		public:
			Math::Vector3 getPlaneNormal() const;
			float getDistanceFromOrigin() const;
			ParametricPlane(Vector3 iNormal,Vector3 iPointOnPlane);
		private:
			Vector3 normal;
			float distance;
		};
	}
}

#endif