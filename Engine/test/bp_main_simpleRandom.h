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

		Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, "../Resources/internal", "grid", Vec3f(0.1f));

		Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, "../Resources/obj_objects/", "bottle_water_glass2", Vec3f(0.01f));
		Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, "../Resources/obj_objects/", "table_curved", Vec3f(0.01f));
		Resource::loadMesh(Resource::MeshUsageType::PHYSIC_SIMULATION, "../Resources/obj_objects/", "bottle_water_glass2", Vec3f(0.01f));
		Resource::loadMesh(Resource::MeshUsageType::PHYSIC_SIMULATION, "../Resources/obj_objects/", "table_curved", Vec3f(0.01f));


		Grid.setName("Grid");
		Grid.addComponent<RenderableComponent>("grid");


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
		if (Input::KeyPressed(KEY_ESCAPE))
			Engine::shutdown();

		//##########################################
		if (Input::KeyPressed(KEY_S)) {
			if (conitueSimulation)
				conitueSimulation = false;
			else
				conitueSimulation = true;
		}

		//##########################################
		if (Input::KeyPressed(KEY_P)) {
			if (Engine::getFlag(Engine::SIMULATE_PHYSIC))
				Engine::setFlag(Engine::SIMULATE_PHYSIC, false);
			else
				Engine::setFlag(Engine::SIMULATE_PHYSIC, true);
		}

		//##########################################
		if (Input::KeyPressed(KEY_D)) {
			if (Engine::getFlag(Engine::VISUALIZE_WORLD))
				Engine::setFlag(Engine::VISUALIZE_WORLD, false);
			else
				Engine::setFlag(Engine::VISUALIZE_WORLD, true);
		}

		if(conitueSimulation)
			for (auto& instance : insanceList)
				instance->update(deltaTime);
		

	}

	void destroy() override {
		
	}
};

#endif // !BP_MAIN_SIMPLE_RANDOM_H



