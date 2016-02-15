#include "Line.h"

std::vector<Engine::SharedPointer<Engine::Graphics::Line>>
Engine::Graphics::Line::mLineList;

Engine::Graphics::Line::Line()
{
	debugObject = true;
}

bool Engine::Graphics::Line::containsDebugLine()
{
	return mLineList.size();
}



void Engine::Graphics::Line::AddLine(Engine::Maths::Point3 i_startPoint, Engine::Maths::Point3 i_endPoint, RGBAColor iLineColor)
{
	SharedPointer<Line> tempLine = SharedPointer<Line>(new Line(), "Engine::Graphics::Line");
	tempLine->mLineStruct.startPoint = i_startPoint;
	tempLine->mLineStruct.endPoint = i_endPoint;
	tempLine->mLineStruct.color = iLineColor;
	tempLine->debugObject = true;
	mLineList.push_back(tempLine);
}

Engine::Transformation Engine::Graphics::Line::getTransformation()
{
	return Transformation();
}

void Engine::Graphics::Line::setTransformation(Math::cVector, Math::cQuaternion)
{}


bool Engine::Graphics::Line::isDebugObject() const
{
	return debugObject;
}


bool Engine::Graphics::Line::isRenderable() const
{
	return true;
}


void Engine::Graphics::Line::draw(bool drawDebugObject)
{

}








