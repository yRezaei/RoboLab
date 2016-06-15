#include "resource.h"

#include <algorithm>
#include "../utils/fileIO.h"
#include "../utils/utility.h"
#include "../graphics/geometry.h"
#include "../system/logging.h"



namespace robolab {
	using namespace utils;
	using namespace graphics;

	namespace manager {

		std::vector<std::shared_ptr<Mesh>> Resource::emptyPhysicalMesh;
		bool Resource::isInitialized = false;
		std::unordered_map<std::string, std::shared_ptr<Mesh>> Resource::visualMeshList;
		std::unordered_map<std::string, std::vector<std::shared_ptr<Mesh>>> Resource::physicalMeshList;
		std::unordered_map<std::string, Resource::FileExtention> Resource::filesExtentionList {
			{"OBJ", FILE_OBJ },
			{"obj", FILE_OBJ },
			{"STL", FILE_STL },
			{"stl", FILE_STL }
		};

		//#########################################################################

		bool Resource::initialize() {
			if (!isInitialized)
			{
				isInitialized = true;
			}
				
			return isInitialized;
		}


		void Resource::loadMesh(MeshUsageType type, const std::string& directory, const std::string& meshName, Vec3f& scaleFactor) {
			Path directoryPath(directory);
			/*if (!directoryPath.isDirectory()) {
				system::Logging::console(system::LOG_ERROR, "\"" + directoryPath.toString() + "\" is not a directory.", LOCATION);
				return;
			}*/

			std::shared_ptr<Mesh> mesh;
			switch (type)
			{
				case MeshUsageType::VISUALIZATION:
				{
					std::vector<Path> fileList;
					fileList = getListOfFiles(directoryPath, meshName);
					if (fileList.empty()) {
						system::Logging::console(system::LOG_ERROR, "No file found with name \"" + meshName + "\" in " + directoryPath.toString());
						return;
					}

					bool isRenderableMeshFound = false;
					for (auto& path : fileList)
					{
						if (path.getBaseName() == meshName && filesExtentionList.find(path.getExtension()) != filesExtentionList.end()) {
							auto mesh = loadMesh(path, scaleFactor);
							if (mesh) {
								visualMeshList[meshName] = loadMesh(path, scaleFactor);
							}
							else
								system::Logging::console(system::LOG_INFORMATION, "Failed to load mesh \"" + path.getFileName() + "\".");
							break;
						}
					}
					break;
				}
				case MeshUsageType::PHYSIC_SIMULATION:
				{
					std::vector<Path> fileList;
					fileList = getListOfFiles(directoryPath, meshName + "_Physx");
					if (fileList.empty()) {
						system::Logging::console(system::LOG_ERROR, "No file found with name \"" + meshName + "_Physx" + "\" in " + directoryPath.toString());
						return;
					}
					std::vector<std::shared_ptr<Mesh>> physicalMesh;
					for (auto path : fileList)
					{
						if (filesExtentionList.find(path.getExtension()) != filesExtentionList.end()) {
							auto mesh = loadMesh(path, scaleFactor);
							if (mesh) {
								physicalMesh.push_back(mesh);
							}
							else
								system::Logging::console(system::LOG_INFORMATION, "Failed to load mesh \"" + path.getFileName() + "\".");
						}
					}
					if (physicalMesh.empty())
						system::Logging::console(system::LOG_ERROR, "No mesh is loaded with base name \"" + meshName + "_Physx"
							+ "\" in \"" + directory + "\" directory.", __func__);
					else
						physicalMeshList[meshName] = physicalMesh;
					break;
				}
				default:
					break;
			}
		}

		std::shared_ptr<Mesh> Resource::loadMesh(const Path& path, Vec3f& scaleFactor) {
			std::shared_ptr<Mesh> meshBuffer = nullptr;
			switch (filesExtentionList[path.getExtension()])
			{
			case FILE_OBJ:
			{
				meshBuffer = fileIO::obj::load(path, scaleFactor);
				return meshBuffer;
			}
			break;
			default:
				system::Logging::console(system::LOG_ERROR, "The \"" + path.getExtension() + "\" extention is not supported.");
				return nullptr;
				break;
			}
		}



		const std::pair<bool, std::shared_ptr<Mesh>> Resource::getVisualMesh(const std::string& meshName) {
			if (visualMeshList.find(meshName) != visualMeshList.end())
				return std::make_pair(true, visualMeshList[meshName]);
			else
				return std::make_pair(false, nullptr);
		}

		const std::pair<bool, std::vector<std::shared_ptr<Mesh>>> Resource::getPhysicalMesh(const std::string& meshName) {
			if (physicalMeshList.find(meshName) != physicalMeshList.end())
				return std::make_pair(true, physicalMeshList[meshName]);
			else
				return std::make_pair(true, emptyPhysicalMesh);
		}

		std::shared_ptr<Mesh> Resource::createCube(const std::string& meshName, float lenght, float width, float height, Vec3f& pivot) {
			visualMeshList[meshName] = geometry::createCube(lenght, width, height, pivot);
			return visualMeshList[meshName];
		}

		void Resource::shutdown() {

		}


	}// ! namespace manager
}// ! namespace robolab