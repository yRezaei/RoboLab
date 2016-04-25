#ifndef MESH_3D_H
#define MESH_3D_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "../mathematic/math3D.h"
#include "bounds.h"


namespace robolab {
	using namespace math3D;

	namespace graphics {

		using uint = unsigned int;

		struct MeshDataBuffers {
		private:
			std::size_t uniqueID; 
			std::string meshName;
		public:
			Indices rowIndices;
			Vertices rowVertices;
			Vertices vertices;
			Normals normals;
			Colors colors;
			Indices indices;
			Bounds bounds;
			MeshDataBuffers(std::size_t UniqueID, const std::string& MeshName) 
				: uniqueID(UniqueID), meshName(MeshName) {}
			bool operator == (const MeshDataBuffers& meshDataBuffers)
			{
				if (uniqueID == meshDataBuffers.uniqueID)
					return true;
				else
					return false;
			}
			const std::size_t& getID() {
				return uniqueID;
			}
			const std::string& getName() {
				return meshName;
			}
		};

		struct GLBufferIDs {
		private:
			std::size_t uniqueID;
			std::string meshName;
		public:
			uint VAO;
			std::unordered_map<std::string, unsigned int> attributesID;
			uint indexID;
			std::size_t indexSize;
			GLBufferIDs(std::size_t UniqueID, std::string MeshName, uint vao, uint index, std::size_t IndexSize, std::unordered_map<std::string, unsigned int>& AttributesID)
				: uniqueID(UniqueID), meshName(MeshName), VAO(vao), indexID(index), indexSize(IndexSize), attributesID(AttributesID) {}
			bool operator == (const GLBufferIDs& glBufferIDs)
			{
				if (uniqueID == glBufferIDs.uniqueID)
					return true;
				else
					return false;
			}

			const std::size_t& getID() {
				return uniqueID;
			}
			const std::string& getName() {
				return meshName;
			}

		};

		struct GLShaderIDs {
			uint shaderID;
			std::unordered_map<std::string, unsigned int> locationIDs;
			GLShaderIDs(uint ShaderID, std::unordered_map<std::string, unsigned int>& LocationIDs) 
				: shaderID(ShaderID), locationIDs(LocationIDs) {}
		};

		struct RenderableObject {
			std::size_t index;
			std::shared_ptr<GLBufferIDs> gLIDs;
			RenderableObject(std::size_t Index, std::shared_ptr<GLBufferIDs> GLIDs)
				: index(Index), gLIDs(GLIDs) {}
		};

		struct PhysicalProperty
		{
			float mass;
			float density;
			float friction;
			float dynamicFriction;
			float restitution;
			float angularDamping;
			float linearDamping;

			PhysicalProperty() {
				this->mass = 1.3f;
				this->density = 0.7f;
				this->friction = 0.7f;
				this->dynamicFriction = 0.7f;
				this->restitution = 0.4f;
				this->angularDamping = 0.3f;
				this->linearDamping = 0.3f;
			}

			PhysicalProperty(float mass, float density, float friction, float dynamicFriction,
				float restitution, float angularDamping, float linearDamping) {
				this->mass = mass;
				this->density = density;
				this->friction = friction;
				this->dynamicFriction = dynamicFriction;
				this->restitution = restitution;
				this->angularDamping = angularDamping;
				this->linearDamping = linearDamping;
			}
		};
	}
}


#endif // !MESH_DATA_H

