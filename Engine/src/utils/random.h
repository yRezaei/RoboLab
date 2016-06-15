/*
* random.h
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
#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace robolab {
	namespace utils {

		inline float randF(float min, float max) {
			if(max > min)
				return min + ((((float)rand()) / (float)RAND_MAX) * (max - min));
			return 0.0f;
		}

		struct UniformRandomFloat
		{
		private:
			std::uniform_real_distribution<float>*  randomFloat;
			std::random_device randomDevice;
			std::mt19937 engine;
		public:
			UniformRandomFloat() {
				engine.seed(randomDevice());
				randomFloat = new std::uniform_real_distribution<float>(-1.0f, 1.0f);
			}

			UniformRandomFloat(float min, float max) {
				engine.seed(randomDevice());
				if (min < max)
					randomFloat = new std::uniform_real_distribution<float>(min, max);
				else
					randomFloat = new std::uniform_real_distribution<float>(0.0f, 1.0f);
			}

			~UniformRandomFloat() {
				if (randomFloat)
					delete(randomFloat);
			}

			float next() {
				return (*randomFloat)(engine);
			}

			void setRange(float min, float max) {
				if (min < max)
					randomFloat = new std::uniform_real_distribution<float>(min, max);
				else
					randomFloat = new std::uniform_real_distribution<float>(0, 1);
			}
		};

		struct UniformRandomInt
		{
		private:
			std::uniform_int_distribution<int>*  randomInt;
			std::random_device randomDevice;
			std::mt19937 engine;
		public:
			UniformRandomInt() {
				engine.seed(randomDevice());
				randomInt = new std::uniform_int_distribution<int>(-1, 1);
			}

			UniformRandomInt(int min, int max) {
				engine.seed(randomDevice());
				if (min < max)
					randomInt = new std::uniform_int_distribution<int>(min, max);
				else
					randomInt = new std::uniform_int_distribution<int>(-1, 1);
			}

			~UniformRandomInt() {
				if (randomInt)
					delete(randomInt);
			}

			int next() {
				return (*randomInt)(engine);
			}

			void setRange(int min, int max) {
				if (min < max)
					randomInt = new std::uniform_int_distribution<int>(min, max);
				else
					randomInt = new std::uniform_int_distribution<int>(-1, 1);
			}
		};

	}
}

#endif // !RANDOM_H

