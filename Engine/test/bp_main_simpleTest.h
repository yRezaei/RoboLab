#ifndef SIMPLE_TEST_H
#define SIMPLE_TEST_H

#include "../src/engine.h"

class BP_Main_SimpleTest : public IBlueprint
{
public:
	Entity Grid;
	std::shared_ptr<RigidObject> dropObject;
	std::shared_ptr<RigidObject> surfacePbject;
	bool enablePhysic;
	Bounds* surfaceBounds;
	utils::UniformRandomFloat randUX;
	utils::UniformRandomFloat randUY;
	//utils::UniformRandomFloat randUZ;
	utils::UniformRandomFloat randURoll;
	utils::UniformRandomFloat randUPitch;
	utils::UniformRandomFloat randUYaw;
	float dropHeight;
public:
	BP_Main_SimpleTest() {
		enablePhysic = false;
	}

	~BP_Main_SimpleTest() {
	}

	void init() override {
		RenderMgr::initialize("Robo-Lab", Vec2i(800, 600), false);
		PhysicsMgr::initialize(UNIT_METER);

		ResourceMgr::loadMeshFile("../Resources/internal", "grid", ResourceMgr::MESH_RENDERING, Vec3f(0.1f));

		ResourceMgr::loadMeshFile("../Resources/obj_objects/", "bottle_water_glass2", ResourceMgr::MESH_RENDERING | ResourceMgr::MESH_PHYSIC_SIMULATION, Vec3f(0.01f));
		ResourceMgr::loadMeshFile("../Resources/obj_objects/", "table_curved", ResourceMgr::MESH_RENDERING | ResourceMgr::MESH_PHYSIC_SIMULATION, Vec3f(0.01f));

		if (ResourceMgr::existRenderMesh("grid")) {
			Grid.setName("Grid");
			Grid.addComponent<RenderableComponent>("grid");
		}
		else
			system::Logging::console(system::LOG_WARNING, "No mesh found loaded with name GRID.");

		if (ResourceMgr::existRenderMesh("bottle_water_glass2")) {
			dropObject = std::make_shared<RigidObject>("bottle_water_glass2", Mat4(1.0f), "bottle_water_glass2", true);
		}

		if (ResourceMgr::existRenderMesh("table_curved")) {
			surfacePbject = std::make_shared<RigidObject>("table_curved", Mat4(1.0f), "table_curved", false);
			surfaceBounds = &ResourceMgr::getRenderMesh("table_curved")->bounds;
		}

		dropHeight = surfaceBounds->getMax().z + (surfaceBounds->getMax().z / 3.0f);
		randUX.setRange(surfaceBounds->getMin().x, surfaceBounds->getMax().x);
		randUY.setRange(surfaceBounds->getMin().y, surfaceBounds->getMax().y);
		//randUZ.setRange(Deg2Rad(-50), Deg2Rad(50));

		randURoll.setRange(Deg2Rad(-50), Deg2Rad(50));
		randUPitch.setRange(Deg2Rad(-50), Deg2Rad(50));
		randUYaw.setRange(Deg2Rad(-50), Deg2Rad(50));

		dropObject->setTransform(makeMat4(Vec3f(randUX.next(), randUY.next(), dropHeight), makeQuat(EulerAngles( randURoll.next(), randUPitch.next(), randUYaw.next()))));
	}

	

	void update(float deltaTime) override
	{
		utils::Timer::update();
		
		//##########################################
		if (Input::KeyPressed(KEY_S))
			enablePhysic = true;
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
		
		if(enablePhysic)
			manager::PhysicsMgr::update(1 / 60.f);
		
		//##########################################
		manager::RenderMgr::update(true);
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

#endif // !SURFACE_POINT_VALIDITY_TEST_H


