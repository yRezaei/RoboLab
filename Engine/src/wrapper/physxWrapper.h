/*
* physxWrapper.h
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
#ifndef PHYSX_H
#define PHYSX_H

#include <memory>
#include <string>
#include <utility>
#include <Poco/Platform.h>
#include <physx/PxPhysicsAPI.h>
#include <physx/PxPhysics.h>
#include "customAllocatorCallback.h"
#include "customEventCallback.h"
#include "customErrorCallback.h"
#include "../mathematic/math3D.h"
#include "../commen/dataTypes.h"
#include "../system/logging.h"
#include "../graphics/mesh3D.h"
#include "../entity/entity.h"
#include "../graphics/mesh.h"


namespace robolab {
	using namespace math3D;
	using namespace graphics;

	namespace wrapper {
		namespace nvidiaPhysx
		{

			//#########################################################

			inline physx::PxFilterFlags CustomSimulationFilterShader(
				physx::PxFilterObjectAttributes attribute0, physx::PxFilterData filterData0,
				physx::PxFilterObjectAttributes attribute1, physx::PxFilterData filterData1,
				physx::PxPairFlags& pairFlags, const void* constantBlock, physx::PxU32 constantBlockSize)
			{
				if ((attribute0 & physx::PxFilterObjectFlag::eTRIGGER) != 0 || (attribute1 & physx::PxFilterObjectFlag::eTRIGGER) != 0) {
					pairFlags = physx::PxPairFlag::eTRIGGER_DEFAULT;
					return physx::PxFilterFlags();
				}
				pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT | physx::PxPairFlag::eNOTIFY_TOUCH_FOUND;
				return physx::PxFilterFlags();
			}

			//###############################################################################

			inline physx::PxFoundation* createFoundation(CustomAllocatorCallback& AllocatorCallback, CustomErrorCallback& ErrorCallback) {
				return PxCreateFoundation(PX_PHYSICS_VERSION, AllocatorCallback, ErrorCallback);
			}

			inline physx::PxPhysics* createPhysics(physx::PxFoundation& foundation, physx::PxTolerancesScale& worldScale ) {
				return PxCreatePhysics(PX_PHYSICS_VERSION, foundation, worldScale);
			}

			inline bool enableExtentions(physx::PxPhysics& physicsSDK) {
				if (PxInitExtensions(physicsSDK))
					return true;
				else
					return false;
			}

			inline physx::PxMaterial* createMaterial(physx::PxPhysics& physicsSDK, PhysicalProperty& physxProperty) {
				return physicsSDK.createMaterial(physxProperty.friction, physxProperty.dynamicFriction, physxProperty.restitution);
			}

			inline physx::PxScene* createScene(physx::PxPhysics& physicsSDK, physx::PxVec3& gravity, physx::PxTolerancesScale& worldScale,
				CustomEventCallback& customEventCallback, unsigned int nrOfThread) 
			{
				physx::PxSceneDesc sceneDesc(worldScale);
				sceneDesc.flags |= physx::PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
				sceneDesc.flags |= physx::PxSceneFlag::eREQUIRE_RW_LOCK;
				sceneDesc.flags |= physx::PxSceneFlag::eENABLE_CCD;
				sceneDesc.flags |= physx::PxSceneFlag::eENABLE_STABILIZATION;
				sceneDesc.simulationEventCallback = &customEventCallback;
				sceneDesc.gravity = gravity;
				sceneDesc.cpuDispatcher = physx::PxDefaultCpuDispatcherCreate(nrOfThread);
				sceneDesc.filterShader = CustomSimulationFilterShader;
				return physicsSDK.createScene(sceneDesc);
			}

			inline physx::PxShape* createBoxShape(physx::PxPhysics& physicsSDK, physx::PxVec3& halfExtent, physx::PxVec3& center, physx::PxMaterial* physxMaterial) {
				physx::PxShape* boxShape = physicsSDK.createShape(physx::PxBoxGeometry(halfExtent), *physxMaterial);
				boxShape->setLocalPose(physx::PxTransform(center, physx::PxQuat::createIdentity()));
				return boxShape;
			}

			inline physx::PxShape* createConvexShape(std::shared_ptr<graphics::Mesh> buffer, physx::PxFoundation& foundation, 
				physx::PxPhysics& physicsSDK, float skinWidth, physx::PxTolerancesScale& worldScale, PhysicalProperty& physxProperty) 
			{
				physx::PxCookingParams CookingParams(worldScale);
				CookingParams.skinWidth = skinWidth;
				physx::PxCooking* cooking = PxCreateCooking(PX_PHYSICS_VERSION, foundation, CookingParams);
				physx::PxConvexMeshDesc meshDesc;
				auto rowVertices = buffer->getRowVertices();
				meshDesc.points.data = rowVertices.data();
				meshDesc.points.count = (physx::PxU32)rowVertices.size();
				meshDesc.points.stride = sizeof(Vec3f);
				meshDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX | physx::PxConvexFlag::eINFLATE_CONVEX;

				physx::PxShapeFlags shapeFlags = physx::PxShapeFlag::eSIMULATION_SHAPE;
				physx::PxDefaultMemoryOutputStream output;
				if (!cooking->cookConvexMesh(meshDesc, output))
					return NULL;
				physx::PxDefaultMemoryInputData input(output.getData(), output.getSize());
				physx::PxConvexMesh* convexMesh = physicsSDK.createConvexMesh(input);
				physx::PxShape* convexShape = physicsSDK.createShape(physx::PxConvexMeshGeometry(convexMesh), *createMaterial(physicsSDK, physxProperty), shapeFlags);
				cooking->release();
				return convexShape;
			}

			inline physx::PxRigidActor* createStaticActor(physx::PxPhysics& physicsSDK, std::vector<physx::PxShape*>& physicShapes, 
				physx::PxTransform& transform, PhysicalProperty& physxProperty)
			{
				physx::PxRigidStatic* staticBody = physicsSDK.createRigidStatic(transform);
				for (auto i = 0; i < physicShapes.size(); i++)
					staticBody->attachShape(*physicShapes[i]);
				return static_cast<physx::PxRigidActor*>(staticBody);

			}

			inline physx::PxRigidActor* createDynamicActor(physx::PxPhysics& physicsSDK, std::vector<physx::PxShape*>& physicShapes,
				physx::PxTransform& transform, PhysicalProperty& physxProperty)
			{
				physx::PxRigidDynamic* dynamicBody = physicsSDK.createRigidDynamic(transform);
				for (auto i = 0; i < physicShapes.size(); i++) {
					dynamicBody->attachShape(*physicShapes[i]);
					physx::PxRigidBodyExt::updateMassAndInertia(*dynamicBody, 1.0f);
				}
				dynamicBody->setAngularDamping(physxProperty.angularDamping);
				dynamicBody->setLinearDamping(physxProperty.linearDamping);
				dynamicBody->setMass(physxProperty.mass);
				dynamicBody->setSolverIterationCounts(500, 500);
				dynamicBody->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, true);
				return static_cast<physx::PxRigidActor*>(dynamicBody);
			}

			inline void updateDynamicTransform( physx::PxScene* scene) {
				physx::PxU32 nrOfTransform;
				const physx::PxActiveTransform* dynamicTransforms = scene->getActiveTransforms(nrOfTransform);
				for (auto ii = 0; ii < nrOfTransform; ii++) {
					const physx::PxActiveTransform activeTransform = dynamicTransforms[ii];
					entity::Entity* actor = (entity::Entity*)(activeTransform.userData);
					actor->getComponent<entity::component::PhysicComponent>()->updateTransform();
				}
			}

		}
	}
}

#endif // !PHYSX_H

