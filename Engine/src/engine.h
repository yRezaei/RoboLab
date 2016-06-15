#ifndef ENGINE_H
#define ENGINE_H

#include "utils/fileIO.h"
#include "utils/timer.h"
#include "utils/random.h"
#include "system/input.h"
#include "managers/resource.h"
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

	enum class EngineMode {
		GUI,
		CMD
	};

	enum class EngineState {
		NONE,
		IDEAL,
		SHUTDOWN
	};

	class Engine {
	private:
		class DefaultBlueprint : public IBlueprint {
		public:
			Entity Grid;
			DefaultBlueprint();
			~DefaultBlueprint();
		};
	public:
		using EngineFlagBitset = std::bitset<3>;
		enum EngineFlag {
			REAL_TIME_UPDATE,
			VISUALIZE_WORLD,
			SIMULATE_PHYSIC
		};
		
	private:
		static bool isInitialized;
		static float renderTimeCounter;
		static std::unique_ptr<IBlueprint> mainBlueprint;
		static EngineState activeState;
		static EngineState newState;
		static EngineFlagBitset engineFlags;
		static EngineMode mode;

		static void cleanUp();
	public:
		static void initialize(std::unique_ptr<IBlueprint> MainBlueprint, EngineMode Mode);
		static void setFlag(EngineFlag flag, bool value);
		static bool getFlag(EngineFlag flag);
		static EngineState update(float physicDeltaTime);
		static void shutdown();
	};
}


#endif
