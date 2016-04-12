#ifndef ENGINE_H
#define ENGINE_H

#include "utils/fileIO.h"
#include "utils/timer.h"
#include "utils/random.h"
#include "managers/renderMgr.h"
#include "managers/physicsMgr.h"
#include "managers/resourceMgr.h"
#include "system/logging.h"
#include "blueprint/IBlueprint.h"
#include "entity/rigidObject.h"

using namespace robolab;
using namespace graphics;
using namespace entity;
using namespace system;
using namespace manager;
using namespace blueprint;

namespace robolab {
	class Engine {
	private:
		bool initialize();
	public:
		Engine(const std::string& pathToSettingFile);
		~Engine();
		bool loadResource(const std::string& fileName);
	};
}


#endif
