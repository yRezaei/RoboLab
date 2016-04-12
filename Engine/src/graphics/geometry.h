#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../mathematic/math3D.h"
#include "../graphics/mesh3D.h"
#include <memory>

namespace robolab {
	using namespace math3D;

	namespace graphics {
		namespace geometry {

			void createCube(std::shared_ptr<MeshDataBuffers> meshBuffer, float lenght, float width, float height, Vec3f& pivot);

		}
	}
}
#endif // !GEOMETRY_H

