#include "rigidObject.h"

namespace robolab {
	namespace entity {

		RigidObject::RigidObject(const std::string& Name, const Mat4& transform, const std::string& meshName, bool isDynamic) 
		{
			this->setName(Name);
			this->setTransform(transform);
			this->addComponent<RenderableComponent>(meshName);
			this->addComponent<PhysicComponent>(meshName, PhysicalProperty(), isDynamic);
		}

		RigidObject::~RigidObject() {

		}

		bool RigidObject::onCollision(CollisionInfo& collisionInfo) {
			if (getComponent<PhysicComponent>()->hasCollision()) {
				collisionInfo.otherObject = getComponent<PhysicComponent>()->getCollidedObject();
				return true;
			}
			else
				return false;
		}

	}
}