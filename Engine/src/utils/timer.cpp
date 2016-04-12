#include "timer.h"


namespace robolab {
	namespace utils {

		Clock::time_point Timer::previousTime = Clock::now();
		Clock::time_point Timer::currentTime = Clock::now();
		Clock::time_point Timer::startTime = Clock::now();
		unsigned long long Timer::movingDeltaTimeSum;
		unsigned int Timer::counter = 3;
		std::vector< unsigned long long> Timer::deltaTimeList = { 0, 0, 0};
		unsigned long long Timer::deltaTime;

		void Timer::update() {
			currentTime = Clock::now();
			deltaTime = Clock::duration(currentTime - previousTime).count();
			previousTime = currentTime;
			movingDeltaTimeSum = maxDeltaCount;
			deltaTimeList[counter++ % 3] = deltaTime;
			for (auto dt : deltaTimeList)
				movingDeltaTimeSum += dt;
		}

		double Timer::getFPS() {
			return (maxDeltaCount * 1000000000.0) / movingDeltaTimeSum;
		}

		double Timer::getDeltaTime() {
			return deltaTime / 1000000000.0;
		}

		double Timer::getTotalTime() {
			return Clock::duration(currentTime - startTime).count() / 1000000000.0;
		}
	}
}