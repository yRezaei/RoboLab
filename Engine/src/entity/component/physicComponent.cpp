#include "physicComponent.h"

#include "../entity.h"
#include "../../managers/physicsMgr.h"
#include "../../managers/renderMgr.h"
#include "../../system/logging.h"
#include "../../utils/timer.h"


namespace robolab {
	using namespace manager;

	namespace entity {
		namespace component {

			PhysicComponent::PhysicComponent(const std::string& meshName, graphics::PhysicalProperty& physxProperty, bool IsDynamic) {
				isDynamic = IsDynamic;
				physicalProperty = physxProperty;
				shapeList = PhysicsMgr::createPhysicShape(meshName, physicalProperty);
			}

			PhysicComponent::~PhysicComponent() {
				if (physxActor)
					physxActor->release();
			}

			void PhysicComponent::init() {
				physxActor = PhysicsMgr::submitPhysicActor(owner, shapeList, physicalProperty, isDynamic);
				if (isDynamic)
					defaultSleepThreshold = static_cast<physx::PxRigidDynamic*>(physxActor)->getSleepThreshold();
				physxActor->userData = owner;
				setGlobalTransform( owner->getTransform() );
			}

			bool PhysicComponent::isDynamicObject() {
				return isDynamic;
			}

			bool PhysicComponent::isSleeping() {
				if (isDynamic) {
					return physxActor->isRigidDynamic()->isSleeping();
				}
				return false;
			}

			void PhysicComponent::setFlag(PhysicFlag type) {
				switch (type)
				{
				case PHYSIC_SET_ENABLE:
					this->physxActor->setActorFlags(physx::PxActorFlag::eVISUALIZATION);
					break;
				case PHYSIC_SET_DISABLE:
					physxActor->setActorFlags(physx::PxActorFlag::eDISABLE_SIMULATION);
					break;
				case PHYSIC_SET_SLEEP:
					if (isDynamic)
						physxActor->isRigidDynamic()->putToSleep();
					break;
				case PHYSIC_SET_DEEP_SLEEP:
					if (isDynamic) {
						static_cast<physx::PxRigidDynamic*>(physxActor)->setSleepThreshold(PX_MAX_F32);
						static_cast<physx::PxRigidDynamic*>(physxActor)->putToSleep();
					}
					break;
				case PHYSIC_SET_AWAK:
					if (isDynamic) {
						//static_cast<physx::PxRigidDynamic*>(physxActor)->setSleepThreshold(defaultSleepThreshold);
						static_cast<physx::PxRigidDynamic*>(physxActor)->wakeUp();
					}
					break;
				default:
					break;
				}
			}

			void PhysicComponent::addForce(Vec3f& force) {
				if (isDynamic)
					static_cast<physx::PxRigidDynamic*>(physxActor)->addForce(makePxVec3(force));
			}

			void PhysicComponent::addTorque(Vec3f& torque) {
				if (isDynamic)
					static_cast<physx::PxRigidDynamic*>(physxActor)->addForce(makePxVec3(torque));
			}

			void PhysicComponent::removeForce() {
				if (isDynamic) {
					setFlag(PHYSIC_SET_DISABLE);
					static_cast<physx::PxRigidDynamic*>(physxActor)->clearForce();
					setFlag(PHYSIC_SET_DISABLE);
					setFlag(PHYSIC_SET_AWAK);
				}
			}

			void PhysicComponent::removeTorque() {
				if (isDynamic) {
					setFlag(PHYSIC_SET_DISABLE);
					static_cast<physx::PxRigidDynamic*>(physxActor)->clearTorque();
					setFlag(PHYSIC_SET_ENABLE);
					setFlag(PHYSIC_SET_AWAK);
				}
			}

			void PhysicComponent::setPosition(Vec3f& position) {
				setFlag(PHYSIC_SET_DISABLE);
				removeForce();
				removeTorque();
				physxActor->setGlobalPose(makePxTransform(position, makeQuat(physxActor->getGlobalPose().q)));
				setFlag(PHYSIC_SET_ENABLE);
				setFlag(PHYSIC_SET_AWAK);
			}

			void PhysicComponent::setRotation(Quat& rotation) {
				setFlag(PHYSIC_SET_DISABLE);
				removeForce();
				removeTorque();
				physxActor->setGlobalPose(makePxTransform(makeVec3f(physxActor->getGlobalPose().p), rotation));
				setFlag(PHYSIC_SET_ENABLE);
				setFlag(PHYSIC_SET_AWAK);
			}

			void PhysicComponent::setTransform(Vec3f& position, Quat& rotation) {
				setFlag(PHYSIC_SET_DISABLE);
				removeForce();
				removeTorque();
				physxActor->setGlobalPose(makePxTransform(position, rotation));
				setFlag(PHYSIC_SET_ENABLE);
				setFlag(PHYSIC_SET_AWAK);
			}

			void PhysicComponent::setGlobalTransform(const Mat4& mat4) {
				setFlag(PHYSIC_SET_DISABLE);
				removeForce();
				removeTorque();
				physxActor->setGlobalPose(makePxTransform(mat4));
				setFlag(PHYSIC_SET_ENABLE);
				setFlag(PHYSIC_SET_AWAK);
			}

			Mat4 PhysicComponent::getTransform() {
				return makeMat4(physxActor->getGlobalPose());
			}

			void PhysicComponent::updateTransform() {
				owner->getComponent<TransformComponent>()->transform = makeMat4(physxActor->getGlobalPose());
				if (owner->hasComponent<RenderableComponent>()) {
					std::size_t glID = owner->getComponent<RenderableComponent>()->getGLBufferIDs()->getID();
					int transformID = owner->getComponent<RenderableComponent>()->index;
					RenderMgr::updateActorTransform(glID, transformID, makeMat4(physxActor->getGlobalPose()));
				}
			}

			bool PhysicComponent::hasCollision() {
				if (isCollided && utils::Timer::getTotalTime() - collisionTime < 0.1)
					isCollided = true;
				else
				{
					collidedEntity = NULL;
					isCollided = false;
				}
				return isCollided;
			}

			Entity* PhysicComponent::getCollidedObject() {
				isCollided = false;
				return collidedEntity;
			}

			void PhysicComponent::updateCollision(Entity* otherEntity) {
				collisionTime = utils::Timer::getTotalTime();
				collidedEntity = otherEntity;
				isCollided = true;
			}
		}
	}
}