/*
* bounds.h
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
*/#ifndef BOUNDS_H
#define BOUNDS_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "../mathematic/math3D.h"

namespace robolab {
	using namespace math3D;

	namespace graphics {
		
		struct Bounds
		{
		private:
			Vec3f min, max;
		public:
			enum class Axis { XY, YZ, XZ, XYZ };
		public:
			bool isValid;
			Bounds() {
				isValid = false;
			}

			Bounds(Vec3f min, Vec3f& max) {
				this->max = max;
				this->min = min;
				if (max != min)
					isValid = true;
				else
					isValid = false;
			}

			Bounds(const Bounds& bounds) {
				this->setBounds(bounds.getMin(), bounds.getMax());
			}

			~Bounds() {}

			void setBounds(const Vec3f& min, const Vec3f& max) {
				this->max = max;
				this->min = min;
				if (max != min)
					isValid = true;
				else
					isValid = false;
			}

			const Vec3f& getMin() const {
				return min;
			}

			const Vec3f& getMax() const {
				return max;
			}

			Bounds& operator = (const Bounds& bounds) {
				this->setBounds(bounds.getMin(), bounds.getMax());
				return *this;
			}

			Vec3f size() const {
				if (isValid)
					return (max - min);
				else
					return Vec3f(0.0f);
			}

			Vec3f extents() const {
				if (isValid)
					return size() / 2.0f;
				else
					return Vec3f(0.0f);
			}

			Vec3f center() const {
				if (isValid)
					return (max + min) / 2.0f;
				else
					return Vec3f(0.0f);
			}

			float radius(Axis axis) const {
				if (isValid) {
					switch (axis)
					{
					case Bounds::Axis::XY:
					{
						auto radius = max.x;
						if (radius < max.y)
							radius = max.y;
						return radius;
					}
					break;
					case Bounds::Axis::YZ:
					{
						auto radius = max.y;
						if (radius < max.z)
							radius = max.z;
						return radius;
					}
					break;
					case Bounds::Axis::XZ:
					{
						auto radius = max.x;
						if (radius < max.z)
							radius = max.z;
						return radius;
					}
					break;
					case Bounds::Axis::XYZ:
					{
						auto radius = max.x;
						if (radius < max.y)
							radius = max.y;
						if (radius < max.z)
							radius = max.z;
						return radius;
					}
					break;
					default:
						return 0;
						break;
					}
				}
				else
					return 0;
			}

			std::vector<Vec3f> corners() {
				if (isValid) {
					std::vector<Vec3f> vertices({
						Vec3f(max.x, max.y, max.z),
						Vec3f(min.x, max.y, max.z),
						Vec3f(max.x, max.y, max.z),
						Vec3f(min.x, min.y, max.z),
						Vec3f(max.x, max.y, min.z),
						Vec3f(min.x, max.y, min.z),
						Vec3f(max.x, max.y, min.z),
						Vec3f(min.x, min.y, min.z)
					});
					return vertices;
				}
				else
					return std::vector<Vec3f>();
			}

			Bounds getAABB(Quat& quat) {
				std::vector<Vec3f> vertices = corners();

				Mat3 rot = glm::mat3_cast(quat);

				for (auto& vert : vertices) {
					vert = rot * vert;
				}

				Vec3f tempMax = vertices[0];
				Vec3f tempMin = vertices[0];

				for (auto vertex : vertices) {
					if (tempMax.x < vertex.x)
						tempMax.x = vertex.x;
					if (tempMin.x > vertex.x)
						tempMin.x = vertex.x;

					if (tempMax.y < vertex.y)
						tempMax.y = vertex.y;
					if (tempMin.y > vertex.y)
						tempMin.y = vertex.y;

					if (tempMax.z < vertex.z)
						tempMax.z = vertex.z;
					if (tempMin.z > vertex.z)
						tempMin.z = vertex.z;
				}

				return Bounds(tempMin, tempMax);
			}

			friend std::ostream& operator << (std::ostream& out, const Bounds& bounds) {
				Vec3f max = bounds.getMax();
				Vec3f min = bounds.getMin();
				Vec3f s = bounds.size();
				Vec3f e = bounds.extents();
				out << "Max:	 [" << max.x << " , " << max.y << " , " << max.z << "]" << std::endl;
				out << "Min:	 [" << min.x << " , " << min.y << " , " << min.z << "]" << std::endl;
				out << "Size:	 [" << s.x << " , " << s.y << " , " << s.z << "]" << std::endl;
				out << "Extents: [" << e.x << " , " << e.y << " , " << e.z << "]" << std::endl;
				out << "Radius:   " << bounds.radius(Bounds::Axis::XYZ);
				return out;
			}
		};// end of struct Bounds
	}
}
#endif // !BOUNDS_H
