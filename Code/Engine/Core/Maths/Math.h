#ifndef __MATHS_H
#define __MATHS_H

#include "Vector3.h"


namespace Engine
{
	namespace Math
	{
		float getPlaneDistanceFromOrigin(Vector3 iNormal, 
			Vector3 iPointOnPlane);
	}
}

#endif