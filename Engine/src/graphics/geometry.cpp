#include "geometry.h"
#include "../utils/random.h"
#include "../mathematic/math3D.h"

namespace robolab {
	using namespace math3D;

	namespace graphics {
		namespace geometry {

			void createCube(std::shared_ptr<MeshDataBuffers> meshBuffer, float lenght, float width, float height, Vec3f& pivot) {
				const unsigned short vertexSize = 36;
				meshBuffer->vertices = Vertices({
					Vec3f(-0.5f, -0.5f, 0.5f), Vec3f(0.5f, -0.5f, 0.5f), Vec3f(-0.5f, 0.5f, 0.5f),
					Vec3f(-0.5f, 0.5f, 0.5f), Vec3f(0.5f, -0.5f, 0.5f), Vec3f(0.5f, 0.5f, 0.5f),
					Vec3f(-0.5f, 0.5f, 0.5f), Vec3f(0.5f, 0.5f, 0.5f), Vec3f(-0.5f, 0.5f, -0.5f),
					Vec3f(-0.5f, 0.5f, -0.5f), Vec3f(0.5f, 0.5f, 0.5f), Vec3f(0.5f, 0.5f, -0.5f),
					Vec3f(-0.5f, 0.5f, -0.5f), Vec3f(0.5f, 0.5f, -0.5f), Vec3f(-0.5f, -0.5f, -0.5f),
					Vec3f(-0.5f, -0.5f, -0.5f), Vec3f(0.5f, 0.5f, -0.5f), Vec3f(0.5f, -0.5f, -0.5f),
					Vec3f(-0.5f, -0.5f, -0.5f), Vec3f(0.5f, -0.5f, -0.5f), Vec3f(-0.5f, -0.5f, 0.5f),
					Vec3f(-0.5f, -0.5f, 0.5f), Vec3f(0.5f, -0.5f, -0.5f), Vec3f(0.5f, -0.5f, 0.5f),
					Vec3f(0.5f, -0.5f, 0.5f), Vec3f(0.5f, -0.5f, -0.5f), Vec3f(0.5f, 0.5f, 0.5f),
					Vec3f(0.5f, 0.5f, 0.5f), Vec3f(0.5f, -0.5f, -0.5f), Vec3f(0.5f, 0.5f, -0.5f),
					Vec3f(-0.5f, -0.5f, -0.5f), Vec3f(-0.5f, -0.5f, 0.5f), Vec3f(-0.5f, 0.5f, -0.5f),
					Vec3f(-0.5f, 0.5f, -0.5f), Vec3f(-0.5f, -0.5f, 0.5f), Vec3f(-0.5f, 0.5f, 0.5f)
				});
				meshBuffer->colors.resize(vertexSize, Vec3f(utils::randF(0,1), utils::randF(0, 1), utils::randF(0, 1)));
				meshBuffer->normals.resize(vertexSize);
				meshBuffer->indices.resize(vertexSize);
				Vec3f normTemp(0.0f);
				Mat4 transform = makeMat4(pivot) * glm::scale(glm::mat4(1.0f), Vec3f(lenght, width, height));
				for (auto ii = 0; ii < vertexSize; ii += 3) {
					meshBuffer->vertices[ii] = Vec3f(transform * Vec4f(meshBuffer->vertices[ii], 1.0f));
					meshBuffer->vertices[ii+1] = Vec3f(transform * Vec4f(meshBuffer->vertices[ii+1], 1.0f));
					meshBuffer->vertices[ii+2] = Vec3f(transform * Vec4f(meshBuffer->vertices[ii+2], 1.0f));
					meshBuffer->indices[ii] = ii;
					meshBuffer->indices[ii+1] = ii+1;
					meshBuffer->indices[ii+2] = ii+2;
					normTemp = normalize(cross(meshBuffer->vertices[ii + 1] - meshBuffer->vertices[ii], meshBuffer->vertices[ii + 2] - meshBuffer->vertices[ii]));
					meshBuffer->normals[ii] = normTemp;
					meshBuffer->normals[ii+1] = normTemp;
					meshBuffer->normals[ii+2] = normTemp;
				}
			}


		}
	}
}