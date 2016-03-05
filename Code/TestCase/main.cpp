#include <iostream>
#include "../Engine/Windows/WindowsFunctions.h"
#include "../Engine/Core/Maths/Transform.h"
#include "../Engine/Core/Maths/Functions.h"

using namespace Engine::Math;

int main()
{
	/*WindowsUtil::setVSEnvironmentVariableValue("Hello", "kjhsdkjfhdskjfhdksj");
	std::string valueData;
	WindowsUtil::GetVSEnvironmentVariable("Hello", valueData);
	std::cout << valueData;*/
	/*Engine::Math::Transform testTransform;
	testTransform.setOrientation(Quaternion::getYaw(Engine::Math::ConvertDegreesToRadians(180.0f)));
	testTransform.printTransform();
	
	Engine::Math::Matrix4x4 tempMatrix =
		Engine::Math::Matrix4x4(Vector3(10,1,1));

	tempMatrix.printMatrix4x4();
	
	Quaternion qYaw = Quaternion::getYaw(ConvertDegreesToRadians(180));
	Matrix4x4 yawMAtrix = Matrix4x4(qYaw);

	yawMAtrix.printMatrix4x4();

	// Order translate * yaw *pitch * roll
	yawMAtrix = yawMAtrix * tempMatrix;
	yawMAtrix.printMatrix4x4();*/
	/*Matrix4x4 rollMatrix = Matrix4x4(Quaternion::getRoll(ConvertDegreesToRadians(0)));
	Matrix4x4 pitchMatrix = Matrix4x4(Quaternion::getPitch(ConvertDegreesToRadians(0)));*/
	Matrix4x4 yawMAtrix = Matrix4x4(Quaternion::getYaw(ConvertDegreesToRadians(180)));;
	/*Matrix4x4 translateMatrix = Matrix4x4(Vector3(-10.0f, -1.0f, -1.0f));*/
	yawMAtrix.mul(Vector3(1, 1, 0)).printVector();
	/*Matrix4x4 inverseMatrix = rollMatrix * pitchMatrix * yawMAtrix * translateMatrix;*/
//	inverseMatrix.printMatrix4x4();

	/*Quaternion q1 = Quaternion::getYaw(ConvertDegreesToRadians(0))
		* Quaternion::getPitch(ConvertDegreesToRadians(180))* Quaternion::getRoll(ConvertDegreesToRadians(90));
	(q1 * Vector3(1, 1, 1)).printVector();*/
	/*Quaternion q2 = Quaternion::getPitch(ConvertDegreesToRadians(90));
	q1.printQuaternion();
	q2.printQuaternion();
	Quaternion q3 = q1 * q2;
	q3.printQuaternion();*/

	//Vector3 newPosition = tempMatrix.mul(Vector3(0, 0, 0));
	//tempMatrix.printMatrix4x4();
	//newPosition.printVector();
}
