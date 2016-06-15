/*
* shape.h
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
#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <vector>
#include <string>
#include "mesh.h"
#include "../mathematic/math3D.h"

namespace robolab {
	using namespace math3D;

	namespace graphics {

		class Shape {
		private:
			std::string name;
			std::size_t id;
			std::shared_ptr<Mesh> visual;
			std::vector<std::shared_ptr<Mesh>> physical;
		public:
			Shape(const std::string& Name, std::size_t ID) {
				name = Name;
				id = ID;
			}

			Shape(const std::string& Name, std::size_t ID, std::shared_ptr<Mesh>& VisualMesh) {
				name = Name;
				id = ID;
				visual = VisualMesh;
			}

			Shape(const std::string& Name, std::size_t ID, std::vector<std::shared_ptr<Mesh>>& PhysicalMesh) {
				name = Name;
				id = ID;
				physical = PhysicalMesh;
			}

			Shape(const std::string& Name, std::size_t ID, std::shared_ptr<Mesh>& VisualMesh, std::vector<std::shared_ptr<Mesh>>& PhysicalMesh) {
				name = Name;
				id = ID;
				visual = VisualMesh;
				physical = PhysicalMesh;
			}

			~Shape() {}
		public:
			void setVisualMesh(std::shared_ptr<Mesh>& VisualMesh) {
				visual = VisualMesh;
			}

			void setPhysicalMesh(std::vector<std::shared_ptr<Mesh>>& PhysicalMesh) {
				physical = PhysicalMesh;
			}

			const std::string& getName() {
				return name;
			}

			std::size_t getID() {
				return id;
			}

			bool hasVisual() {
				if (visual)
					return true;
				else
					return false;
			}

			bool hasPhysical() {
				bool result;
				if (physical.size() > 0) {
					for (auto phy : physical) {
						if (phy) {
							result = true;
						}
						else {
							result = false;
							break;
						}
					}
				}
				else
					result = false;
				return result;
			}

			const std::shared_ptr<Mesh> getVisual() {
				return visual;
			}

			const std::vector<std::shared_ptr<Mesh>>& getPhysical() {
				return physical;
			}
		};
	}
}

#endif // !SHAPE_H#pragma once
