#include "engine.h"

namespace robolab {

	Engine::Engine(const std::string& pathToSettingFile) {
		RenderMgr::initialize("Robo-Lab", Vec2i(800, 600), false);
		PhysicsMgr::initialize(UNIT_METER);
	}

	Engine::~Engine() {
		Logging::console(system::LOG_INFORMATION, "Cleaning up Renderable objects.");
		manager::RenderMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up NVIDIA Physx objects.");
		PhysicsMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up Loaded resources.");
		manager::ResourceMgr::shutdown();
	}
}