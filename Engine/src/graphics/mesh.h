/*
* mesh.h
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
#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "../mathematic/math3D.h"
#include "bounds.h"

namespace robolab {
	using namespace math3D;

	namespace graphics {

		class Mesh {
		public:
			struct Triangle {
				Vec3ui indices;
				Vec3f normal;
				Vec3f color;
				Triangle();
				Triangle(Vec3ui& verticesIndex, Vec3f& norm, Vec3f& color)
					: indices(verticesIndex), normal(norm), color(color) {}
			};
		private:
			std::size_t id;
			Vertices rowVertices;
			std::vector<Triangle> triangles;
			Bounds bounds;
		public:
			Mesh();
			~Mesh();
		public:
			std::size_t getID();
			const Vertices& getRowVertices();
			void addVertex(Vec3f& vertex);
			void addTriangles(unsigned int id_1, unsigned int id_2, unsigned int id_3, Vec3f& color);
			Vertices getVertices();
			Normals getNormals();
			Colors getColors();
			Indices getIndices();
			bool isValid();
			const Bounds& getBounds();
		};
	}
}
#endif // !VERTEX_DATA_H

