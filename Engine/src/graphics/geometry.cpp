#include "geometry.h"
#include "../utils/random.h"
#include "../mathematic/math3D.h"

namespace robolab {
	using namespace math3D;

	namespace graphics {
		namespace geometry {

			std::shared_ptr<Mesh> createCube(float lenght, float width, float height, Vec3f& pivot) {
				Mesh mesh;
				Mat4 transform = makeMat4(pivot) * glm::scale(glm::mat4(1.0f), Vec3f(lenght, width, height));
				
				mesh.addVertex(Vec3f(transform * Vec4f(-0.5f, -0.5f, 0.5f, 1.0f)));
				mesh.addVertex(Vec3f(transform * Vec4f(0.5f, -0.5f, 0.5f, 1.0f)));
				mesh.addVertex(Vec3f(transform * Vec4f(-0.5f, 0.5f, 0.5f, 1.0f)));
				mesh.addVertex(Vec3f(transform * Vec4f(0.5f, 0.5f, 0.5f, 1.0f)));
				mesh.addVertex(Vec3f(transform * Vec4f(-0.5f, 0.5f, -0.5f, 1.0f)));
				mesh.addVertex(Vec3f(transform * Vec4f(0.5f, 0.5f, -0.5f, 1.0f)));
				mesh.addVertex(Vec3f(transform * Vec4f(-0.5f, -0.5f, -0.5f, 1.0f)));
				mesh.addVertex(Vec3f(transform * Vec4f(0.5f, -0.5f, -0.5f, 1.0f)));

				const Indices indices({
					0,1,2, 2,1,3, 2,3,4, 4,3,5,
					4,5,6, 6,5,7, 6,7,0, 0,7,1,
					1,7,3, 3,7,5, 6,0,4, 4,0,2});
				
				for (auto ii = 0; ii < indices.size(); ii += 3) {
					mesh.addTriangles(indices[ii], indices[ii + 1], indices[ii + 2] , Vec3f(0.6f));
				}

				return std::make_shared<Mesh>(mesh);
			}


		}
	}
}