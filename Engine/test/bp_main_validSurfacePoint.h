#ifndef BP_MAIN_VALID_SURFACE_POINT_H
#define BP_MAIN_VALID_SURFACE_POINT_H

#include "../src/engine.h"
#include "bp_validSurfacePointInstance.h"

#include <fstream>

class BP_Main_validSurfacePoint : public IBlueprint
{
private:
	Entity Grid;
	std::vector<Vec3f> allUniformPoints;
	std::size_t step;
	std::vector<Vec3f> validPoints;
	bool step_validPoints;
	unsigned int unfinishedTestCount;
	bool isDataReady;
	std::ofstream file;
	//#################
	std::size_t nrOfInstance;
	unsigned int instanceGap;
	std::vector<std::shared_ptr<BP_validSurfacePointInstance>> insanceList;
	std::string activeSurface, dropObject;
public:
	BP_Main_validSurfacePoint(std::size_t NrOfInstace) {
		step = 0;
		step_validPoints = true;
		unfinishedTestCount = 0;
		isDataReady = false;
		nrOfInstance = NrOfInstace;
		instanceGap = 0;
	}

	~BP_Main_validSurfacePoint() {
	}

	void init() override {
		ResourceMgr::BitwiseMeshUsageType render = ResourceMgr::MESH_RENDERING;
		ResourceMgr::BitwiseMeshUsageType renderANDphysic = ResourceMgr::MESH_RENDERING | ResourceMgr::MESH_PHYSIC_SIMULATION;

		RenderMgr::initialize("Robo-Lab", Vec2i(800, 600), false);
		PhysicsMgr::initialize(UNIT_METER);

		ResourceMgr::loadMeshFile("../Resources/internal", "grid", render, Vec3f(0.1f));

		ResourceMgr::loadMeshFile("../Resources/obj_objects/", "test_cube", renderANDphysic, Vec3f(0.01f));
		ResourceMgr::loadMeshFile("../Resources/obj_objects/", "table_curved", renderANDphysic, Vec3f(0.01f));
		ResourceMgr::loadMeshFile("../Resources/obj_objects/", "table_round", renderANDphysic, Vec3f(0.01f));

		dropObject = "test_cube";
		activeSurface = "table_round";

		if (ResourceMgr::existRenderMesh("grid")) {
			Grid.setName("Grid");
			Grid.addComponent<RenderableComponent>("grid");
		}
		else
			system::Logging::console(system::LOG_WARNING, "No mesh found loaded with name GRID.");


		float dropOffset = 0.1f;
		float validPointOffset = 0.02f;
		Bounds bounds = ResourceMgr::getRenderMesh(activeSurface)->bounds;
		std::cout << "Bounds:\n" << bounds << std::endl;
		
		for (auto x = bounds.getMin().x; x <= bounds.getMax().x; x += validPointOffset) {
			for (auto y = bounds.getMin().y; y <= bounds.getMax().y; y += validPointOffset) {
				allUniformPoints.push_back(Vec3f(x, y, bounds.getMax().z + dropOffset));
			}
		}
		
		if (allUniformPoints.size() < nrOfInstance)
			nrOfInstance = (int)allUniformPoints.size();

		while ((instanceGap * instanceGap) < nrOfInstance)
			instanceGap += 1;

		auto idx = 0;
		auto idy = 0;
		auto instanceIndex = 0;
		for (auto i = 1; i <= nrOfInstance; i++) {
			std::shared_ptr<BP_validSurfacePointInstance> bp = std::make_shared<BP_validSurfacePointInstance>(
				Vec3f(idx, idy, 0.0f), dropObject, activeSurface);
			bp->init();
			insanceList.push_back(bp);
			idx += 3;
			if (i % instanceGap == 0) {
				idx = 0;
				idy += 3;
			}
		}

		Logging::console(LOG_NOTICE, "Number Of parallel test: " + std::to_string(nrOfInstance));
		Logging::console(LOG_NOTICE, "Total uniform points : " + std::to_string(allUniformPoints.size()));
	}
	

	void update(float deltaTime) override 
	{
		utils::Timer::update();
		//##########################################

		if (step_validPoints)
		{
			unfinishedTestCount = 0;
			for (auto instance : insanceList)
			{
				instance->update(deltaTime);

				if (!instance->hasTask && instance->istestDone) {
					if (instance->isPointValid)
						validPoints.push_back(instance->getTestPoint());
					instance->istestDone = false;
				}

				if (!allUniformPoints.empty() && !instance->hasTask) {
					instance->setTestPoint(allUniformPoints.back());
					allUniformPoints.pop_back();
				}

				if (instance->hasTask) {
					unfinishedTestCount++;
				}
			}
		}

		if (allUniformPoints.empty() && unfinishedTestCount == 0 && step_validPoints) {
			Logging::console(system::LOG_NOTICE, "Valid Points count : " + std::to_string(validPoints.size()));
			step_validPoints = false;
			isDataReady = true;
		}
		
		if(isDataReady) {
			file.open(activeSurface + ".txt");
			for (auto vert : validPoints)
				file << vert.x << "," << vert.y << "\n";
			file.close();
			isDataReady = false;
			Logging::console(system::LOG_NOTICE, "The results are written to file.");
		}
		
		//##########################################
		manager::PhysicsMgr::update(1 / 60.f);
		manager::RenderMgr::update(true);
	}

	void destroy() override {
		Logging::console(system::LOG_INFORMATION, "Cleaning up Renderable objects.");
		manager::RenderMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up NVIDIA Physx objects.");
		PhysicsMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up Loaded resources.");
		manager::ResourceMgr::shutdown();

		Logging::console(system::LOG_NOTICE, "Bye bye.");
	}
};

#endif // !SURFACE_POINT_VALIDITY_TEST_H

