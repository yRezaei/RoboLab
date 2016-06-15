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

