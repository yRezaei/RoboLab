#ifndef UTILS_H
#define UTILS_H

#include "../../src/engine.h"
#include <random>
#include "Global.h"
#include <regex>
#include <string>


inline bool readSceneDescription(const std::string& fileName, SceneInfo& scene) {
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile(fileName.c_str());
	if (xmlDoc.Error())
		return false;

	tinyxml2::XMLElement *rootElement = xmlDoc.RootElement();
	
	if (std::string(rootElement->Name()) == "scene_description") {
		tinyxml2::XMLElement *childElem = rootElement->FirstChildElement();
		if (childElem) {
			do
			{
				if (std::string(childElem->Name()) == "mesh3D_List") {
					tinyxml2::XMLElement *elem = childElem->FirstChildElement();
					if (elem) {
						do
						{
							if (std::string(elem->Name()) == "mesh3D") {
								scene.meshList.push_back(Mesh3DInfo(elem->Attribute("path"), elem->Attribute("name")));
							}
						} while (elem = elem->NextSiblingElement());
					}
				}
				
				if (std::string(childElem->Name()) == "scene_objects") {
					tinyxml2::XMLElement *elem = childElem->FirstChildElement();
					if (elem) {
						do
						{
							if (std::string(elem->Name()) == "object") {
								scene.objectList.push_back(ObjectInfo(elem->Attribute("name"), elem->Attribute("mesh3D"), elem->Attribute("type")));
								tinyxml2::XMLElement *elemChild = elem->FirstChildElement();
								if (elemChild) {
									do
									{
										if (std::string(elemChild->Name()) == "position") {
											elemChild->QueryFloatAttribute("x", &scene.objectList.back().position.x);
											elemChild->QueryFloatAttribute("y", &scene.objectList.back().position.y);
											elemChild->QueryFloatAttribute("z", &scene.objectList.back().position.z);
										}
										if (std::string(elemChild->Name()) == "euler_angles") {
											elemChild->QueryFloatAttribute("roll", &scene.objectList.back().eulerAngles.roll);
											elemChild->QueryFloatAttribute("pitch", &scene.objectList.back().eulerAngles.pitch);
											elemChild->QueryFloatAttribute("yaw", &scene.objectList.back().eulerAngles.yaw);
										}
									} while (elemChild = elemChild->NextSiblingElement());
								}
							}
						} while (elem = elem->NextSiblingElement());
					}
				}
			} while (childElem = childElem->NextSiblingElement());
		}
	}
	else
		return false;
	return true;
}

struct RandomFloat
{
private:
	std::uniform_real_distribution<float>*  randomFloat;
	std::random_device randomDevice;
	std::mt19937 engine;
public:
	RandomFloat() {
		engine.seed(randomDevice());
		randomFloat = new std::uniform_real_distribution<float>(-1.0f, 1.0f);
	}

	RandomFloat(float min, float max) {
		engine.seed(randomDevice());
		if (min < max)
			randomFloat = new std::uniform_real_distribution<float>(min, max);
		else
			randomFloat = new std::uniform_real_distribution<float>(-1.0f, 1.0f);
	}

	~RandomFloat() {
		if (randomFloat)
			delete(randomFloat);
	}

	float next() {
		return (*randomFloat)(engine);
	}

	void setRange(float min, float max) {
		if (min < max)
			randomFloat = new std::uniform_real_distribution<float>(min, max);
		else
			randomFloat = new std::uniform_real_distribution<float>(-1, 1);
	}
};

struct RandomInt
{
private:
	std::uniform_int_distribution<int>*  randomInt;
	std::random_device randomDevice;
	std::mt19937 engine;
public:
	RandomInt() {
		engine.seed(randomDevice());
		randomInt = new std::uniform_int_distribution<int>(-1, 1);
	}

	RandomInt(int min, int max) {
		engine.seed(randomDevice());
		if (min < max)
			randomInt = new std::uniform_int_distribution<int>(min, max);
		else
			randomInt = new std::uniform_int_distribution<int>(-1, 1);
	}

	~RandomInt() {
		if (randomInt)
			delete(randomInt);
	}

	int next() {
		return (*randomInt)(engine);
	}

	void setRange(int min, int max) {
		if (min < max)
			randomInt = new std::uniform_int_distribution<int>(min, max);
		else
			randomInt = new std::uniform_int_distribution<int>(-1, 1);
	}
};

#endif



