#ifndef GLOBAL_H
#define GLOBAL_H

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/constants.hpp>

#include <limits>
#include <string>

enum class OrientationPredicates {
	ABITRARYORIENTATION = 1, 
	PARALLELXY, 
	PARALLELYZ, 
	PARALLELXZ, 
	STRAIGHTALONGX, 
	STRAIGHTALONGY, 
	STRAIGHTALONGZ,
	INVERTEDALONGX, 
	INVERTEDALONGY, 
	INVERTEDALONGZ
};

enum class ScenarioTypes { 
	BOOKS = 1, 
	POWER_PLUG = 2, 
	COFFEE_SUGAR = 3, 
	SIMPLE_TABLE = 4 
};

enum class ExecutionState { 
	INIT = 1, 
	GOAL = 2 
};

struct PredicateInfo
{
	std::string type;
	std::string name;
	std::string validity;
	std::unordered_map<std::string, std::string> arguments;
	std::vector<std::string> active;
	std::vector<std::string> passive;
	PredicateInfo() {}
	PredicateInfo(const std::string& Type, const std::string& Name, const std::string& Validity)
	: type(Type), name(Name), validity(Validity) {}
};

struct ScenarioInfo
{
	std::string name;
	unsigned int nrOfSamples;
	std::string action;
	std::vector<PredicateInfo> initilStatePredicates;
	std::vector<PredicateInfo> goalStatePredicates;
	ScenarioInfo() {}
};

struct Mesh3DInfo {
	std::string path;
	std::string name;
	Mesh3DInfo() {}
	Mesh3DInfo(std::string Path, std::string Name)
	: path(Path), name(Name) {}
	
};

struct ObjectInfo {
	std::string name;
	std::string mesh;
	Vec3f position;
	EulerAngles eulerAngles;
	std::string type;
	ObjectInfo() {}
	ObjectInfo(const std::string& Name, const std::string& meshName, const std::string& Type)
		: name(Name), mesh(meshName), type(Type) {}
	ObjectInfo(const std::string& Name, const std::string& meshName, Vec3f Position, EulerAngles euler, const std::string& Type) 
	: name(Name), mesh(meshName), position(Position), eulerAngles(euler), type(Type) {}
};

struct SceneInfo {
	std::vector<Mesh3DInfo> meshList;
	std::vector<ObjectInfo> objectList;
	SceneInfo() {}
	SceneInfo(std::vector<Mesh3DInfo>& MeshList, std::vector<ObjectInfo>& ObjectList)
	: objectList(ObjectList) {}
};


const float SMALLEST_ANGLE = 0.1f;
const float MPI = 3.141592653f;
const float EPSILON_TRANSLATION = 5.0f;
const float EPSILON_ROTATION = 10.0f;

const float TRANSLATION_DELTA = 5.0f;
const float ROTATION_DELTA = 10.0f;

const float SUCCESS_THRESHOLD = 0.8f;

const int OBJECTS_PER_FLOOR = 3;

const float ROTATION_MIN = 0.0f;
const float ROTATION_MAX = 360.0f;

const float CASE_X = -30.0f;
const float CASE_X_T = -15.0f;
const float CASE_Y = -350.0f;
const float CASE_Y_T = 0.0f;
const float CASE_Z = -70.0f;
const float CASE_Z_T = 0.0f;

const float FLOOR_X = 0.0f;
const float FLOOR_Y = 70.0f;
const float FLOOR_Z = -70.0f;

const float FLOOR_X_OFFSET = 1000;
const float CASE_X_OFFSET = 950;
const float CASE_Y_OFFSET = 350;

/**************************
* Simple table use case constants
***************************/
const float STABLE_UC_X_MIN = -70.0f;
const float STABLE_UC_X_MAX = 30.0f;
const float STABLE_UC_Y_MIN = -360.0f;
const float STABLE_UC_Y_MAX = -280.0f;
const float STABLE_UC_Z_MIN = 140.0f;
const float STABLE_UC_Z_MAX = 250.0f;

const float STABLE_UC_OBJ_X = -40.0f;
const float STABLE_UC_OBJ_Y = -320.0f;
const float STABLE_UC_OBJ_Z = 80.0f;
const float STABLE_UC_OBJ_ROLL = 0.0f;
const float STABLE_UC_OBJ_PITCH = 0.0f;
const float STABLE_UC_OBJ_YAW = 0.0f;

#endif // !GLOBAL_H