#ifndef __PHYSICS_SYSTEM_H
#define __PHYSICS_SYSTEM_H

#ifdef PLATFORM_OPEN_GL
#include "../../../Externals/OpenGLExtensions/OpenGlExtensions.h"
#elif PLATFORM_D3D
#include <d3d9.h>
#endif

#include "../Utilities/SharedPointer.h"
#include "../../Graphics/Mesh.h"
#include "../Physics/RayIntersection.h"
#include "../EngineCore/Objects/MeshObject.h"
#include "../../Graphics/Line.h"


namespace Engine
{
	namespace Physics
	{
		class HitInfo;

		class PhysicsSystem
		{
		public:
			static void InitializePhysicsSystem(std::string iCollisionMesh);
			static SharedPointer<PhysicsSystem> GetPhysicsSystem();
			static bool ShowCollisionMesh();
			static void DrawCollisionMesh();
			static void SetShowCollisionMesh(bool iRequest);
			static void EnableCollisionDebugging(bool iRequest);
			static bool CollisionDebuggingStatus();
			bool CheckCollision(Physics::Ray iRay, HitInfo& iHitInfo) const;
			bool CheckCollision(Math::Vector3 startPoint,
				Math::Vector3 endPoint, HitInfo& iHitInfo);
			bool IntersectTriangle(Math::Vector3 startPoint,
				Math::Vector3 EndPoint, Triangle iTriangle,
				HitInfo& iHitInfo) const;
		private:
			static SharedPointer<PhysicsSystem> mPhysicsSystem;
			SharedPointer<Graphics::Mesh> mCollisionMesh;
			SharedPointer<Engine::MeshObject> mMeshObject;
			SharedPointer<Engine::Graphics::Line> AB;
			SharedPointer<Engine::Graphics::Line> BC;
			SharedPointer<Engine::Graphics::Line> AC;
			std::string collisionMeshName;
			bool showCollisionMesh;
			bool collisionDebugging;
			PhysicsSystem();
		};
	}
}


#endif