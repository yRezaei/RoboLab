#include "customEventCallback.h"
#include "../entity/entity.h"


namespace robolab {
	namespace wrapper {

		CustomEventCallback::CustomEventCallback() {}

		CustomEventCallback::~CustomEventCallback() {}

		void CustomEventCallback::onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) {}

		void CustomEventCallback::onWake(physx::PxActor** actors, physx::PxU32 count) {}

		void CustomEventCallback::onSleep(physx::PxActor** actors, physx::PxU32 count) {}

		void CustomEventCallback::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) {
			if (pairHeader.flags & (physx::PxContactPairHeaderFlag::eDELETED_ACTOR_0 | physx::PxContactPairHeaderFlag::eDELETED_ACTOR_1)) {
				return;
			}
			entity::Entity* ac1 = (entity::Entity*)pairHeader.actors[0]->userData;
			entity::Entity* ac2 = (entity::Entity*)pairHeader.actors[1]->userData;
			ac1->getComponent<entity::PhysicComponent>()->updateCollision(ac2);
			ac2->getComponent<entity::PhysicComponent>()->updateCollision(ac1);
			/*for (unsigned int i = 0; i < nbPairs; i++) {
				physx::PxContactPair pair = pairs[i];
			}*/
		}

		void CustomEventCallback::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 nbPairs) {

			for (unsigned int i = 0; i < nbPairs; i++)
			{
				// Check if shapes were deleted
				if (pairs[i].flags & (physx::PxTriggerPairFlag::eDELETED_SHAPE_TRIGGER | physx::PxTriggerPairFlag::eDELETED_SHAPE_OTHER)) {
					continue;
				}

				physx::PxTriggerPair pair = pairs[i];

				physx::PxActor* ac1 = pair.triggerActor;
				physx::PxActor* ac2 = pair.otherActor;

				entity::Entity* actor1 = (entity::Entity*)(ac1->userData);
				entity::Entity* actor2 = (entity::Entity*)(ac2->userData);

				/*actor1->overLap.isTrue = true;
				actor1->overLap.otherActor = actor2;
				actor2->overLap.isTrue = true;
				actor2->overLap.otherActor = actor1;*/
			}
		}

	}
}