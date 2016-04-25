#include "mesh.h"

namespace robolab {

	namespace graphics {

		Mesh::Mesh() {

		}

		Mesh::~Mesh() {

		}

		void Mesh::addVertex(Vec3f& vertex) {
			vertices.push_back(vertex);
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

		void Mesh::addTriangles(std::array<unsigned int, 3>& indices, Vec3f& color) {
			Vec3f norm = normalize(
				cross(vertices[indices[1]] - vertices[indices[0]],
					vertices[indices[2]] - vertices[indices[0]]));
			triangles.push_back(Triangle(indices, norm, color));
		}

		bool Mesh::isValid() {
			bool result = false;
			if(vertices.size() >= 3 && triangles.size() >= 1 && vertices[0] != vertices[1] && 
				vertices[0] != vertices[2] && vertices[1] != vertices[2])
				result = true;
			return result;
		}

		/*Vertices Mesh::getVertices() {
			Vertices vertices(triangles.size() * 3);
			std::size_t index = 0;
			for (auto tri : triangles) {
				for (auto idx : tri.indices) {
					vertices[index++] = rowVertices[idx];
				}
			}
			return vertices;
		}

		Normals Mesh::getNomals() {
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
			std::size_t index = 0;
			for (auto i = 0; i < triangles.size() * 3; i++)
				indices[index] = index++;
			return indices;
		}*/

		const Bounds& Mesh::getBounds() {
			return bounds;
		}

	}
}