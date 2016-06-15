#include "engine.h"
#include "managers/renderMgr.h"
#include "managers/physicsMgr.h"

namespace robolab {

	bool Engine::isInitialized = false;
	float Engine::renderTimeCounter = 0.0f;
	std::unique_ptr<IBlueprint> Engine::mainBlueprint = nullptr;
	EngineState Engine::activeState  = EngineState::NONE;
	EngineState Engine::newState = EngineState::NONE;
	Engine::EngineFlagBitset Engine::engineFlags = std::bitset<3>(std::string("111"));
	EngineMode Engine::mode = EngineMode::GUI;

	

	void Engine::initialize(std::unique_ptr<IBlueprint> MainBlueprint, EngineMode Mode) {
		if (newState == EngineState::NONE) {
			if (MainBlueprint) {
				mode = Mode;
				isInitialized = true;
				newState = EngineState::IDEAL;
				if (mode == EngineMode::GUI) {
					RenderMgr::initialize("Robo-Lab", Vec2i(800, 600), false);

					PhysicsMgr::initialize(UNIT_METER);

					mainBlueprint = std::move(MainBlueprint);
					mainBlueprint->init();
				}
				else
					Logging::console(system::LOG_ERROR, "The main blueprint is NULL.");
			}
		}
		else
			Logging::console(system::LOG_ERROR, "Engine already initialized. Reinitialization requiers shut it down first.");
	}

	void Engine::setFlag(EngineFlag flag, bool value) {
		engineFlags[flag] = value;
	}

	bool Engine::getFlag(EngineFlag flag) {
		return engineFlags[flag];
	}

	EngineState Engine::update(float physicDeltaTime) 
	{
		activeState = newState;

		utils::Timer::update();

		if (activeState == robolab::EngineState::IDEAL)
		{
			mainBlueprint->update(physicDeltaTime);

			if (engineFlags[REAL_TIME_UPDATE]) {
				if (renderTimeCounter < physicDeltaTime) {
					renderTimeCounter += utils::Timer::getDeltaTime(utils::Timer::SECOND);
				}
				else {
					renderTimeCounter = 0.0f;
					if (engineFlags[SIMULATE_PHYSIC])
						manager::PhysicsMgr::update(physicDeltaTime);
				}
			}
			else {
				if (engineFlags[SIMULATE_PHYSIC])
					manager::PhysicsMgr::update(physicDeltaTime);
			}

			/* todo

			Implement the gui / cmd mode seperation
			*/
			if (manager::RenderMgr::isOK())
				manager::RenderMgr::update(true);
		}
		else
			if (activeState == robolab::EngineState::SHUTDOWN) {
				cleanUp();
			}

		return activeState;
	}


	void Engine::shutdown() {
		newState = EngineState::SHUTDOWN;
	}


	void Engine::cleanUp() {
		newState = EngineState::NONE;

		mainBlueprint->destroy();

		Logging::console(system::LOG_INFORMATION, "Cleaning up Renderable objects.");
		manager::RenderMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up NVIDIA Physx objects.");
		PhysicsMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up Loaded resources.");
		manager::Resource::shutdown();
	}

}