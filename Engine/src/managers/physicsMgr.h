/*
* physicMgr.h
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
#ifndef PHYSICS_H
#define PHYSICS_H

#include <vector>
#include <unordered_map>
#include <memory>
#include <utility>
#include <string>
#include "../graphics/mesh3D.h"
#include "../wrapper/physxWrapper.h"
#include "../entity/entity.h"

namespace robolab {

	enum MeasurementUnit {
		UNIT_METER,
		UNIT_CENTIMETER,
		UNIT_MILLIMETER
	};

	namespace manager {

		class PhysicsMgr
		{
		private:
			struct PhysicScene
			{
			private:
				std::size_t actorCount;
			public:
				std::string name;
				physx::PxScene* scene;
			public:
				PhysicScene(const std::string& Name, physx::PxScene* Scene)
					: name(Name) {
					scene = Scene;
					actorCount = 0;
				}

				~PhysicScene() {
					scene->release();
				}

				void addActor(physx::PxActor& physxActor) {
					scene->addActor(physxActor);
					actorCount++;
				}

				void simulate(float deltaTime) {
					scene->simulate(deltaTime);
					scene->fetchResults(true);
					updateDynamicTransform(scene);
				}

				const std::size_t& getActorCount() const {
					return actorCount;
				}

				void shutdown() {
					//scene->lockRead();
					scene->lockWrite();
					scene->release();
				}

			void updateDynamicTransform(physx::PxScene* scene) {
					physx::PxU32 nrOfTransform;
					const physx::PxActiveTransform* dynamicTransforms = scene->getActiveTransforms(nrOfTransform);
					for (auto ii = 0; ii < nrOfTransform; ii++) {
						const physx::PxActiveTransform activeTransform = dynamicTransforms[ii];
						entity::Entity* actor = static_cast<entity::Entity*>(activeTransform.userData);
						actor->getComponent<entity::component::PhysicComponent>()->updateTransform();
					}
				}

			};
		private:
			static physx::PxFoundation* foundation;
			static physx::PxPhysics* physicsSDK;
			static physx::PxCooking* cooking;
			static physx::PxTolerancesScale* worldScale;
			static PhysicScene* physicScene;
			static physx::PxScene* scene;
			static physx::PxVec3 gravityVector;
			static bool isInitialized;
			static std::unordered_map<std::string, std::vector<physx::PxShape*>> physicShapes;
		public:
			static wrapper::CustomAllocatorCallback* customAllocatorCallback;
			static wrapper::CustomErrorCallback* customErrorCallback;
			static wrapper::CustomEventCallback* customEventCallback;
		public:
			static bool initialize(MeasurementUnit type);
			static std::vector<physx::PxShape*> createPhysicShape(const std::string& meshName, graphics::PhysicalProperty& physicalProperty);
			static physx::PxRigidActor* submitPhysicActor(entity::Entity* owner, std::vector<physx::PxShape*> shapeList, graphics::PhysicalProperty& physicalProperty, bool isDynamic);
			static void update(float deltaTime);
			static void shutdown();
		};

	}
}
#endif // !PHYSICS_H
