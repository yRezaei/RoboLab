#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <bitset>

#include "icomponent.h"
#include "transformComponent.h"
#include "renderableComponent.h"
#include "physicComponent.h"

namespace robolab {
	namespace entity {

		using EntityID = std::size_t;

		inline EntityID getUniqueEntityID() {
			static EntityID uniqueActorID{ 0u };
			return uniqueActorID++;
		}


	}// !namespace entity
}// !namespace robolab


#endif // !COMPONENTS_H


