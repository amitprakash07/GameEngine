/*
This file contains math-related functions
*/

#ifndef _MATH_FUNCTIONS_H
#define _MATH_FUNCTIONS_H

namespace Engine
{
	namespace Math
	{
		// Interface
		//==========

		extern const float Pi;

		float ConvertDegreesToRadians(const float i_degrees);
		bool InRange(float valToCheck, float min, float max,
			bool minInclusive = true, bool maxInclusive = true);
		float scaleAndBias(float valueToConvert,
			float oldRangeMin,
			float oldRangeMax,
			float newRangeMin,
			float newRangeMax);
	}
}

#endif	// EAE6320_MATH_FUNCTIONS_H
