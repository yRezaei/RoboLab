#ifndef BP_MAIN_SIMPLE_RANDOM_H
#define BP_MAIN_SIMPLE_RANDOM_H

#include "../src/engine.h"
#include "bp_simpleRandomInstance.h"

class BP_Main_SimpleRandom : public IBlueprint
{
public:
	Entity Grid;
	bool conitueSimulation, enablePhysics, enableDrawing;
	std::size_t nrOfInstance;
	unsigned int instanceGap;
	std::vector<std::shared_ptr<BP_SimpleRandomInstance>> insanceList;
public:
	BP_Main_SimpleRandom(std::size_t NrOfInstace) {
		enablePhysics = enableDrawing = conitueSimulation = false;
		nrOfInstance = NrOfInstace;
	}

	~BP_Main_SimpleRandom() {
	}

	void init() override {
		RenderMgr::initialize("Robo-Lab", Vec2i(800, 600), false);
		PhysicsMgr::initialize(UNIT_METER);

		ResourceMgr::loadMeshFile("../Resources/internal", "grid", ResourceMgr::MESH_RENDERING, Vec3f(0.1f));

		ResourceMgr::loadMeshFile("../Resources/obj_objects/", "bottle_water_glass2", ResourceMgr::MESH_RENDERING | ResourceMgr::MESH_PHYSIC_SIMULATION, Vec3f(0.01f));
		ResourceMgr::loadMeshFile("../Resources/obj_objects/", "table_curved", ResourceMgr::MESH_RENDERING | ResourceMgr::MESH_PHYSIC_SIMULATION, Vec3f(0.01f));

		if (ResourceMgr::existRenderMesh("grid")) {
			Grid.setName("Grid");
			Grid.addComponent<RenderableComponent>("grid");
		}
		else
			system::Logging::console(system::LOG_WARNING, "No mesh found loaded with name GRID.");

		while ((instanceGap * instanceGap) < nrOfInstance)
			instanceGap += 1;

		auto idx = 0.0f;
		auto idy = 0.0f;
		for (auto i = 1; i <= nrOfInstance; i++) {

			std::shared_ptr<BP_SimpleRandomInstance> bp = std::make_shared<BP_SimpleRandomInstance>(
				Vec3f(idx, idy, 0.0f), "bottle_water_glass2", "table_curved");
			bp->init();
			insanceList.push_back(bp);

			idx += 3;
			if (i % instanceGap == 0) {
				idx = 0;
				idy += 3;
			}
		}
		
	}


	void update(float deltaTime) override
	{
		utils::Timer::update();

		//##########################################
		if (Input::KeyPressed(KEY_S)) {
			Logging::console(system::LOG_INFORMATION, "KEY_S is pressed.");
			if (conitueSimulation)
				conitueSimulation = false;
			else
				conitueSimulation = true;
		}

		//##########################################
		if (Input::KeyPressed(KEY_P)) {
			if (enablePhysics)
				enablePhysics = false;
			else
				enablePhysics = true;
		}

		//##########################################
		if (Input::KeyPressed(KEY_D)) {
			if (enableDrawing)
				enableDrawing = false;
			else
				enableDrawing = true;
		}

		if (conitueSimulation) {
			for (auto instance : insanceList)
				instance->update(deltaTime);
		}

		//##########################################
		if(enablePhysics)
			manager::PhysicsMgr::update(1 / 60.f);

		manager::RenderMgr::update(enableDrawing);
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

#endif // !BP_MAIN_SIMPLE_RANDOM_H



