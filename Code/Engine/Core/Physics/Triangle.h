#ifndef __TRIANGLE_H
#define __TRIANGLE_H

#include "../../Graphics/typedefs.h"

namespace Engine
{
	namespace Physics
	{
		class Triangle
		{
		public:
			// Returns 2 times the signed triangle area. The result is positive if
			// abc is ccw, negative if abc is cw, zero if abc is degenerate.
			float Signed2DTriArea() const;
			//Counter ClockWise Direction
			Graphics::vertex vertexA;
			Graphics::vertex vertexB;
			Graphics::vertex vertexC;
		};
	}
}

#endif