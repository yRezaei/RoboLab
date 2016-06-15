#ifndef TIMER_H
#define TIMER_H

#include <vector>
#include <chrono>

namespace robolab {
	namespace utils {

		using Clock = std::chrono::high_resolution_clock;

		class Timer
		{
		public:
			enum TimeUnit {
				NANOSECOND,
				MICROSECOND,
				MILISECOND,
				SECOND
			};
		private:
			static constexpr unsigned short maxDeltaCount = 3;
			static Clock::time_point previousTime;
			static Clock::time_point currentTime;
			static Clock::time_point startTime;
			static unsigned long long movingDeltaTimeSum;
			static unsigned int counter;
			static std::vector< unsigned long long> deltaTimeList;
			static unsigned long long deltaTime;
		public:
			static void update();
			static double getFPS();
			static double getDeltaTime(TimeUnit unit);
			static double getTotalTime();
		};

	}
}

#endif // !TIMER_H

