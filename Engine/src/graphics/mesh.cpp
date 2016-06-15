#include "mesh.h"

namespace robolab {

	namespace graphics {

		Mesh::Mesh() {
			static std::size_t uniqueMeshID{ 0ull };
			id = uniqueMeshID++;
		}

		Mesh::~Mesh() {

		}

		std::size_t Mesh::getID() {
			return id;
		}

		const Vertices& Mesh::getRowVertices() {
			return rowVertices;
		}

		void Mesh::addVertex(Vec3f& vertex) {
			rowVertices.push_back(vertex);
			Vec3f max = bounds.getMax();
			Vec3f min = bounds.getMin();
			if (max.x < vertex.x)
				max.x = vertex.x;
			if (min.x > vertex.x)
				min.x = vertex.x;

			if (max.y < vertex.y)
				max.y = vertex.y;
			if (min.y > vertex.y)
				min.y = vertex.y;

			if (max.z < vertex.z)
				max.z = vertex.z;
			if (min.z > vertex.z)
				min.z = vertex.z;
			bounds = Bounds(min, max);
		}

		void Mesh::addTriangles(unsigned int id_1, unsigned int id_2, unsigned int id_3, Vec3f& color) {
			Vec3f norm = normalize( cross(rowVertices[id_2] - rowVertices[id_1], rowVertices[id_3] - rowVertices[id_1]));
			triangles.push_back(Triangle(Vec3ui(id_1, id_2, id_3), norm, color));
		}

		bool Mesh::isValid() {
			bool result = false;
			if(rowVertices.size() >= 3 && triangles.size() >= 1 && rowVertices[0] != rowVertices[1] &&
				rowVertices[0] != rowVertices[2] && rowVertices[1] != rowVertices[2])
				result = true;
			return result;
		}

		Vertices Mesh::getVertices() {
			Vertices vertices(triangles.size() * 3);
			std::size_t index = 0;
			for (auto tri : triangles) {
				vertices[index++] = rowVertices[tri.indices[0]];
				vertices[index++] = rowVertices[tri.indices[1]];
				vertices[index++] = rowVertices[tri.indices[2]];
			}
			return vertices;
		}

		Normals Mesh::getNormals() {
			Normals normals(triangles.size() * 3);
			std::size_t index = 0;
			for (auto tri : triangles) {
				normals[index++] = tri.normal;
				normals[index++] = tri.normal;
				normals[index++] = tri.normal;
			}
			return normals;
		}

		Colors Mesh::getColors() {
			Colors colors(triangles.size() * 3);
			std::size_t index = 0;
			for (auto tri : triangles) {
				colors[index++] = tri.color;
				colors[index++] = tri.color;
				colors[index++] = tri.color;
			}
			return colors;
		}

		Indices Mesh::getIndices() {
			Indices indices(triangles.size() * 3);
			unsigned int index = 0;
			for (auto i = 0; i < triangles.size() * 3; i++)
				indices[index] = index++;
			return indices;
		}

		const Bounds& Mesh::getBounds() {
			return bounds;
		}

	}
}