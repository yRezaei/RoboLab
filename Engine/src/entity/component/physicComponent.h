#ifndef PHYSIC_COMPONENT_H
#define PHYSIC_COMPONENT_H

#include "icomponent.h"
#include "../../mathematic/math3D.h"
#include "../../graphics/mesh3D.h"


namespace robolab {
	namespace wrapper {
		class CustomEventCallback;
	}
}


namespace robolab {
	using namespace math3D;
	using namespace graphics;

	namespace entity {
		namespace component {
			enum PhysicFlag {
				PHYSIC_SET_ENABLE,
				PHYSIC_SET_DISABLE,
				PHYSIC_SET_SLEEP,
				PHYSIC_SET_DEEP_SLEEP,
				PHYSIC_SET_AWAK
			};

			class TransformComponent;
			class PhysicComponent : public IComponent
			{
				friend wrapper::CustomEventCallback;
				friend class TransformComponent;
			private:
				std::vector<physx::PxShape*> shapeList;
				PhysicalProperty physicalProperty;
				bool isDynamic;
				float defaultSleepThreshold;
				bool isCollided;
				double collisionTime;
				Entity* collidedEntity;
			public:
				physx::PxRigidActor* physxActor;
			public:
				PhysicComponent(const std::string& meshName, PhysicalProperty& physxProperty, bool isDynamic);
				~PhysicComponent();
			public:
				void init() override;
				bool isDynamicObject();
				bool isSleeping();
				void setFlag(PhysicFlag type);
				void addForce(Vec3f& force);
				void addTorque(Vec3f& torque);
				void removeForce();
				void removeTorque();
				void setPosition(Vec3f& position);
				void setRotation(Quat& rotation);
				void setTransform(Vec3f& position, Quat& rotation);
				Mat4 getTransform();
				void updateTransform();
				bool hasCollision();
				Entity* getCollidedObject();
			private:
				void setGlobalTransform(const Mat4& mat4);
				void updateCollision(Entity* otherEntity);
			};
		}
	}
}


#endif // !PHYSIC_COMPONENT_H
