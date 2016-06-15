/*
* customEventCallback.h
*
* Copyright 2016 Yashar Abbasalizadeh Rezaei <yashar.a.rezaei@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
* MA 02110-1301, USA.
*
*
*/
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
