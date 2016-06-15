#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../mathematic/math3D.h"
#include "../graphics/mesh3D.h"
#include "../graphics/mesh.h"
#include <memory>

namespace robolab {
	using namespace math3D;

	namespace graphics {
		namespace geometry {

			std::shared_ptr<Mesh> createCube( float lenght, float width, float height, Vec3f& pivot);

		}
	}
}
#endif // !GEOMETRY_H

