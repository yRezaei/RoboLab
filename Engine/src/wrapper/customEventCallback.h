#ifndef CUSTOM_EVENT_CALLBACK_H
#define CUSTOM_EVENT_CALLBACK_H

#include <physx/PxPhysicsAPI.h>
#include <physx/PxPhysics.h>

namespace robolab {
	namespace wrapper {

		class CustomEventCallback : public physx::PxSimulationEventCallback
		{
		public:
			CustomEventCallback();
			~CustomEventCallback();
			void onConstraintBreak(physx::PxConstraintInfo* constraints, physx::PxU32 count) override;
			void onWake(physx::PxActor** actors, physx::PxU32 count) override;
			void onSleep(physx::PxActor** actors, physx::PxU32 count) override;
			void onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs) override;
			void onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 nbPairs) override;
		}; // end of class EventCallback

	}
}

#endif // !CUSTOM_ALLOCATOR_CALLBACK_H
