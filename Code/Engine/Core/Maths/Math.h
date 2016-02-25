#ifndef __MATHS_H
#define __MATHS_H
#include "Quaternion.h"
#include "Vector3.h"


namespace Engine
{
	namespace Math
	{

		struct Transformation
		{
			Engine::Math::Vector3 mPositionOffset;
			Engine::Math::Quaternion mOrientation;
			Transformation()
			{
				mPositionOffset = Engine::Math::Vector3();
				mOrientation = Engine::Math::Quaternion();
			}
		};

		struct Point2
		{
			float x;
			float y;
		};

		struct Point3
		{
			float x;
			float y;
			float z;

			Point3()
			{
				x = y = z = 0.0f;
			}
			Point3(Point3& i_point3)
			{
				x = i_point3.x;
				y = i_point3.y;
				z = i_point3.z;
			}

			Point3(float i_x, float i_y, float i_z)
			{
				x = i_x;
				y = i_y;
				z = i_z;
			}

			bool operator == (const Point3 &i_point2) const
			{
				if ((x == i_point2.x)
					&& (y == i_point2.y)
					&& (z == i_point2.z))
					return true;
				return false;
			}
		};
	}
}

#endif