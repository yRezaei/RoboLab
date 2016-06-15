/*
 * engine.h
 * 
 * Copyright 2016 Yashar Abbasalizadeh Rezaei <yashar.a.rezaei@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


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
