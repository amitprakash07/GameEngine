#include <iostream>
#include "../Engine/Windows/WindowsFunctions.h"
#include "../Engine/Core/Maths/Transform.h"
#include "../Engine/Core/Maths/Functions.h"

using namespace Engine::Math;

int main()
{
	Vector3 a = Vector3(-1.0f, -1.0f, 1.0f);
	Vector3 b = Vector3(1.0f, -1.0f, 1.0f);
	Vector3 c = Vector3(1.0f, 1.0f, 1.0f);
	Vector3 d = Vector3(-1.0f, 1.0f, 1.0f);

	Vector3 e = Vector3(-1.0f, -1.0f, -1.0f);
	Vector3 f = Vector3(1.0f, -1.0f, -1.0f);
	Vector3 g = Vector3(1.0f, 1.0f, -1.0f);
	Vector3 h = Vector3(-1.0f, 1.0f, -1.0f);

	Matrix4x4 changeMatrix = Matrix4x4(Engine::Math::Quaternion(Engine::Math::ConvertDegreesToRadians(45.0f),
		Engine::Math::Vector3(0.0f, 1.0f, 0.0f)));

	changeMatrix.mul(a).printVector();
	changeMatrix.mul(b).printVector();
	changeMatrix.mul(c).printVector();
	changeMatrix.mul(d).printVector();

	changeMatrix.mul(e).printVector();
	changeMatrix.mul(f).printVector();
	changeMatrix.mul(g).printVector();
	changeMatrix.mul(h).printVector();
}
