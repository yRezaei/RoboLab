/*
* timer.h
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

