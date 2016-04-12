#ifndef BP_SYMBOLIC_NUMERIC_CONVERSION_H
#define BP_SYMBOLIC_NUMERIC_CONVERSION_H

#include "../src/engine.h"
#include "symbolicNumeric/SymbolState.h"
#include "symbolicNumeric/StateDescriptionReader.h"
#include "symbolicNumeric/GeometricalState.h"

#include "symbolicNumeric\Scenario.h"

class BP_SymbolicNumericConversion : public IBlueprint
{
public:
	Entity Grid;
	bool conitueSimulation, enablePhysics, enableDrawing;
	std::size_t nrOfInstance;
	//###########
	StateDescriptionReader descriptionReader;
	SymbolState stateDescription;
	GeometricalState stateGeometry;

	RandomFloat randPitch;
	RandomFloat randYaw;
	RandomFloat randRoll;

	RandomFloat randX;
	RandomFloat randY;
	RandomFloat randZ;

	RandomInt randSym;
public:
	BP_SymbolicNumericConversion(std::size_t NrOfInstace) {
		nrOfInstance = NrOfInstace;
	}

	~BP_SymbolicNumericConversion() {
	}

	void init() override;
	void update(float deltaTime) override;
	void destroy() override;
};



void BP_SymbolicNumericConversion::init() {
		
	RenderMgr::initialize("Robo-Lab", Vec2i(800, 600), false);
	PhysicsMgr::initialize(UNIT_METER);

	ResourceMgr::loadMeshFile("../Resources/internal", "grid", ResourceMgr::MESH_RENDERING, Vec3f(0.1f));
	if (ResourceMgr::existRenderMesh("grid")) {
		Grid.setName("Grid");
		Grid.addComponent<RenderableComponent>("grid");
	}
	else
		system::Logging::console(system::LOG_WARNING, "No mesh found loaded with name GRID.");
		
	//###################################################

	//ResourceMgr::loadMeshFile("../Resources/obj_objects/", "bottle_water_glass2", ResourceMgr::MESH_RENDERING | ResourceMgr::MESH_PHYSIC_SIMULATION, Vec3f(0.01f));
	//ResourceMgr::loadMeshFile("../Resources/obj_objects/", "table_curved", ResourceMgr::MESH_RENDERING | ResourceMgr::MESH_PHYSIC_SIMULATION, Vec3f(0.01f));

	unsigned int instanceGap = 0;
	while ((instanceGap * instanceGap) < nrOfInstance)
		instanceGap += 1;

	/*auto idx = 0.0f;
	auto idy = 0.0f;
	for (auto i = 1; i <= nrOfInstance; i++) {

		std::shared_ptr<BP_SimpleRandomInstance> bp = std::make_shared<BP_SimpleRandomInstance>(
			Vec3f(idx, idy, 0.0f), "bottle_water_glass2", "table_curved");
		bp->init();
		insanceList.push_back(bp);

		idx += 3;
		if (i % instanceGap == 0) {
			idx = 0;
			idy += 3;
		}
	}*/

	SceneInfo scene;
	readSceneDescription("../Resources/scenario/sceneDescription.xml", scene);
	for (auto m : scene.meshList)
		std::cout << m.path +"/"+ m.name << std::endl;
	for (auto o : scene.objectList)
		std::cout << o.name + " " + o.mesh + " " + o.type << std::endl;
	

	symbolicNumeric::Scenario scenario;
	scenario.loadDescriptionFile("../Resources/scenario/problemDescription.xml");
	for (auto i : scenario.initilStatePredicates) {
		std::cout << "Predicate " << std::endl;
		std::cout << "\tType: " + i.type + "   , Name: " + i.name + "   , Validity: " + i.validity << std::endl;
		std::cout << "\tArguments: ";
		for(auto a : i.arguments)
			std::cout << a.first + " " + a.second;
		std::cout << std::endl;
		std::cout << "\tActive:    ";
		for(auto a : i.active)
			std::cout << a + " ";
		std::cout << std::endl;
		std::cout << "\tPassive:   ";
		for (auto a : i.passive)
			std::cout << a + " ";
		std::cout << std::endl;
	}

}



void BP_SymbolicNumericConversion::update(float deltaTime)
{
	utils::Timer::update();

	//##########################################
	if (Input::KeyPressed(KEY_S)) {
		if (conitueSimulation)
			conitueSimulation = false;
		else
			conitueSimulation = true;
	}

	//##########################################
	if (Input::KeyPressed(KEY_P)) {
		if (enablePhysics)
			enablePhysics = false;
		else
			enablePhysics = true;
	}

	//##########################################
	if (Input::KeyPressed(KEY_D)) {
		if (enableDrawing)
			enableDrawing = false;
		else
			enableDrawing = true;
	}

	if (conitueSimulation) {
		/*for (auto instance : insanceList)
			instance->update(deltaTime);*/
	}

	//##########################################
	if (enablePhysics)
		manager::PhysicsMgr::update(1 / 60.f);

	manager::RenderMgr::update(enableDrawing);
}

void BP_SymbolicNumericConversion::destroy() {
	Logging::console(system::LOG_INFORMATION, "Cleaning up Renderable objects.");
	manager::RenderMgr::shutdown();

	Logging::console(system::LOG_INFORMATION, "Cleaning up NVIDIA Physx objects.");
	PhysicsMgr::shutdown();

	Logging::console(system::LOG_INFORMATION, "Cleaning up Loaded resources.");
	manager::ResourceMgr::shutdown();

	Logging::console(system::LOG_NOTICE, "Bye bye.");
}


#endif // !BP_MAIN_SIMPLE_RANDOM_H



