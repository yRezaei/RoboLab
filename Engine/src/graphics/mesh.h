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
				std::array<unsigned int, 3> indices;
				Vec3f normal;
				Vec3f color;
				Triangle();
				Triangle(std::array<unsigned int, 3>& verticesIndex, Vec3f& norm, Vec3f& color)
					: indices(verticesIndex), normal(norm), color(color) {}
			};
		private:
			Vertices vertices;
			std::vector<Triangle> triangles;
			Bounds bounds;
		public:
			Mesh();
			~Mesh();
		public:
			void addVertex(Vec3f& vertex);
			void addTriangles(std::array<unsigned int, 3>& indices, Vec3f& color);
			bool isValid();
			const Bounds& getBounds();
		};
	}
}
#endif // !VERTEX_DATA_H

