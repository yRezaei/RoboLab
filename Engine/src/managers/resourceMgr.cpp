#include "resourceMgr.h"

#include <algorithm>
#include "../utils/fileIO.h"
#include "../utils/utility.h"
#include "../graphics/geometry.h"
#include "../system/logging.h"



namespace robolab {
	using namespace utils;
	using namespace graphics;

	namespace manager {

		std::vector<std::shared_ptr<Mesh>> ResourceMgr::emptyPhysicalMesh;
		bool ResourceMgr::isInitialized = false;
		std::unordered_map<std::string, std::shared_ptr<Mesh>> ResourceMgr::visualMeshList;
		std::unordered_map<std::string, std::vector<std::shared_ptr<Mesh>>> ResourceMgr::physicalMeshList;
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


		void ResourceMgr::loadMesh(MeshUsageType type, const std::string& directory, const std::string& meshName, Vec3f& scaleFactor) {
			Path path(directory);
			if (!path.isDirectory())
				return;

			std::vector<Path> fileList;
			if (path.isDirectory())
				fileList = getListOfFiles(directory, meshName);

			std::shared_ptr<Mesh> mesh;
			switch (type)
			{
			case MeshUsageType::VISUALIZATION:
				mesh = fileIO::obj::load(path, scaleFactor);
				break;
			case MeshUsageType::PHYSIC_SIMULATION:
				break;
			default:
				break;
			}
			//###########################################
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
				if (type & MeshUsageType::VISUALIZATION)
				{
					bool isRenderableMeshFound = false;
					for (auto path : fileList)
					{
						if (path.getBaseName() == meshName && filesExtentionList.find(path.getExtension()) != filesExtentionList.end()) {
							visualMeshList[meshName] = loadMesh(path, scaleFactor);
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
					std::vector<std::shared_ptr<Mesh>> physicalMesh;
					for (auto path : fileList)
					{
						if (path.getBaseName().find(meshName + "_Physx") != std::string::npos  && filesExtentionList.find(path.getExtension()) != filesExtentionList.end()) {
							physicalMesh.push_back( loadMesh(path, scaleFactor) );
							isPhysicMeshFound = true;
							system::Logging::console(system::LOG_INFORMATION, "The mesh \"" + path.getFileName() + "\" is loaded successfully");
						}
					}
					if (!isPhysicMeshFound)
						system::Logging::console(system::LOG_ERROR, "No mesh with name \"" + meshName + "_Physx"
							+ "\" is found in \"" + directory.toString() + "\" directory.", __func__);
					else
						physicalMeshList[meshName] = physicalMesh;
				}
			}
			else {
				system::Logging::console(system::LOG_ERROR, "No mesh file found that contains \"" + meshName + "\".", __func__);
			}
		}

		void ResourceMgr::addVisualMesh(VisualMesh& visualMesh) {
			if (visualMeshList.find(visualMesh.name) == visualMeshList.end())
				visualMeshList[visualMesh.name] = visualMesh;
		}

		void ResourceMgr::addPhysicalMesh(PhysicalMesh& physicalMesh) {
			if (physicalMeshList.find(physicalMesh.name) == physicalMeshList.end())
				physicalMeshList[physicalMesh.name] = physicalMesh;
		}

		void ResourceMgr::loadMesh(const Path& path, Vec3f& scaleFactor) {
			std::shared_ptr<Mesh> meshBuffer = nullptr;
			switch (filesExtentionList[path.getExtension()])
			{
			case FILE_OBJ:
			{
				meshBuffer = std::make_shared<Mesh>(internal::getUniqueMeshID(), path.getBaseName());
				fileIO::obj::load(path, scaleFactor);
				return meshBuffer;
			}
			break;
			default:
				system::Logging::console(system::LOG_ERROR, "The \"" + path.getExtension() + "\" extention is not supported yet.");
				return nullptr;
				break;
			}
		}



		const std::shared_ptr<Mesh> ResourceMgr::getVisualMesh(const std::string& meshName) {
			if (visualMeshList.find(meshName) != visualMeshList.end())
				return visualMeshList[meshName];
			else
				return nullptr;
		}

		const std::vector<std::shared_ptr<Mesh>>& ResourceMgr::getPhysicalMesh(const std::string& meshName) {
			if (physicalMeshList.find(meshName) != physicalMeshList.end())
				return physicalMeshList[meshName];
			else
				return emptyPhysicalMesh;
		}

		std::shared_ptr<Mesh> ResourceMgr::createCube(const std::string& meshName, float lenght, float width, float height, Vec3f& pivot) {
			std::shared_ptr<Mesh> meshBuffer = std::make_shared<Mesh>(internal::getUniqueMeshID(), meshName);
			geometry::createCube(meshBuffer, lenght, width, height, pivot);
			visualMeshList[meshName] = meshBuffer;
			return meshBuffer;
		}

		void ResourceMgr::shutdown() {

		}


	}// ! namespace manager
}// ! namespace robolab