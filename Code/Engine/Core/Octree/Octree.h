#ifndef _OCTREE_H
#define _OCTREE_H

#include <vector>
#include "../Maths/Vector3.h"

namespace Engine 
{
	namespace Physics 
	{
		struct TriangleIndex
		{
			TriangleIndex() = default;
			union
			{
				uint32_t _indices[3];
				struct
				{
					uint32_t index0;
					uint32_t index1;
					uint32_t index2;
				};
			};
		};

		struct OctreeNode
		{
			Engine::Math::Vector3 pos;
			Engine::Math::Vector3 extent;
			std::vector<TriangleIndex> triangles;
			Engine::Math::Vector3 GetMin() const
			{
				return pos - extent;
			}
			Engine::Math::Vector3 GetMax() const
			{
				return pos + extent;
			}
		};
			

		class Octree
		{
		public: 
			Octree();
			~Octree();
			void InitFromRange(uint32_t level, Engine::Math::Vector3 min, Engine::Math::Vector3 max);
			void InitFromFile(const char* pFile);
			OctreeNode* GetNodesInLevel(uint32_t levelIndex) const;
			uint32_t GetCountOfNodesInLevel(uint32_t levelIndex) const;			
			uint32_t GetNodeCount() const;
			OctreeNode* GetNodes() const;
			Engine::Math::Vector3 GetMin() const;
			Engine::Math::Vector3 GetMax() const;
			uint32_t Level() const;

		private:
			uint32_t mLevel;
			OctreeNode* mNodes;
			uint32_t mCountOfNode;
			Engine::Math::Vector3 min;
			Engine::Math::Vector3 max;
		};

		
	}
}


#endif