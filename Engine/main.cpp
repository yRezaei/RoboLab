#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include "src\engine.h"
#include "test/bp_main_simpleTest.h"
#include "test/bp_main_simpleRandom.h"
#include "test/bp_main_robocup.h"

int main(int argc, char **argv)
{
	using namespace std::literals;


	/*##################################################################
					Simple test
	###################################################################*/

	/*robolab::Engine::initialize(std::make_unique<BP_Main_SimpleTest>(), EngineMode::GUI);
	while (true) {
		if (robolab::Engine::update(1 / 60.0f) == robolab::EngineState::SHUTDOWN)
			break;
	}*/

	/*##################################################################
			Simple random drop
	###################################################################*/

	/*robolab::Engine::initialize(std::make_unique<BP_Main_SimpleRandom>(100), EngineMode::GUI);
	while (true) {
		if (robolab::Engine::update(1 / 60.0f) == robolab::EngineState::SHUTDOWN)
			break;
	}
	*/	
	/*##################################################################
							Robocup
	###################################################################*/

	robolab::Engine::initialize(std::make_unique<BP_Main_Robocup>(), EngineMode::GUI);
	while (true) {
		if (robolab::Engine::update(1 / 60.0f) == robolab::EngineState::SHUTDOWN)
			break;
	}

	
	//std::this_thread::sleep_for(0.5s);
	return 0;
}
