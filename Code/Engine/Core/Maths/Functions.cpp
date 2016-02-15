// Header Files
//=============

#include "Functions.h"

// Static Data Initialization
//===========================

const float Engine::Math::Pi = 3.141592654f;

// Interface
//==========

float Engine::Math::ConvertDegreesToRadians(const float i_degrees)
{
	return i_degrees * Pi / 180.0f;
}

bool Engine::Math::InRange(float valToCheck, float min,
	float max, bool minInclusive, bool maxInclusive)
{
	if (minInclusive && maxInclusive)
		return (valToCheck >= min && valToCheck <= max) ? true : false;
	else if (minInclusive)
		return (valToCheck >= min && valToCheck < max) ? true : false;
	else
		return (valToCheck > min && valToCheck <= max) ? true : false;
}

float Engine::Math::scaleAndBias(float valueToConvert,
	float oldRangeMin,
	float oldRangeMax,
	float newRangeMin,
	float newRangeMax)
{
	/*
	Scale and Bias Operation Formulae
	old			New
	[a,b]		[c,d]
	newValue = (oldValue - oldRangeMin) * (ratio of new range difference to old range difference) + new Range Minimum
	newVal = ((oldVal - a) * ((d-c)/(b-a))) + c
	*/
	float ratioToMaintain = (newRangeMax - newRangeMin) / (oldRangeMax - oldRangeMin);
	return(((valueToConvert - oldRangeMin)*ratioToMaintain) + newRangeMin);
}
