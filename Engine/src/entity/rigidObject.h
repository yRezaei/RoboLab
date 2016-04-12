#ifndef RIGID_OBJECT_H
#define RIGID_OBJECT_H

#include "entity.h"

namespace robolab {
	namespace entity {
		struct CollisionInfo
		{
			Entity* otherObject;
		};

		class RigidObject : public Entity
		{
		public:
			RigidObject(const std::string& Name, const Mat4& transform, const std::string& meshName, bool isDynamic);
			~RigidObject();

			bool onCollision(CollisionInfo& collisionInfo);

		};
	}
}

#endif //!RIGID_OBJECT_H