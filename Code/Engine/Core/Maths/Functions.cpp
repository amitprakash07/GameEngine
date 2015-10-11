// Header Files
//=============

#include "Functions.h"

// Static Data Initialization
//===========================

const float Engine::Math::Pi = 3.141592654f;

// Interface
//==========

float Engine::Math::ConvertDegreesToRadians( const float i_degrees )
{
	return i_degrees * Pi / 180.0f;
}
