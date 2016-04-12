#include "engine.h"

namespace robolab {

	Engine::Engine(const std::string& pathToSettingFile) {

	}

	Engine::~Engine() {

	}

	bool Engine::loadResource(const std::string& fileName) {



		return false;
	}

	void ResourceMgr::loadMeshFile(const std::string& dir, const std::string& meshName, ResourceMgr::BitwiseMeshUsageType usageType, Vec3f& scaleFactor) {
		Path directory;
		if (dir.back() != '/' || dir.back() != '\\')
			directory = Path(dir + "/");
		else
			directory = Path(dir);
		std::vector<Path> fileList;
		if (directory.isDirectory())
			fileList = fileIO::getAllFileInDirectory(directory, meshName);
		else
		{
			system::Logging::console(system::LOG_WARNING, "The given directory contains file name \"" + directory.getFileName() + "\".", __func__);
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
				if (!isRenderableMeshFound)
					system::Logging::console(system::LOG_ERROR, "No mesh with name \"" + meshName
						+ "\" is found in \"" + directory.toString() + "\" directory.", __func__);
			}
			if (usageType & MESH_PHYSIC_SIMULATION) {
				bool isPhysicMeshFound = false;
				std::vector<std::shared_ptr<MeshDataBuffers>> physicMeshs;
				for (auto path : fileList)
				{
					if (path.getBaseName().find(meshName + "_Physx") != std::string::npos  && filesExtentionList.find(path.getExtension()) != filesExtentionList.end()) {
						physicMeshs.push_back(loadMesh(path, scaleFactor));
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
}