#ifndef RESOURCE_MGR_H
#define RESOURCE_MGR_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "../commen/dataTypes.h"
#include "../graphics/mesh3D.h"

namespace robolab {
	using namespace graphics;
	namespace manager {

		namespace internal
		{
			inline std::size_t getUniqueMeshID() noexcept
			{
				static std::size_t lastMeshID{ 0u };
				return lastMeshID++;
			}
		}

		class ResourceMgr {
		public:
			using BitwiseMeshUsageType = int;
			enum MeshUsageType {
				MESH_RENDERING = 1,
				MESH_PHYSIC_SIMULATION = 2
			};
		private:
			enum FileExtention {
				FILE_OBJ,
				FILE_STL
			};
			static bool isInitialized;
		private:
			static std::unordered_map<std::string, FileExtention> filesExtentionList;
			static std::unordered_map<std::string, std::shared_ptr<MeshDataBuffers>> renderMeshData;
			static std::unordered_map<std::string, std::vector<std::shared_ptr<MeshDataBuffers>>> physicMeshData;
			static std::shared_ptr<MeshDataBuffers> loadMesh(const Path& path, Vec3f& scaleFactor);
		public:
			static bool initialize();
			static void loadMeshFile(const std::string& directory, const std::string& meshName, BitwiseMeshUsageType usageType, Vec3f& scaleFactor = Vec3f(1.0f));
			static bool hasRenderMesh(const std::string& meshName);
			static bool existPhysicMesh(const std::string& meshName);
			static const std::shared_ptr<MeshDataBuffers> getRenderMesh(const std::string& meshName);
			static const std::vector<std::shared_ptr<MeshDataBuffers>> getPhysicMesh(const std::string& meshName);
			static std::shared_ptr<MeshDataBuffers> createCube(const std::string& meshName, float lenght, float width, float height, Vec3f& pivot);
			static void shutdown();
		};

	}
}
#endif // !RESOURCE_H

