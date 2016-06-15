#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include "../src/engine.h"

class BP_Main_SimpleTest : public IBlueprint
{
public:
	Entity Grid;
	std::shared_ptr<RigidObject> dropObject;
	std::shared_ptr<RigidObject> surfacePbject;
	Bounds surfaceBounds;
	utils::UniformRandomFloat randUX;
	utils::UniformRandomFloat randUY;
	//utils::UniformRandomFloat randUZ;
	utils::UniformRandomFloat randURoll;
	utils::UniformRandomFloat randUPitch;
	utils::UniformRandomFloat randUYaw;
	float dropHeight;
public:
	BP_Main_SimpleTest() {
	}

	~BP_Main_SimpleTest() {
	}

	void init() override {

		Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, "../Resources/internal", "grid", Vec3f(0.1f));

		Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, "../Resources/obj_objects/", "bottle_water_glass2", Vec3f(0.01f));
		Resource::loadMesh(Resource::MeshUsageType::PHYSIC_SIMULATION, "../Resources/obj_objects/", "bottle_water_glass2", Vec3f(0.01f));

		Resource::loadMesh(Resource::MeshUsageType::VISUALIZATION, "../Resources/obj_objects/", "table_curved", Vec3f(0.01f));
		Resource::loadMesh(Resource::MeshUsageType::PHYSIC_SIMULATION, "../Resources/obj_objects/", "table_curved", Vec3f(0.01f));

		Grid.setName("Grid");
		Grid.addComponent<RenderableComponent>("grid");


		dropObject = std::make_shared<RigidObject>("bottle_water_glass2", Mat4(1.0f), "bottle_water_glass2", true);

		surfacePbject = std::make_shared<RigidObject>("table_curved", Mat4(1.0f), "table_curved", false);
		surfaceBounds = Resource::getVisualMesh("table_curved").second->getBounds();

		dropHeight = surfaceBounds.getMax().z + (surfaceBounds.getMax().z / 3.0f);
		randUX.setRange(surfaceBounds.getMin().x, surfaceBounds.getMax().x);
		randUY.setRange(surfaceBounds.getMin().y, surfaceBounds.getMax().y);
		//randUZ.setRange(Deg2Rad(-50), Deg2Rad(50));

		randURoll.setRange(Deg2Rad(-50), Deg2Rad(50));
		randUPitch.setRange(Deg2Rad(-50), Deg2Rad(50));
		randUYaw.setRange(Deg2Rad(-50), Deg2Rad(50));

		dropObject->setTransform(makeMat4(Vec3f(randUX.next(), randUY.next(), dropHeight), makeQuat(EulerAngles( randURoll.next(), randUPitch.next(), randUYaw.next()))));
	}

	

	void update(float deltaTime) override
	{
		if (Input::KeyPressed(KEY_ESCAPE))
			Engine::shutdown();

		//##########################################
		if (Input::KeyPressed(KEY_R))
			dropObject->setTransform(makeMat4(Vec3f(randUX.next(), randUY.next(), dropHeight), makeQuat(EulerAngles(randURoll.next(), randUPitch.next(), randUYaw.next()))));
		
		//##########################################
		CollisionInfo hit;
		if(dropObject->onCollision(hit))
			Logging::console(system::LOG_NOTICE, dropObject->getName() + " is collided with " + hit.otherObject->getName() );
		if (surfacePbject->onCollision(hit))
			Logging::console(system::LOG_NOTICE, surfacePbject->getName() + " is collided with " + hit.otherObject->getName() );
		//##########################################
	}

	void destroy() override {
	}
};

#endif // !SURFACE_POINT_VALIDITY_TEST_H


