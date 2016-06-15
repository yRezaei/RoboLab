#include "physicsMgr.h"

#include "../managers/resource.h"
#include "../entity/component/transformComponent.h"
#include "../system/logging.h"
#include "../graphics/mesh.h"

namespace robolab {
	using namespace wrapper;
	using namespace system;

	namespace manager {

		physx::PxFoundation* PhysicsMgr::foundation;
		physx::PxPhysics* PhysicsMgr::physicsSDK;
		physx::PxCooking* PhysicsMgr::cooking;
		physx::PxTolerancesScale* PhysicsMgr::worldScale;
		PhysicsMgr::PhysicScene* PhysicsMgr::physicScene;
		physx::PxScene* PhysicsMgr::scene;
		physx::PxVec3 PhysicsMgr::gravityVector;
		bool PhysicsMgr::isInitialized;
		std::unordered_map<std::string, std::vector<physx::PxShape*>> PhysicsMgr::physicShapes;

		//##################################################################

		bool PhysicsMgr::initialize(MeasurementUnit type) {
			isInitialized = false;
			wrapper::CustomAllocatorCallback* customAllocatorCallback = new wrapper::CustomAllocatorCallback();
			wrapper::CustomErrorCallback* customErrorCallback = new wrapper::CustomErrorCallback();
			wrapper::CustomEventCallback* customEventCallback = new wrapper::CustomEventCallback();
			worldScale = new physx::PxTolerancesScale();
			switch (type)
			{
			case robolab::UNIT_METER:
				worldScale->length = 1;
				worldScale->mass = 1000;
				worldScale->speed = 9.806f;
				break;
			case robolab::UNIT_CENTIMETER:
				worldScale->length = 100;
				worldScale->mass = 1000;
				worldScale->speed = 98.06f;
				break;
			case robolab::UNIT_MILLIMETER:
				worldScale->length = 1000;
				worldScale->mass = 1000;
				worldScale->speed = 980.6f;
				break;
			default:
				worldScale->length = 1;
				worldScale->mass = 1000;
				worldScale->speed = 9.806f;
				break;
			}
			gravityVector = physx::PxVec3(0.0f, 0.0f, -worldScale->speed);
			foundation = wrapper::nvidiaPhysx::createFoundation(*customAllocatorCallback, *customErrorCallback);
			if (foundation) {
				Logging::console(LOG_INFORMATION, "NVIDIA Physx foundation is initialized successfully.");
				physicsSDK = wrapper::nvidiaPhysx::createPhysics(*foundation, *worldScale);
				if (physicsSDK) {
					Logging::console(LOG_INFORMATION, "NVIDIA Physx factory object is initialized successfully.");
					if (wrapper::nvidiaPhysx::enableExtentions(*physicsSDK)) {
						Logging::console(LOG_INFORMATION, "NVIDIA Physx extension is initialized successfully.");
						scene = wrapper::nvidiaPhysx::createScene(*physicsSDK, gravityVector, *worldScale, *customEventCallback, 3);
						//physicScene = new PhysicScene("Main", wrapper::nvidiaPhysx::createScene(*physicsSDK, sceneDescriptor));
						if (scene) {
							Logging::console(LOG_INFORMATION, "NVIDIA Physx scene is initialized successfully.");
							isInitialized = true;
						}
						else {
							Logging::console(LOG_ERROR, "NVIDIA Physx scene is NOT initialized.\nPhysicScene object is null", LOCATION);
							isInitialized = false;
						}
					}
					else {
						Logging::console(LOG_ERROR, "NVIDIA cooking is NOT initialized."
							" wrapper::nvidiaPhysx::enableExtentions(*physicsSDK) returned FALSE.", LOCATION);
						isInitialized = false;
					}
				}
				else {
					Logging::console(LOG_ERROR, "NVIDIA Physx factory object is NOT initialized. Physx-factory object is null.", LOCATION);
					isInitialized = false;
				}
			}
			else {
				Logging::console(LOG_ERROR, "NVIDIA Physx foundation is NOT initialized. Foundation object is null.", LOCATION);
				isInitialized = false;
			}
			return isInitialized;
		}

		std::vector<physx::PxShape*> PhysicsMgr::createPhysicShape(const std::string& meshName, graphics::PhysicalProperty& physicalProperty) {
			std::vector<physx::PxShape*> shapeList;
			if (physicShapes.find(meshName) == physicShapes.end())
			{
				auto& meshList = Resource::getPhysicalMesh(meshName);
				if (meshList.first) {
					for (auto mesh : meshList.second) {
						shapeList.push_back(nvidiaPhysx::createConvexShape(mesh, *foundation, *physicsSDK, 0.0001f, *worldScale, physicalProperty));
					}
				}
				else {
					shapeList.push_back(nvidiaPhysx::createBoxShape(*physicsSDK, physx::PxVec3(0.5f), physx::PxVec3(0.0f),
						nvidiaPhysx::createMaterial(*physicsSDK, physicalProperty)));
					Logging::console(LOG_NOTICE, "No mesh data exist for the given mesh name \"" + meshName + "\".", LOCATION);
				}
			}
			else
				shapeList = physicShapes[meshName];	
			return shapeList;
		}

		physx::PxRigidActor* PhysicsMgr::submitPhysicActor(entity::Entity* owner, std::vector<physx::PxShape*> shapeList, graphics::PhysicalProperty& physicalProperty, bool isDynamic) {
			physx::PxRigidActor* actor;
			if (isDynamic) {
				actor = nvidiaPhysx::createDynamicActor(*physicsSDK, shapeList,
					makePxTransform(owner->getComponent<entity::component::TransformComponent>()->getTransform()), physicalProperty);
				
			}
			else {			
				actor = nvidiaPhysx::createStaticActor(*physicsSDK, shapeList,
					makePxTransform(owner->getComponent<entity::component::TransformComponent>()->getTransform()), physicalProperty);
			}
			scene->addActor(*actor);
			return actor;
		}

		void PhysicsMgr::update(float deltaTime) {
			//physicScene->simulate(deltaTime);
			scene->simulate(deltaTime);
			scene->fetchResults(true);

			wrapper::nvidiaPhysx::updateDynamicTransform(scene);
		}

		void PhysicsMgr::shutdown() {
			if (scene)
				scene->release();

			if(physicsSDK)
				physicsSDK->release();

			//if(foundation) {
				//foundation->release();
				//Logging::console(LOG_NOTICE, "foundation released.", LOCATION);
			//}
		}


	}
}