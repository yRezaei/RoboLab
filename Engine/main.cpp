#include <iostream>
#include <thread>
#include <chrono>

#include "test/bp_main_simpleTest.h"
#include "test/bp_main_simpleRandom.h"
#include "test/bp_main_validSurfacePoint.h"
#include "test/bp_symbolicNumericConversion.h"

int main(int argc, char **argv)
{
	using namespace std::literals;


	/*##################################################################
					Simple test
	############################################*/

	/*BP_Main_SimpleTest simpleTest;
	simpleTest.init();
	while (RenderMgr::isOK())
	{
		simpleTest.update(1 / 60.f);
	}
	simpleTest.destroy();*/

	/*##################################################################
			Simple random drop
	############################################*/

	/*BP_Main_SimpleRandom simpleRandom(100);
	simpleRandom.init();
	while (RenderMgr::isOK())
	{
		simpleRandom.update(1 / 120.f);
	}
	simpleRandom.destroy();*/

	/*#################################################################
				Valid surface point test
	############################################*/

	/*BP_Main_validSurfacePoint validSurfacePoint(1000);
	validSurfacePoint.init();
	while (RenderMgr::isOK())
	{
		validSurfacePoint.update(1 / 200.f);
	}
	validSurfacePoint.destroy();*/

	/*#################################################################
				Symbolic Numeric conversion
	############################################*/

	BP_SymbolicNumericConversion symbolicNumeric(1000);
	symbolicNumeric.init();
	while (RenderMgr::isOK())
	{
		symbolicNumeric.update(1 / 200.f);
	}
	symbolicNumeric.destroy();

	
	std::this_thread::sleep_for(1s);
	return 0;
}
