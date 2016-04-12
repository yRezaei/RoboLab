#include "resourceMgr.h"

#include <algorithm>
#include "../utils/fileIO.h"
#include "../graphics/geometry.h"
#include "../system/logging.h"



namespace robolab {
	using namespace utils;
	using namespace graphics;

	namespace manager {

		bool ResourceMgr::isInitialized = false;
		std::unordered_map<std::string, std::shared_ptr<MeshDataBuffers>> ResourceMgr::renderMeshData;
		std::unordered_map<std::string, std::vector<std::shared_ptr<MeshDataBuffers>>> ResourceMgr::physicMeshData;
		std::unordered_map<std::string, ResourceMgr::FileExtention> ResourceMgr::filesExtentionList {
			{"OBJ", FILE_OBJ },
			{"obj", FILE_OBJ },
			{"STL", FILE_STL },
			{"stl", FILE_STL }
		};

		//#########################################################################

		bool ResourceMgr::initialize() {
			if (!isInitialized)
			{
				isInitialized = true;
			}
				
			return isInitialized;
		}


		void ResourceMgr::loadMeshFile(const std::string& dir, const std::string& meshName, ResourceMgr::BitwiseMeshUsageType usageType, Vec3f& scaleFactor) {
			Path directory;
			if (dir.back() != '/' || dir.back() != '\\')
				directory = Path(dir + "/");
			else
				directory = Path(dir);
			std::vector<Path> fileList;
			if(directory.isDirectory())
				fileList = fileIO::getAllFileInDirectory(directory, meshName);
			else
			{
				system::Logging::console(system::LOG_WARNING, "The given directory contains file name \"" + directory.getFileName()+ "\".", __func__);
				system::Logging::console(system::LOG_WARNING, "The directory\"" + directory.parent().toString() + "\" will be used instead.", __func__);
				directory = directory.parent();
				fileList = fileIO::getAllFileInDirectory(directory, meshName);
			}

			if (fileList.size() > 0)
			{
				if (usageType & MESH_RENDERING) 
				{
					bool isRenderableMeshFound = false;
					for (auto path : fileList)
					{
						if (path.getBaseName() == meshName && filesExtentionList.find(path.getExtension()) != filesExtentionList.end()) {
							renderMeshData[meshName] = loadMesh(path, scaleFactor);
							isRenderableMeshFound = true;
							system::Logging::console(system::LOG_INFORMATION, "The mesh \"" + path.getFileName() + "\" is loaded successfully");
							break;
						}
					}
					if(!isRenderableMeshFound)
						system::Logging::console(system::LOG_ERROR, "No mesh with name \"" + meshName
							+ "\" is found in \"" + directory.toString() + "\" directory.", __func__);
				}
				if (usageType & MESH_PHYSIC_SIMULATION) {
					bool isPhysicMeshFound = false;
					std::vector<std::shared_ptr<MeshDataBuffers>> physicMeshs;
					for (auto path : fileList)
					{
						if (path.getBaseName().find(meshName + "_Physx") != std::string::npos  && filesExtentionList.find(path.getExtension()) != filesExtentionList.end()) {
							 physicMeshs.push_back( loadMesh(path, scaleFactor) );
							isPhysicMeshFound = true;
							system::Logging::console(system::LOG_INFORMATION, "The mesh \"" + path.getFileName() + "\" is loaded successfully");
						}
					}
					if (!isPhysicMeshFound)
						system::Logging::console(system::LOG_ERROR, "No mesh with name \"" + meshName + "_Physx"
							+ "\" is found in \"" + directory.toString() + "\" directory.", __func__);
					else
						physicMeshData[meshName] = physicMeshs;
				}
			}
			else {
				system::Logging::console(system::LOG_ERROR, "No mesh file found that contains \"" + meshName + "\".", __func__);
			}
		}

		std::shared_ptr<MeshDataBuffers> ResourceMgr::loadMesh(const Path& path, Vec3f& scaleFactor) {
			std::shared_ptr<MeshDataBuffers> meshBuffer = nullptr;
			switch (filesExtentionList[path.getExtension()])
			{
			case FILE_OBJ:
			{
				meshBuffer = std::make_shared<MeshDataBuffers>(internal::getUniqueMeshID(), path.getBaseName());
				fileIO::obj::load(path, meshBuffer, scaleFactor);
				return meshBuffer;
			}
			break;
			default:
				system::Logging::console(system::LOG_ERROR, "The \"" + path.getExtension() + "\" extention is not supported yet.");
				return nullptr;
				break;
			}
		}

		bool ResourceMgr::existRenderMesh(const std::string& meshName) {
			if (renderMeshData.find(meshName) != renderMeshData.end())
				return true;
			else
				return false;
		}

		bool ResourceMgr::existPhysicMesh(const std::string& meshName) {
			if (physicMeshData.find(meshName) != physicMeshData.end())
				return true;
			else
				return false;
		}

		const std::shared_ptr<MeshDataBuffers> ResourceMgr::getRenderMesh(const std::string& meshName) {
			return renderMeshData[meshName];
		}

		const std::vector<std::shared_ptr<MeshDataBuffers>> ResourceMgr::getPhysicMesh(const std::string& meshName) {
			return physicMeshData[meshName];
		}

		std::shared_ptr<MeshDataBuffers> ResourceMgr::createCube(const std::string& meshName, float lenght, float width, float height, Vec3f& pivot) {
			std::shared_ptr<MeshDataBuffers> meshBuffer = std::make_shared<MeshDataBuffers>(internal::getUniqueMeshID(), meshName);
			geometry::createCube(meshBuffer, lenght, width, height, pivot);
			renderMeshData[meshName] = meshBuffer;
			return meshBuffer;
		}

		void ResourceMgr::shutdown() {

		}


	}// ! namespace manager
}// ! namespace robolab