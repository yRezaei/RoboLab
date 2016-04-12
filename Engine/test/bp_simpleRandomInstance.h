#ifndef BP_SIMPLE_RANDOM_INSTANCE_H
#define BP_SIMPLE_RANDOM_INSTANCE_H

#include "../src/engine.h"


class BP_SimpleRandomInstance : public IBlueprint
{
public:
	Vec3f rootPos;
	std::shared_ptr<RigidObject> dropObject;
	std::shared_ptr<RigidObject> surfaceObject;

	Bounds* surfaceObjectBounds;
	bool collision;
	utils::UniformRandomFloat randUX;
	utils::UniformRandomFloat randUY;

	utils::UniformRandomFloat randURoll;
	utils::UniformRandomFloat randUPitch;
	utils::UniformRandomFloat randUYaw;
	float dropHeight;
	float resetTime;
public:
	BP_SimpleRandomInstance(Vec3f& root, const std::string& dropObjectName, const std::string& surfaceObjectName) {
		rootPos = root;
		if (ResourceMgr::existRenderMesh(dropObjectName)) {
			dropObject = std::make_shared<RigidObject>("bottle_water_glass2", makeMat4(rootPos), dropObjectName, true);
		}

		if (ResourceMgr::existRenderMesh(surfaceObjectName)) {
			surfaceObject = std::make_shared<RigidObject>("Surface", makeMat4(rootPos), surfaceObjectName, false);
			surfaceObjectBounds = &ResourceMgr::getRenderMesh(surfaceObjectName)->bounds;
		}
		collision = false;
	}

	~BP_SimpleRandomInstance() {
	}

	void init() override {
		dropHeight = surfaceObjectBounds->getMax().z + (surfaceObjectBounds->getMax().z / 3.0f);
		randUX.setRange(surfaceObjectBounds->getMin().x, surfaceObjectBounds->getMax().x);
		randUY.setRange(surfaceObjectBounds->getMin().y, surfaceObjectBounds->getMax().y);

		randURoll.setRange(Deg2Rad(-50), Deg2Rad(50));
		randUPitch.setRange(Deg2Rad(-50), Deg2Rad(50));
		randUYaw.setRange(Deg2Rad(-50), Deg2Rad(50));

		dropObject->setTransform(makeMat4(rootPos + Vec3f(randUX.next(), randUY.next(), dropHeight), makeQuat(EulerAngles(randURoll.next(), randUPitch.next(), randUYaw.next()))));
	}



	void update(float deltaTime) override
	{
		CollisionInfo hit;
		if (dropObject->onCollision(hit))
			collision = true;

		if (collision && resetTime > 1.5f) {
			collision = false;
			dropObject->setTransform(makeMat4(rootPos + Vec3f(randUX.next(), randUY.next(), dropHeight), makeQuat(EulerAngles(randURoll.next(), randUPitch.next(), randUYaw.next()))));
			resetTime = 0.0f;
		}

		if (resetTime > 2.5f) {
			dropObject->setTransform(makeMat4(rootPos + Vec3f(randUX.next(), randUY.next(), dropHeight), makeQuat(EulerAngles(randURoll.next(), randUPitch.next(), randUYaw.next()))));
			resetTime = 0.0f;
		}
		resetTime += deltaTime;
	}

	void destroy() override {
		Logging::console(system::LOG_INFORMATION, "Cleaning up Renderable objects.");
		manager::RenderMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up NVIDIA Physx objects.");
		PhysicsMgr::shutdown();

		Logging::console(system::LOG_INFORMATION, "Cleaning up Loaded resources.");
		manager::ResourceMgr::shutdown();

		Logging::console(system::LOG_NOTICE, "Bye bye.");
	}
};


#endif // !BP_SIMPLE_RANDOM_INSTANCE_H

