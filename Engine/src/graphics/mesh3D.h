#ifndef MESH_3D_H
#define MESH_3D_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "../mathematic/math3D.h"


namespace robolab {
	using namespace math3D;

	namespace graphics {

		using uint = unsigned int;

		struct Bounds 
		{
		private:
			Vec3f min, max;
		public:
			enum class Plane { XY, YZ, XZ };
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

			float radius() const {
				if (isValid) {
					auto radius = max.x;
					if (radius < max.y)
						radius = max.y;
					if (radius < max.z)
						radius = max.z;
					return radius;
				}
				else
					return 0;
			}

			float radius(Plane plane) const {
				if (isValid) {
					switch (plane)
					{
					case Bounds::Plane::XY:
					{
						auto radius = max.x;
						if (radius < max.y)
							radius = max.y;
						return radius;
					}
						break;
					case Bounds::Plane::YZ:
					{
						auto radius = max.y;
						if (radius < max.z)
							radius = max.z;
						return radius;
					}
						break;
					case Bounds::Plane::XZ:
					{
						auto radius = max.x;
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

			float radius() const {
				if (isValid) {
					auto radius = max.x;
					if (radius < max.y)
						radius = max.y;
					if (radius < max.z)
						radius = max.z;
					return radius;
				}
				else
					return 0;
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
				out << "Radius:   " << bounds.radius();
				return out;
			}
		};// end of struct Bounds

		struct MeshDataBuffers {
		private:
			std::size_t uniqueID; 
			std::string meshName;
		public:
			Indices rowIndices;
			Vertices rowVertices;
			Vertices vertices;
			Normals normals;
			Colors colors;
			Indices indices;
			Bounds bounds;
			MeshDataBuffers(std::size_t UniqueID, const std::string& MeshName) 
				: uniqueID(UniqueID), meshName(MeshName) {}
			bool operator == (const MeshDataBuffers& meshDataBuffers)
			{
				if (uniqueID == meshDataBuffers.uniqueID)
					return true;
				else
					return false;
			}
			const std::size_t& getID() {
				return uniqueID;
			}
			const std::string& getName() {
				return meshName;
			}
		};

		struct GLBufferIDs {
		private:
			std::size_t uniqueID;
			std::string meshName;
		public:
			uint VAO;
			std::unordered_map<std::string, unsigned int> attributesID;
			uint indexID;
			std::size_t indexSize;
			GLBufferIDs(std::size_t UniqueID, std::string MeshName, uint vao, uint index, std::size_t IndexSize, std::unordered_map<std::string, unsigned int>& AttributesID)
				: uniqueID(UniqueID), meshName(MeshName), VAO(vao), indexID(index), indexSize(IndexSize), attributesID(AttributesID) {}
			bool operator == (const GLBufferIDs& glBufferIDs)
			{
				if (uniqueID == glBufferIDs.uniqueID)
					return true;
				else
					return false;
			}

			const std::size_t& getID() {
				return uniqueID;
			}
			const std::string& getName() {
				return meshName;
			}

		};

		struct GLShaderIDs {
			uint shaderID;
			std::unordered_map<std::string, unsigned int> locationIDs;
			GLShaderIDs(uint ShaderID, std::unordered_map<std::string, unsigned int>& LocationIDs) 
				: shaderID(ShaderID), locationIDs(LocationIDs) {}
		};

		struct RenderableObject {
			std::size_t index;
			std::shared_ptr<GLBufferIDs> gLIDs;
			RenderableObject(std::size_t Index, std::shared_ptr<GLBufferIDs> GLIDs)
				: index(Index), gLIDs(GLIDs) {}
		};

		struct PhysicalProperty
		{
			float mass;
			float density;
			float friction;
			float dynamicFriction;
			float restitution;
			float angularDamping;
			float linearDamping;

			PhysicalProperty() {
				this->mass = 1.3f;
				this->density = 0.7f;
				this->friction = 0.7f;
				this->dynamicFriction = 0.7f;
				this->restitution = 0.4f;
				this->angularDamping = 0.3f;
				this->linearDamping = 0.3f;
			}

			PhysicalProperty(float mass, float density, float friction, float dynamicFriction,
				float restitution, float angularDamping, float linearDamping) {
				this->mass = mass;
				this->density = density;
				this->friction = friction;
				this->dynamicFriction = dynamicFriction;
				this->restitution = restitution;
				this->angularDamping = angularDamping;
				this->linearDamping = linearDamping;
			}
		};
	}
}


#endif // !MESH_DATA_H

